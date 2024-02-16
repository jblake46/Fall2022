/********************************
 *Blake Moore                   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6               *
 *Instructor:  Dr. Yvon Feaster *
********************************/
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