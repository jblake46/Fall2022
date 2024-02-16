/********
 * Blake Moore
 * CPSC2310 Sec 1
 * jbm6@clemson.edu
 * *************/

#ifndef ENCODEDECODE_H
#define ENCODEDECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
/* Parameters pixel** - 2D pixel array
              header - header struct containing needed header values
              to create a header in a new file
* Return: void
* Function justs rounds down the pixel values
*/
void takeDigit(pixel**, header);

/* Parameters FILE* - file pointer to the output file
              FILE* - pointer to the input file
              char* - char ptr message to be encoded
* Return: void
* Function makes a ppm img with the encoded message in it
*/
void encode(FILE*, FILE*, char*);

/* Parameters  char - character to be converted binary
                int* int array that displays binary number
* Return: void
* Function converts the character to its binary counter part
*/
void charConv(char, int*);

/* Parameters int* - int array for showing a binary number

* Return: unsigned char that was converted from the binary number
* Function converts binary to its char counter part
*/
unsigned char binaryConv(int*);
/* Parameters int - binary value to be queued into an array
              int* - int arrray for showing binary number
              int* - pointer to the position in the binary array
* Return: void
* Function places the int value to be queued into the int* index in the int* binary
array
*/

void q(int,int*, int*);

/* Parameters int* - int array for binary number
                int - decimal int to convert to binary

* Return: void
* Function converts from decimal to binary
*/
void decimalConv(int*, int);

/* Parameters FILE* - file pointer to the output file
* Return: void
* Function decodes the message in the ppm img and displays it
in the terminal
*/
void decode(FILE*); 

#endif