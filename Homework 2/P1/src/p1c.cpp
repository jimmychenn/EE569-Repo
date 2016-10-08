#include "readraw.h"
#include "solutions.h"
#include "global.h"

int main(int argc, char *argv[])
{	
	image_type fieldImage = read(FIELD_FILE, 972, 648, 3);
	image_type image = solutionq1c(fieldImage);
	write(image, P1C_OUT);
	
	return 0;
}