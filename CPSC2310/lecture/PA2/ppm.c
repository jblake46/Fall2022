/********
 * Blake Moore
 * CPSC2310 Sec 1
 * jbm6@clemson.edu
 * *************/

#include "ppm.h"


header readHeader(FILE* input)
{
    header headerVals;

    //this gets the magic numbers
    fscanf(input, "%c%c%c", &(headerVals.magicNum[0]), &(headerVals.magicNum[1]), &(headerVals.magicNum[2]));

    validateHeader(input);
    fscanf(input, "%d", &(headerVals.width));
    validateHeader(input);
    fscanf(input, "%d", &(headerVals.height));
    validateHeader(input);
    fscanf(input, "%d", &(headerVals.maxVal));
    return headerVals;
}

pixel** readPixel(FILE* input, header headerVals)
{
    //creating an array using malloc
    pixel** filePix= (pixel**)malloc(headerVals.height *sizeof(pixel*));

    for(int i = 0; i < headerVals.height; i++)
    {
        //making it a 2d array using malloc
        *(filePix+i) = (pixel*)malloc(headerVals.width * sizeof(pixel*));
    }

    for(int i = 0; i < headerVals.height; i++)
    {
        for(int j = 0; j < headerVals.width; j++)
        {
        fscanf(input, "%c", &((*(filePix+i)+j-1)->b));
        fscanf(input, "%c", &((*(filePix+i)+j)->r));
        fscanf(input, "%c", &((*(filePix+i)+j)->g));
        }
    }
    return filePix;
}


void writeHeader(FILE* out, header headerVals)
{
    //writing all the necesarry header value structs to the output file
    fprintf(out, "%c%c%c%d %d %d\n", headerVals.magicNum[0], headerVals.magicNum[1], headerVals.magicNum[2],headerVals.width, headerVals.height, headerVals.maxVal);
}


void validateHeader(FILE* input)
{
    //reads next char in file and adjusts it if theres a comment

    char c = fgetc(input);

    //checking file for comments, blank spaces or a new line
    while(c == '#' || c == ' ' || c == '\n')
    {
        //checks to see if we are at beginning at the comment
        //if so we go until we find the next line
        if(c == '#')
        {
            while(fgetc(input) != '\n')
            {
                //do nothing, we are just going until we find the \n
            }
        }
        //updating the char 
        c = fgetc(input);
    }
    //resetting char pointer
    fseek(input, -1, SEEK_CUR);
}

//writes the pixels to the output file
void writePix(FILE* out, pixel** pixArr, header headerValues)
{
    //loops through the 2d array and writes the rgb values to the file
    for(int i = 0; i <  headerValues.height; i ++)
    {
        for(int j = 0; j < headerValues.width; j++)
        {
            fprintf(out, "%c%c%c", (*(pixArr+i)+j)->r,(*(pixArr+i)+j)->g,(*(pixArr+i)+j)->b);
        }
    }
}