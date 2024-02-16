/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
printf(" %.2x", start[i]);  
    printf("\n");
}
int main(int argc, char *argv[])
{
    /*-12345 is signed*/
    short sx = -12345; //what if we change this to 12345
    
    /*53191 size same
     *implicitly converts from signed short to unsigned short*/
    unsigned short usx = sx;
    /*-12345 Implicitly converts size of the sx to 4 bytes
     *both are signed What type of extension will occur and when*/
    int x = sx;
    /*53191 size 2 to 4 
     *both are unsigned (implicit conversion with an extension)*/
    unsigned ux = usx;
   
    
    /* signed to unsigned and from 2 to 4 bytes.
     *This shows that when converting from short to unsigned int - the program 
first
     *changes the size from 2 to 4 bytes (sign extension) and then the goes 
     *from signed to unsigned.(c7 cf - little endian) The actual bit representation
     * is cf c7 = 1100 1111 1100 0111 the expansion is done first 
     *so the output would be 1111 1111 1111 1111 1100 1111 1100 0111
     */
    unsigned uy = sx;//Signed extension
    printf("size of a short %lu\n", sizeof(short));
    printf("sx = %d: \t", sx);
    show_bytes((byte_pointer) &sx, sizeof(short));
    
    printf("\n");
    printf("size of an unsigned short %lu\n", sizeof(unsigned short));
    printf("usx = %u: \t", usx);
    show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    
    printf("\n");
    printf("size of an int %lu\n", sizeof(int));
    printf("x = %d: \t", x);
    show_bytes((byte_pointer) &x, sizeof(int));
    
    printf("\nZero Extension\n");
    printf("size of an unsigned %lu\n", sizeof(unsigned));
    printf("ux = %u: \t", ux);
}
