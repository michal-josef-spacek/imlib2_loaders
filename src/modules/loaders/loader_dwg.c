#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <dwg.h>

#include "loader_common.h"

#define DWG_DBG 0
#if DWG_DBG
#define D(fmt...) printf("Imlib2 DWG loader: " fmt)
#else
#define D(fmt...)
#endif

int dwg2bmp(char * dwg_file, int dest_fd);

int
dwg2bmp(char * dwg_file, int dest_fd)
{
   Dwg_Data            dwg;
   int                 error;
   unsigned char      *dib_data;
   uint32_t            dib_size;
   FILE               *bmp_fh;
   size_t              wrote_items;
   char                bmp_magic[2] = "BM";
   struct BMP_HEADER {
      uint32_t file_size;
      uint32_t reserved;
      uint32_t offset;
    } bmp_header;

   memset(&dwg, 0, sizeof(Dwg_Data));
   error = dwg_read_file(dwg_file, &dwg);
   if (error >= DWG_ERR_CRITICAL)
      {
         D("Cannot open DWG file\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }

   dib_data = dwg_bmp(&dwg, &dib_size);
   if (!dib_data)
      {
         D("Cannot get DIB data\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }
   if (dib_size < 1)
      {
         D("DIB data size is < 1\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }
   if (dib_size > dwg.thumbnail.size)
      {
         D("DIB data size is > thumbnail size\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }

   // Write BMP to tmp file.
   bmp_fh = fdopen(dest_fd, "w");
   if (!bmp_fh)
      {
         D("Cannot open dest tmp file\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }

   wrote_items = fwrite(&bmp_magic, sizeof(bmp_magic), 1, bmp_fh);
   if (!wrote_items)
      {
         D("Cannot write BMP magic\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }

   bmp_header.file_size = 14 + dib_size; // file header + DIB header
   bmp_header.reserved = 0;
   bmp_header.offset = 14 + 40 + 4 * 256; // file header + DIB header + color table
   wrote_items = fwrite(&bmp_header, sizeof(bmp_header), 1, bmp_fh);
   if (!wrote_items)
      {
         D("Cannot write BMP size\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }

   wrote_items = fwrite(dib_data, sizeof(char), dib_size, bmp_fh);
   if (!wrote_items)
      {
         D("Cannot write BMP data\n");
         dwg_free(&dwg);
         return LOAD_FAIL;
      }
   fclose(bmp_fh);

   dwg_free(&dwg);

   return 1;
}

int
load2(ImlibImage * im, int load_data)
{
   ImlibLoader        *loader;
   int                 dest, res;
   char                tmp[] = "/tmp/imlib2_loader_bmp-XXXXXX";

   loader = __imlib_FindBestLoaderForFormat("bmp", 0);
   if (!loader)
      {
         D("Cannot load BMP loader\n");
         return 0;
      }

   if ((dest = mkstemp(tmp)) < 0)
      {
         D("Cannot create tempfile for BMP file\n");
         return 0;
      }

   res = dwg2bmp(im->real_file, dest);
   if (!res)
      goto quit;
   close(dest);

   if (!res)
      goto quit;

   res = __imlib_LoadEmbedded(loader, im, tmp, load_data);

 quit:
   unlink(tmp);

   return res;
}

void
formats(ImlibLoader * l)
{
   static const char  *const list_formats[] = { "dwg" };
   __imlib_LoaderSetFormats(l, list_formats,
                            sizeof(list_formats) / sizeof(char *));
}
