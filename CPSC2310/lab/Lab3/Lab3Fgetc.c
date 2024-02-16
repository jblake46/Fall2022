#include <stdio.h>
#include <stdbool.h>
#include "Lab3Fgetc.h"

/************************* 
       *Blake Moore
       *CPSC 2311 F22 Section 4 
       *jbm6@clemson.edu
      *************************/ 
void start(FILE* in){
    //bool endOfFile = false;
    char c;
    c = fgetc(in);
    //while loops takes one character in, and does this until it hits the end of the file
    while(!feof(in))
    {
       
        if(c == '/')
        {
            rcomment(in);
        }
 
        else
        {
            putchar(c);
        }

        c = fgetc(in);
    }
}

/*
*rcomment decides which function to call to take out the comments
*/
void rcomment(FILE* in)
{
    char notImportant = fgetc(in);


        if( notImportant == '*')
        {
            skipM_comment(in);
        }
        else if (notImportant == '/')
        {
            skipS_comment(in);
        }        
    
}

void skipM_comment(FILE* in)
{   
    char discardChar = 0;//fgetc(in);
        //searches for the *, when found takes in the next character
 
        while(discardChar != '/')
        {   
            //printf("Do we get here");
            discardChar = fgetc(in);
        }
   
        

}
void skipS_comment(FILE* in)
{
    char discardChar = fgetc(in);  
    //searches for / then takes in the next
    while(discardChar != '\n')
    {
        discardChar = fgetc(in);
    }
    printf("\n");
}   
