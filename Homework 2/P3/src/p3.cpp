#include "readraw.h"
#include "solutions.h"
#include "global.h"

int main(int argc, char *argv[])
{	
	image_type riceImage = read(RICE_FILE, 512, 512, 1);
	solutionq2c(houseImage);
	
	return 0;
}