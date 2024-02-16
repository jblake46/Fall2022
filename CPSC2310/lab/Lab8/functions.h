/********************************
 *Blake Moore                   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6               *
 *Instructor:  Dr. Yvon Feaster *
********************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct pixels
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

typedef struct ppmHeader
{
    char magicNumber[2];
    int width;
    int height;
    int maxVal;
}ppmHeader;

/* Parameters: in - a file pointer pointing to the input file
 * Return:       output - ppmHeader struct which contains necessary
 * data to recreate the header on a ppm image
 * This function gets the header from a ppm image and returns those values
 * as a struct  
 */
ppmHeader readHeader(FILE* in);

/* Parameters: headerInfo - structure containing ppm image header values
*   out - file pointer to the outpur file
 * Return: void
 * This function writes to the output file the header Info found via readHeader 
 */
void writeHeader(ppmHeader headerInfo, FILE* out);

/* Parameters: in - file pointer to the input file
 * Return: void  
 * This function finds any comments in the input file, and skips them so that 
 * when writing to the new ppm image, the comments are ignored
 */
void discardComment(FILE* in);


#endif