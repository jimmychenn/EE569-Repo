#include "readraw.h"
#include "solutions.h"
#include <cmath>

int main(int argc, char *argv[])
{	
	if( !p1aCheckArgs(argc, argv))
		return 1;
	image_type image = read(argv[1]);
	image = solutionq1a(image);
	write(image, argv[2]);
	
	return 0;
}