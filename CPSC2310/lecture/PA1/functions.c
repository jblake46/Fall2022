#include "functions.h"

ppmHeader readHeader(FILE* in)
{

    //header is structured as, magicNum -> width -> height -> max value
    //creating a header struct
    ppmHeader header; 
    //getting magic number
    fscanf(in, "%s ", header.magicNumber);
    //checking for comments
    discardComment(in);
    //getting width
    fscanf(in, "%d ", &header.width);
    //checking for comments
    discardComment(in);
    //getting height
    fscanf(in, "%d ", &header.height );
    //checking comments
    discardComment(in);
    //getting maxVal
    fscanf(in, "%d ", &header.maxVal);
    //shouldnt have any more comments afterwards

    return header;
}


void writeHeader(ppmHeader headerValues, FILE* out)
{

    fprintf(out, "%s\n", headerValues.magicNumber);
    //printing width
    fprintf(out, "%d\n", headerValues.width);
    //printing height
    fprintf(out, "%d\n", headerValues.height);
    //printing max val
    fprintf(out, "%d\n", headerValues.maxVal);
}

void discardComment(FILE* in)
{

    char iteratorChar = fgetc(in);
    //taking in the values from the file
    
    //if the char iterator is a #, it is a comment, read til the end of line 
    while(iteratorChar  == '#')
    {
        //goes all the way until the end of the line
        while(iteratorChar != '\n')
        {
            iteratorChar = fgetc(in);
        }
        iteratorChar = fgetc(in);
    }
    //to prevent the iterator from going to far
    //i decided to use fseek to reset it back to one behind where it is at
    //this prevents it from overstepping
    //pretty nifty huh
    ungetc(iteratorChar, in);
}

pixel** allocation(int h, int w)
{
    //declaring a pointer for a 2d array 
    //and allocating memory for said array
    pixel** pixelPtrArr = (pixel**) malloc(h* sizeof(pixel*));
    for(int i = 0; i < h; i++)
    {
        pixelPtrArr[i]= (pixel*)malloc(w * sizeof(pixel*));
    }
    return pixelPtrArr;
}

void freeMem(pixel** pixelPtrArr, int h)
{
    //iterates through and frees all memory
    for(int i = 0; i < h; i ++)
    {
        free(pixelPtrArr[i]);
    }
    free(pixelPtrArr);
}

pixel** readPixels(FILE* in, ppmHeader header)
{

    //creates space for the pixels
    pixel** filePix = allocation(header.height, header.width);
    //iterates through, and reads in all pixels and adds them to the array
    for(int i = 0; i < header.height; i++)
    {
        for(int j = 0; j < header.width; j++)
        {
            fscanf(in, "%c", &filePix[i][j].r);
            fscanf(in, "%c", &filePix[i][j].g);
            fscanf(in, "%c", &filePix[i][j].b);
        }
    }
    return filePix;
}

void writeNegPPM(ppmHeader headerVal, FILE* out, pixel** newPix)
{
    //writes the header   
    writeHeader(headerVal, out);
    //writing the pixels to output file
    for(int i = 0; i < headerVal.height; i++)
    {
        for(int j = 0; j < headerVal.width; j++)
        {
            fprintf(out, "%c", 255 - newPix[i][j].r);
            fprintf(out, "%c", 255 - newPix[i][j].g);
            fprintf(out, "%c", 255 - newPix[i][j].b);
        }
    }
}