/********************************
 *Blake Moore                   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6               *
 *Instructor:  Dr. Yvon Feaster *
********************************/

#include "functions.h"
#include <assert.h>

int main(int argc, char * argv[])
{ 
    //creating input and output file pointers
    FILE* input;
    FILE* output;
    node_t* head = (node_t*)malloc(sizeof(node_t));
    //opening input for reading
    input = fopen(argv[1], "r");
    //opening output file to write to
    output = fopen(argv[2], "w");
    //making sure there are not too many arguments passed to main
    assert(argc >= 2);
    //validating that input was opened correctly
    assert(input != NULL);
    //validating that output was created successfully
    assert(output != NULL);

    //creating the list
    createList(input, &head);
    printBorder(output);
    printList(output, head);
    printBorder(output);
    deleteList(&head);

}
