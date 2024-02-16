/********************************
 *Blake Moore                   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6               *
 *Instructor:  Dr. Yvon Feaster *
********************************/
#include "functions.h"
int main(int argc, char * argv[])
{
    FILE* input;
    FILE* output;

    //opening file to read ppm data
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    //verifying enough files were passed on command line
    assert(argc >= 2);
    //checking input and output was created successfully
    assert(input !=  NULL);
    assert(output !=  NULL);
    //reading header info from the file
    ppmHeader header = readHeader(input);
    //writing said info to the newfile
    writeHeader(header, output);

    //allocating space for the size of the image
    size_t imageSize = header.width * header.height;
    pixel* imagePixels = (pixel*)malloc(imageSize * sizeof(pixel));

    //reading image data from the input file
    fread(imagePixels, sizeof(pixel), imageSize, input);
    //writing image data to the output file
    fwrite(imagePixels, sizeof(pixel), imageSize, output);

    fclose(output);
    fclose(input);
    free(imagePixels);
}