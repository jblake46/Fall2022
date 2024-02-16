/********
 * Blake Moore
 * CPSC2310 Sec 1
 * jbm6@clemson.edu
 * *************/

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
typedef struct pixels
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

typedef struct headers
{
    char magicNum[3];
    int width;
    int height;
    int maxVal;
}header;

header readHeader(FILE*);

/*Parameters: FILE* - pointer to the ppm file with pixels wanted
 *            header - header struct with the info of the given file
 *Return:      pointer 2D array of pixels with the info of the file
 *Reads in the pixels from the  file and returns an array of pixels
 */
pixel **readPixel(FILE*, header);

/* Parameters FILE* - file pointer to the output file
              header - header struct containing needed header values
              to create a header in a new file
* Return: void
* Function justs writes the header files to the file passed into it
*/
void writeHeader(FILE*, header);

/* Parameters FILE* - file pointer to the specified file
              header - header struct containing needed header values
              to create a header in a new file
              pixel** - 2d ptr array containing needed rgb values
* Return: void
* Function justs writes the rgb pixel values to the file
*/
void writePix(FILE*, pixel**, header);

/* Parameters FILE* - file pointer to the specified file

* Return: void
* Function justs checks to see if theres a comment or not
*/
void commentCheck(FILE*);
/* Parameters FILE* - file pointer to the specified file

* Return: void
* Function justs checks to make sure the header is valid that way the header struct does not get
*messed up when looking for header values
*/
void validateHeader(FILE*);

#endif