
/********
 * Blake Moore
 * CPSC2310 Sec 1
 * jbm6@clemson.edu
 * *************/
#include "EncodeDecode.h"

void takeDigit(pixel** pixArray, header headerVals)
{
    //goes through the pix array and rounds down the rgb value
    int h = headerVals.height;
    int w = headerVals.width;
    //creating a variable to take place of the magic number
    //idk it helps me read it better
    int roundDown = 10;
    for(int i= 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            (*(pixArray+i)+j)->r = ((*(pixArray+i)+j)->r / roundDown) * roundDown; 
            (*(pixArray+i)+j)->g = ((*(pixArray+i)+j)->g / roundDown) * roundDown; 
            (*(pixArray+i)+j)->b = ((*(pixArray+i)+j)->b / roundDown) * roundDown; 
        }
    }
}

void charConv(char conversion, int* binaryNum)
{
    //creating a value to help with conversion
    int power = 1;
    //goes through each bit, starting with most significant
    //then finds binary value for each char
    for(int i = 8; i >= 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            power = power *2;
        }
        binaryNum[8-i] = (conversion >= power);
        if(conversion >= power)
        {
            conversion = conversion - power;
        }
        power = 1;
    }
}

unsigned char binaryConv(int* binaryNum)
{
    //creating return variable
    unsigned char character =0;
    //same concept with power variable as seen with charConv
    int power = 1;

    //goes through arr, creating decimal values to their binary counterpart
    for(int i = 0; i < 9; i++)
    {
        int tmp = 8 - i;
        for(int j = 0; j < tmp; j++)
        {
            power = power*2;

        }
        character += binaryNum[i]*power;
        //updating power
        power = 1;
    }
    return character;
}

void decimalConv(int *binaryNum, int tmp)
{
    //same power concept as binary Conv
    int power = 1;

    //once again, goes through each bit, starts with most sign bit
    //then determines binary value at each int in each bit
    for(int i = 8; i >= 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            //updating power (call me duke energy HAHA)
            //....im sorry
            power = power *2;
        }
        binaryNum[8-1] = (tmp >= power);
        if(tmp >= power)
        {
            tmp -= power;
        }

        //resetting power
        power = 1;

    }
}

//note - i named it q because im queueing it, and i thought it was
//funny and a play on words 
void q(int n, int* binaryNum, int* indexer)
{
    //gives a position via index in an array for the binary number
    //then gives that position the value of n
    binaryNum[*indexer] = n;


    //if last value in the binaryNum array is filled and is a valid char
    //print it to be viewed
    //commented out code was giving me a warning but im not entirely sure if that breaks my code or not
    if(*indexer == 8 /*&&binaryConv(binaryNum) < 256 */)
    {
        printf("%c", binaryConv(binaryNum));
    }

}


void decode(FILE* input)
{
    header headerVals = readHeader(input);
    pixel **pixArray = readPixel(input, headerVals);
    //intializing needed data for the q function
    int bin[9]; 
    int index = 0; 
    int* indexer = &index;

    //goes through pix array and uses q to create binary value of hidden
    // chars, and print them to terminal
    for(int i = 0; i < headerVals.height; i++)
    {
        for(int j = 0; j < headerVals.width; j++)
        {
            //getting each r g and b value
            q(((*(pixArray+i)+j)->r)%2, bin, indexer);
            //incrementing index
            index++;
            q(((*(pixArray+i)+j)->g)%2, bin, indexer);
            index++;
            q(((*(pixArray+i)+j)->b)%2, bin, indexer);
            index++;
            //catch statement
            //did this because i had a bug of it going out of scope
            //IT TOOK ME HOURS TO FIND
            if(index > 8)
            {
                index = 0;
            }
        }
    }
}

void encode(FILE* input, FILE* output, char* msg)
{
    //creates ppm header and pix array from input file
    header headerVals = readHeader(input);
    pixel **pixArray = readPixel(input, headerVals);

    //creating needed variables ya know just like with decode

    int msgIndexer =0;
    int binaryIndexer = msgIndexer;
    //set it to 9 because i had a bug when using empty messages and idk if we would be
    //tested on this for the program
    int binaryArr[9];

    charConv(msg[msgIndexer], binaryArr);
    takeDigit(pixArray, headerVals);
    //goes through the array, gives each set of 3 pixels 9 bits of each
    //character 
    //then stores it as there last digit of the respective rgb values
    for(int i = 0; i < headerVals.height; i ++)
    {
        for(int j = 0; j < headerVals.width; j++)
        {
            //checks to see iff the binary indexer is too high,
            //and to make sure the length of the msg fits in the index
            if(binaryIndexer <9)
            {
                (*(pixArray+i)+j)->r += binaryArr[binaryIndexer++];
                (*(pixArray+i)+j)->g += binaryArr[binaryIndexer++];
                (*(pixArray+i)+j)->b += binaryArr[binaryIndexer++];

            }
            if(binaryIndexer >= 9 && msgIndexer < strlen(msg) -1)
            {
                //reset binary indexer
                binaryIndexer =0;
                //increment msgIndexer
                msgIndexer++;
                charConv(msg[msgIndexer], binaryArr);

            }
            
        }
    }
    writeHeader(output, headerVals);
    writePix(output, pixArray, headerVals);
}