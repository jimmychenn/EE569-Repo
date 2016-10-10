#include "readraw.h"
#include "solutions.h"
#include "global.h"

int main(int argc, char *argv[])
{	
	image_type fieldImage = read(FIELD_FILE, 972, 648, 3);
	solutionq1c(fieldImage);
	
	return 0;
}