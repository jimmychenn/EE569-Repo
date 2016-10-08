#ifndef GLOBAL_H
#define GLOBAL_H
#include "boost/multi_array.hpp"

typedef boost::multi_array<unsigned char, 3> image_type;
typedef boost::multi_array<double, 3> double_image_type;
typedef boost::multi_array<int, 3> three_d_int;
typedef boost::multi_array<int, 2> filter;
typedef boost::multi_array<double, 2> double_filter;
typedef image_type::index ind;
int BytesPerPixel = 3;
int Width;
int Height;

//In file names
char PIECE_FILE[] = "P1/res/piece.raw";
char HILLARY_FILE[] = "P1/res/Hillary.raw";
char TRUMP_FILE[] = "P1/res/Trump.raw";
char FIELD_FILE[] = "P1/res/field.raw";
char TARTANS_FILE[] = "P1/res/tartans.raw";
char TROJANS_FILE[] = "P1/res/trojans.raw";
char HOUSE_FILE[] = "P2/res/house.raw";
char RICE_FILE[] = "P3/res/rice.raw";

//Out file names
char P1B_OUT[] = "P1B_out.raw";
char P1C_OUT[] = "P1C_out.raw";
char P2A_OUT[] = "P2A_out";
char P2B_OUT[] = "P2B_out";

//Binarization method
int GLOBAL_MEAN_THRESHOLD = 1;
int ADAPTIVE_LOCAL_MEAN = 2;

#endif
