/********
 * Blake Moore
 * CPSC2310 Sec 1
 * jbm6@clemson.edu
 * *************/


#include "EncodeDecode.h"

int main(int argc, char* argv[])
{
    FILE*in = fopen(argv[1],"r");
    FILE* out = fopen(argv[2], "w");

     char* encodeMsg = "thanks for the semester";
    encode(in, out, encodeMsg);
    FILE* decoder = fopen(argv[2], "r");
    decode(decoder);
    fclose(in);
    fclose(out);
    fclose(decoder);

    return 0;
}