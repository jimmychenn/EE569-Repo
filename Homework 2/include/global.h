#ifndef GLOBAL_H
#define GLOBAL_H

typedef boost::multi_array<unsigned char, 3> image_type;
typedef image_type::index ind;
int BytesPerPixel;
int Width;
int Height;
char piece_image_file[] = "HW_2_images/piece.raw";

#endif
