#include "readraw.h"
#include "solutions.h"
#include "global.h"

int main(int argc, char *argv[])
{	
	image_type riceImage = read(RICE_FILE, 690, 500, 3);
	solutionq3a(riceImage);
	
	return 0;
}