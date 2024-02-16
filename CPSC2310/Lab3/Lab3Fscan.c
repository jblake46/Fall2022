#include <stdio.h>
#include <stdbool.h>
#include "Lab3Fscan.h"
/************************* 
       *Blake Moore
       *CPSC 2311 F22 Section 4 
       *jbm6@clemson.edu
      *************************/ 

void start(FILE* in){
    bool endOfFile = false;
    //char c;
    char charPtr;

    //while loops takes one character in, and does this until it hits the end of the file
    fscanf(in, "%c", &charPtr);   
    while(!feof(in))
    {

       
        if(charPtr == '/')
        {
            rcomment(in);
        }
        else if(charPtr != EOF)
        {
            putchar(charPtr);
        }
        fscanf(in, "%c", &charPtr);
    }
    printf("\n");
}

void rcomment(FILE* in)
{   //char junkChar = NULL;
    char charPtr = 0;


        fscanf(in, "%c", &charPtr); 

        if(charPtr == '*')
        {
            skipM_comment(in);
        }
        else if (charPtr == '/')
        {
            skipS_comment(in);
        }
}

void skipM_comment(FILE* in)
{   
    char charPtr = 0;
     //fscanf(in, "%c", &charPtr);
        //searches for the *, when found takes in the next character

        while(charPtr != '/')
        {   
            //printf("Do we get here");
            fscanf(in, "%c", &charPtr);
        }
}

void skipS_comment(FILE* in)
{
    char charPtr;
    fscanf(in, "%c", &charPtr);
    //searches for / then takes in the next
    while(charPtr != '\n')
    {
        fscanf(in, "%c", &charPtr);
    }
    printf("\n");
}   

