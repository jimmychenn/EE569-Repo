#include "readraw.h"
#include "solutions.h"
#include "global.h"
#include <cmath>

int main(int argc, char *argv[])
{	
	image_type pieceImage = read(PIECE_FILE, 500, 500, 3);
	solutionq1b(pieceImage);
	
	return 0;
}