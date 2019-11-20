#ifndef LOADER_XCF_H
#define LOADER_XCF_H

/* Stuff for layer merging: */
extern void         combine_pixels_normal(const DATA32 * src, int src_w,
                                          int src_h, DATA32 * dest, int dest_w,
                                          int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_add(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_sub(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_diff(const DATA32 * src, int src_w,
                                        int src_h, DATA32 * dest, int dest_w,
                                        int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_darken(const DATA32 * src, int src_w,
                                          int src_h, DATA32 * dest, int dest_w,
                                          int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_lighten(const DATA32 * src, int src_w,
                                           int src_h, DATA32 * dest, int dest_w,
                                           int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_mult(const DATA32 * src, int src_w,
                                        int src_h, DATA32 * dest, int dest_w,
                                        int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_div(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_screen(const DATA32 * src, int src_w,
                                          int src_h, DATA32 * dest, int dest_w,
                                          int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_overlay(const DATA32 * src, int src_w,
                                           int src_h, DATA32 * dest, int dest_w,
                                           int dest_h, int dest_x, int dest_y);
extern void         combine_pixels_hue(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_sat(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_val(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_col(const DATA32 * src, int src_w, int src_h,
                                       DATA32 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_diss(const DATA32 * src, int src_w,
                                        int src_h, DATA32 * dest, int dest_w,
                                        int dest_h, int dest_x, int dest_y);

#endif /* LOADER_XCF_H */
