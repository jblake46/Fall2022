
#include "functions.h"

int main(int argc, char* argv[])
{
    FILE* input;
    FILE* outputNegativePPM;
    //opening files to read/write data
    input = fopen(argv[1], "r");
    outputNegativePPM = fopen(argv[2], "w");
    //making sure there are enough files passed into the main
    assert(argc >= 4);
    //making sure input and output were created successfully
    assert(input != NULL);
    assert(outputNegativePPM != NULL);
    //getting header info
    ppmHeader header = readHeader(input);
    //allocate size for 2d pixel array
    pixel** pixels = allocation(header.height, header.width);
    //reading pixels
    pixels = readPixels(input, header);
    writeNegPPM(header, outputNegativePPM, pixels);
}