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


void writePPM(ppmHeader headerVal, FILE* out, pixel negativePix);

void discardComment(FILE* in);

ppmHeader readHeader(FILE* in);

pixel** allocation(int h, int w);
void freeMem(pixel** pixelPtrArr, int h);
pixel** readPixels(FILE* in, ppmHeader header);
void writeNegPPM(ppmHeader headerVal, FILE* out, pixel** newPix);
#endif