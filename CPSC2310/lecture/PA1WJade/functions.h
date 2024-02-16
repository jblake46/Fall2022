/********************************
 *Blake Moore and Jade Ashley   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6, vjashle      *
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

/* Parameters: headerVal 
 * Parameters: out
 * Parameters: negativePix
 * Return: void 
 * This function writes a ppm header of an image
 */
void writePPM(ppmHeader headerVal, FILE* out, pixel negativePix);

/* Parameters: in - a file pointer pointing to the input file
 * Return: void
 * This function discards comments 
 */
void discardComment(FILE* in);

/* Parameters: in - a file pointer pointing to the input file
 * Return: output - ppmHeader struct which contains necessary
 * data to recreate the header on a ppm image
 * This function gets the header from a ppm image and returns those values
 * as a struct  
 */
ppmHeader readHeader(FILE* in);

/* Parameters: h - height of the ppm image
    w - width of ppm image
 * Return: pixel** that has allocated memory
 * This function use 2d memory allocation for image pixels
 */
pixel** allocation(int h, int w);

/* Parameters: pixelPtrArr - pixel 2d array
 * Parameters: h - height of ppm image
 * Return: void
 * This function gives allocated memory back to operating system  
 */
void freeMem(pixel** pixelPtrArr, int h);

/* Parameters: in - a file pointer pointing to the input file
 * Parameters: header - header values from the ppm image
 * Return: pixel** that contains pixels from the input file
 * This function read pixels of image
 */
pixel** readPixels(FILE* in, ppmHeader header);

/* Parameters: headerVal - header values from the ppm image
 * Parameters: out - output file
 * Paramters: newPix - 2d pixel array from the ppm image
 * Return: void
 * This function create negative of the image 
 */
void writeNegPPM(ppmHeader headerVal, FILE* out, pixel** newPix);

/* Parameters:  header - contains necessarry ppm image header values
 * Return: void
 * This function resizes the image
 */
void resize(ppmHeader header, pixel** pixArray, FILE* out);

#endif