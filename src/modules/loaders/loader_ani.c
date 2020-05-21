/*

Copyright (C) 2002 Christian Kreibich <cK@whoop.org>.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies of the Software and its documentation and acknowledgment shall be
given in the documentation and software packages that this Software was
used.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>

#include "loader_common.h"

#define ANI_DBG 0
#if ANI_DBG
#define D(fmt...) printf("Imlib2 ANI loader: " fmt)
#else
#define D(fmt...)
#endif

typedef struct _MsChunk {
   struct _MsChunk    *next;
   DATA32              chunk_id;
   DATA32              chunk_size;      /* Size of this chunk, starting from */
   DATA8               data;    /* the following byte. Thus chunk_size = full size - 8 */
} MsChunk;

typedef struct _MsAni {
   char               *filename;
   FILE               *fp;
   DATA32              cp;

   DATA32              riff_id; /* "RIFF" */
   DATA32              data_size;
   DATA32              chunk_id;        /* "ACON" */

   MsChunk            *chunks;
} MsAni;

static void         ani_cleanup(MsAni * ani);

static int
ani_read_int8(FILE * fp, DATA8 * data, int count)
{
   int                 total;
   int                 bytes;

   total = count;
   while (count > 0)
     {
        bytes = fread(data, 1, count, fp);
        if (bytes <= 0)         /* something bad happened */
           break;
        count -= bytes;
        data += bytes;
     }

   return total;
}

static int
ani_read_int32(FILE * fp, DATA32 * data, int count)
{
   int                 i, total;

   total = count;
   if (count > 0)
     {
        ani_read_int8(fp, (DATA8 *) data, count * 4);
        for (i = 0; i < count; i++)
           data[i] = SWAP_LE_32(data[i]);
     }

   return total * 4;
}

static MsAni       *
ani_init(char *filename)
{
   MsAni              *ani;

   if (!(ani = calloc(1, sizeof(MsAni))))
      return NULL;

   if (!(ani->fp = fopen(filename, "r")))
      goto bail;

   ani->filename = filename;
   ani->cp += ani_read_int32(ani->fp, &ani->riff_id, 1);
   ani->cp += ani_read_int32(ani->fp, &ani->data_size, 1);
   ani->cp += ani_read_int32(ani->fp, &ani->chunk_id, 1);

   if (ani->riff_id != 0x46464952 || ani->chunk_id != 0x4E4F4341)
      goto bail;

   return ani;

 bail:
   ani_cleanup(ani);
   return NULL;
}

static void
ani_cleanup(MsAni * ani)
{
   MsChunk            *c, *c_next;

   D("Cleaning up\n");

   if (!ani)
      return;

   if (ani->fp)
      fclose(ani->fp);

   for (c = ani->chunks; c;)
     {
        c_next = c->next;
        free(c);
        c = c_next;
     }

   free(ani);
}

static MsChunk     *
ani_load_chunk(MsAni * ani)
{
   DATA32              chunk_id, chunk_size, dummy;
   MsChunk            *chunk;

   if (ani->cp >= ani->data_size + 8)
      return NULL;

   ani->cp += ani_read_int32(ani->fp, &chunk_id, 1);

   while (chunk_id == 0x5453494C)
     {
        D("Skipping LIST chunk header ...\n");
        ani->cp += ani_read_int32(ani->fp, &dummy, 1);
        ani->cp += ani_read_int32(ani->fp, &dummy, 1);
        ani->cp += ani_read_int32(ani->fp, &chunk_id, 1);
     }

   ani->cp += ani_read_int32(ani->fp, &chunk_size, 1);

   /* Pad it up to word length */
   if (chunk_size % 2)
      chunk_size += (2 - (chunk_size % 2));

   chunk = calloc(1, sizeof(MsChunk *) + 2 * sizeof(DATA32) + chunk_size);
   if (!chunk)
     {
        D("Warning, failed to allocate ANI chunk of size %ld\n",
          sizeof(MsChunk *) + 2 * sizeof(DATA32) + chunk_size);
        return NULL;
     }

   chunk->chunk_id = chunk_id;
   chunk->chunk_size = chunk_size;

   chunk_id = SWAP_LE_32(chunk_id);

   D("Loaded chunk with ID '%c%c%c%c' and length %i\n",
     ((char *)&chunk_id)[0], ((char *)&chunk_id)[1],
     ((char *)&chunk_id)[2], ((char *)&chunk_id)[3], chunk_size);

   ani->cp += ani_read_int8(ani->fp, &chunk->data, chunk_size);

   return chunk;
}

static void
ani_load(MsAni * ani)
{
   MsChunk            *last_chunk;
   MsChunk            *chunk;

   if (!ani)
      return;

   ani->chunks = ani_load_chunk(ani);
   last_chunk = ani->chunks;
   if (!last_chunk)
      return;

   while ((chunk = ani_load_chunk(ani)))
     {
        last_chunk->next = chunk;
        last_chunk = chunk;
     }
}

static char        *
ani_save_ico(MsChunk * chunk)
{
   char                tmp[] = "/tmp/imlib2_loader_ani-XXXXXX";
   int                 fd;

   fd = mkstemp(tmp);
   if (fd < 0)
      return NULL;

   write(fd, &chunk->data, chunk->chunk_size);
   close(fd);

   return strdup(tmp);
}

char
load(ImlibImage * im, ImlibProgressFunction progress, char progress_granularity,
     char load_data)
{
   int                 rc;
   ImlibLoader        *loader;
   MsAni              *ani = NULL;
   MsChunk            *chunk;

   loader = __imlib_FindBestLoaderForFormat("ico", 0);
   if (!loader)
      return LOAD_FAIL;

   if (!(ani = ani_init((im->real_file))))
      return LOAD_FAIL;

   ani_load(ani);

   rc = LOAD_FAIL;

   for (chunk = ani->chunks; chunk; chunk = chunk->next)
     {
        if (chunk->chunk_id == 0x6E6F6369)
          {
             char               *tmpfile;

             if (!(tmpfile = ani_save_ico(chunk)))
                break;

             rc = __imlib_LoadEmbedded(loader, im, tmpfile, load_data);

             unlink(tmpfile);
             free(tmpfile);
             break;
          }
     }

   ani_cleanup(ani);

   return rc;
}

void
formats(ImlibLoader * l)
{
   static const char  *const list_formats[] = { "ani" };
   __imlib_LoaderSetFormats(l, list_formats,
                            sizeof(list_formats) / sizeof(char *));
}
