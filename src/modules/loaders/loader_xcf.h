#ifndef LOADER_XCF_H
#define LOADER_XCF_H

/* Stuff for layer merging: */
extern void         combine_pixels_normal(DATA8 * src, int src_w, int src_h,
                                          DATA8 * dest, int dest_w, int dest_h,
                                          int dest_x, int dest_y);
extern void         combine_pixels_add(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_sub(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_diff(DATA8 * src, int src_w, int src_h,
                                        DATA8 * dest, int dest_w, int dest_h,
                                        int dest_x, int dest_y);
extern void         combine_pixels_darken(DATA8 * src, int src_w, int src_h,
                                          DATA8 * dest, int dest_w, int dest_h,
                                          int dest_x, int dest_y);
extern void         combine_pixels_lighten(DATA8 * src, int src_w, int src_h,
                                           DATA8 * dest, int dest_w, int dest_h,
                                           int dest_x, int dest_y);
extern void         combine_pixels_mult(DATA8 * src, int src_w, int src_h,
                                        DATA8 * dest, int dest_w, int dest_h,
                                        int dest_x, int dest_y);
extern void         combine_pixels_div(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_screen(DATA8 * src, int src_w, int src_h,
                                          DATA8 * dest, int dest_w, int dest_h,
                                          int dest_x, int dest_y);
extern void         combine_pixels_overlay(DATA8 * src, int src_w, int src_h,
                                           DATA8 * dest, int dest_w, int dest_h,
                                           int dest_x, int dest_y);
extern void         combine_pixels_hue(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_sat(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_val(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_col(DATA8 * src, int src_w, int src_h,
                                       DATA8 * dest, int dest_w, int dest_h,
                                       int dest_x, int dest_y);
extern void         combine_pixels_diss(DATA8 * src, int src_w, int src_h,
                                        DATA8 * dest, int dest_w, int dest_h,
                                        int dest_x, int dest_y);

#endif /* LOADER_XCF_H */
