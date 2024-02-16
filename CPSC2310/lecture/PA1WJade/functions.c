/********************************
 *Blake Moore and Jade Ashley   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6, vjashle      *
 *Instructor:  Dr. Yvon Feaster *
********************************/

#include "functions.h"

ppmHeader readHeader(FILE* in){

    //header is structured as, magicNum -> width -> height -> max value
    //creating a header struct
    ppmHeader header; 
    //getting magic number
    fscanf(in, "%s ", header.magicNumber);
    //checking for comments
    discardComment(in);
    //getting width
    fscanf(in, "%d ", &header.width);
    //checking for comments
    discardComment(in);
    //getting height
    fscanf(in, "%d ", &header.height );
    //checking comments
    discardComment(in);
    //getting maxVal
    fscanf(in, "%d ", &header.maxVal);
    //shouldnt have any more comments afterwards

    return header;
}


void writeHeader(ppmHeader headerValues, FILE* out)
{

    fprintf(out, "%s\n", headerValues.magicNumber);
    //printing width
    fprintf(out, "%d\n", headerValues.width);
    //printing height
    fprintf(out, "%d\n", headerValues.height);
    //printing max val
    fprintf(out, "%d\n", headerValues.maxVal);
}

void discardComment(FILE* in)
{

    char iteratorChar = fgetc(in);
    //taking in the values from the file
    
    //if the char iterator is a #, it is a comment, read til the end of line 
    while(iteratorChar  == '#')
    {
        //goes all the way until the end of the line
        while(iteratorChar != '\n')
        {
            iteratorChar = fgetc(in);
        }
        iteratorChar = fgetc(in);
    }
    //to prevent the iterator from going to far
    //i decided to use fseek to reset it back to one behind where it is at
    //this prevents it from overstepping
    //pretty nifty huh
    ungetc(iteratorChar, in);
}

pixel** allocation(int h, int w)
{
    //declaring a pointer for a 2d array 
    //and allocating memory for said array
    pixel** pixelPtrArr = (pixel**) malloc(h* sizeof(pixel*));
    for(int i = 0; i < h; i++)
    {
        pixelPtrArr[i]= (pixel*)malloc(w * sizeof(pixel*));
    }
    return pixelPtrArr;
}

void freeMem(pixel** pixelPtrArr, int h)
{
    for(int i = 0; i < h; i ++)
    {
        free(pixelPtrArr[i]);
    }
    free(pixelPtrArr);
}

pixel** readPixels(FILE* in, ppmHeader header)
{

    pixel** filePix = allocation(header.height, header.width);
    for(int i = 0; i < header.height; i++)
    {
        for(int j = 0; j < header.width; j++)
        {
            fscanf(in, "%c", &filePix[i][j].r);
            fscanf(in, "%c", &filePix[i][j].g);
            fscanf(in, "%c", &filePix[i][j].b);
        }
    }
    return filePix;
}

void writeNegPPM(ppmHeader headerVal, FILE* out, pixel** newPix)
{
    //writes the header   
    writeHeader(headerVal, out);
    //writing the pixels 
    for(int i = 0; i < headerVal.height; i++)
    {
        for(int j = 0; j < headerVal.width; j++)
        {
            fprintf(out, "%c", 255 - newPix[i][j].r);
            fprintf(out, "%c", 255 - newPix[i][j].g);
            fprintf(out, "%c", 255 - newPix[i][j].b);
        }
    }
}

void resize(ppmHeader header, pixel** pixArray, FILE* out){
    int orgWidth = header.width; 
    int userWidth; 
    int orgHeight = header.height;
    int userHeight; 
    double newCol; 
    double newRow; 
    ppmHeader tmpHead = header;

    printf("Enter number you wish to add or subtract the width by.");
    printf("Negative numbers mean decrease. Positive numbers mean increase");
    scanf("%d", &userWidth); 
    //make sure user input doesnt result in negative
    while((orgWidth - userWidth) == 0){
        printf("Enter a number less than %d", orgWidth); 
        scanf("%d", &userWidth); 
    }

    printf("Enter number you wish to add or subtract the height by.");
    printf("Negative numbers mean decrease. Positive numbers mean increase");
    scanf("%d", &userHeight); 
    //make sure user input doesnt result in negative
    while((orgHeight - userHeight) == 0){
        printf("Enter a number less than %d", orgHeight); 
        scanf("%d", &userHeight); 
    }
    tmpHead.width = (int)(userWidth+ orgWidth);
    tmpHead.height = (int)(userHeight + orgHeight);
    // calculate relative width and height 
    //divide original width by user width 
    double newWidth = ((double)orgWidth / (double)tmpHead.width); 
    //divide orginal height by user height
    double newHeight = ((double)orgHeight / (double)tmpHead.height); 

    //for each pixel, find relative pixel in old image that 
    //will be used to set the pixel in the new image by 
    //allocate new space for pixel
    pixel** resizeImg = allocation(tmpHead.height, tmpHead.width);


    for(int r = 0; r < tmpHead.height; r++){
        for(int c = 0; c < tmpHead.width; c++)
        {
            //multipying the current column * the relative width calcualted 
            newRow = r * newHeight; 
            //doing this for height 
            newCol = c * newWidth; 
            resizeImg[r][c] = pixArray[(int)newRow][(int)newCol]; 
        }
    }


    //set new resized image new[row][col] equal to the old image 
    printf("here: %lf \n", newRow);        
    printf("now: %lf \n", newCol); 
    writeHeader(tmpHead, out);

    //writing pixels
    for(int i = 0; i < tmpHead.height; i++)
    {
        for(int j = 0; j < tmpHead.width; j++)
        {
            fprintf(out, "%c", resizeImg[i][j].r);
            fprintf(out, "%c", resizeImg[i][j].g);
            fprintf(out, "%c", resizeImg[i][j].b);
        }
    }
    freeMem(resizeImg, tmpHead.height);
}