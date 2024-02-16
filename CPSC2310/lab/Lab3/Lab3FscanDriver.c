/************************* 
       *Blake Moore
       *CPSC 2311 F22 Section 4 
       *jbm6@clemson.edu
      *************************/ 
#include "Lab3Fscan.h"
#include <assert.h>

int main(int argc, char* argv[])
{

    
    FILE *in;
    in = fopen(argv[1], "r");
    assert(argc >= 2);
    assert(in != NULL);
    
    //display error message if file is not opened properly
    /*
    if(in == NULL)
    {
       printf("%s\n", "FILE IS DUMB");
        return 0;
    }
    */
    start(in);
}