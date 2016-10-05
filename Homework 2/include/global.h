#ifndef GLOBAL_H
#define GLOBAL_H

typedef boost::multi_array<unsigned char, 3> image_type;
typedef image_type::index ind;
int BytesPerPixel = 3;
int Width;
int Height;

//In file names
char PIECE_FILE[] = "P1/res/piece.raw";
char HILLARY_FILE[] = "P1/res/Hillary.raw";
char TRUMP_FILE[] = "P1/res/Trump.raw";

//Out file names
char P1B_OUT[] = "P1B_out.raw";

#endif
