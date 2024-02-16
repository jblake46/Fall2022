/********************************
 *Blake Moore                   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6               *
 *Instructor:  Dr. Yvon Feaster *
********************************/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//implement BDay struct here
typedef struct Bday
{
    int month;
    int day;
    int year;
}Bday;


//implement node_t struct here
typedef struct node_t
{
    Bday birthDay;
    char fName[20];
    char lName[20];
    char favSong[100];
    char favPast[100];
    char whyChoice[500];
    struct node_t *next;
}node_t;
//use typedef on this struct!

/* Parameters: node - the node to be added to the linked list
 *             head - the node that begins the linked list
 * Return: is a void function, no retrun
 * This function adds nodes to a linked list
 */
void add(node_t **node, node_t **head);

/* Parameters: input - file pointer pointing to the input file information
 *                    
 * Return:  node_t* - node_t pointer holding the information 
 *                      from the input file
 * This function gets the info from the file and passes it to the node  
 * 
 */
node_t* readNodeInfo(FILE* input);

/* Parameters: 1st parameter - file pointer that is the input file
 *             2nd parameter - node pointer that is the head node of the 
                                linked list
 * Return: returns a node pointer
 * This function creates the list of pointers 
 */
node_t* createList(FILE*, node_t**);

/* Parameters: 1st parameter - file pointer that is the output file
 *             2nd parameter - node pointer that is the head node of the 
                                linked list
 * Return: none
 * This function prints the list to the output file
 */
void printList(FILE*, node_t*);

/* Parameters: 1st parameter - file pointer pointing to the output file
 * Return: none 
 * This function prints a border to format the list
 */
void printBorder(FILE*);

/* Parameters: 1st parameter - the node double pointer to the head of the linked list
 * Return: none 
 * This function frees all memory allocated for each node in the linked list 
 */
void deleteList(node_t** );
#endif
