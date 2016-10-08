#include "readraw.h"
#include "solutions.h"
#include "global.h"

int main(int argc, char *argv[])
{	
	image_type houseImage = read(HOUSE_FILE, 512, 512, 1);
	solutionq2b(houseImage);
	
	return 0;
}