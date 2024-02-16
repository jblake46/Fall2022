/********************************
 *Blake Moore                   *
 *CPSC 2310 Fall 22             *
 *UserName:  jbm6               *
 *Instructor:  Dr. Yvon Feaster *
********************************/


#include "functions.h"

void add(node_t **node, node_t **head)
{   
    //creating an iterator to transverse the linked list
    
    node_t* iterator = NULL;
    
    //if head is of NULL value, set the current node to 
    if(*head == NULL)
    {
        *head = *node;
    }
    else
    {
        //sets iterator to head
        iterator = *head;
        //iterates to the end of the list 
        //then sets the next node to node passed into the function    
        while(iterator->next != NULL)
        {
            iterator = (node_t*)iterator->next;
        } 
        iterator->next = (node_t*)malloc(sizeof(node_t));
        iterator->next = (struct node_t*)*node;
    }

}
node_t* readNodeInfo(FILE* input)
{   
    //allocating space for the node
    node_t* tmpNode = (node_t*)malloc(sizeof(node_t));
    //creating character arrays to store the data 
    char tmpDay[6];
    char tmpMonth[6];
    char tmpYear[6];
    
    //this fscanf reads in info in the order indicated below
    //should be fName -> lName -> month -> day -> year -> fav song -> hobby -> 
    //and whyCS
    fscanf(input, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n] ", tmpNode->lName, 
    tmpNode->fName, tmpMonth, tmpDay, tmpYear, tmpNode->favSong,
    tmpNode->favPast, tmpNode->whyChoice);
    //converting the ascii value to integer value
    tmpNode->birthDay.month = atoi(tmpMonth);
    tmpNode->birthDay.day = atoi(tmpDay);
    tmpNode->birthDay.year = atoi(tmpYear);

    return tmpNode;
}
node_t* createList(FILE* input, node_t** headNode)
{

    //node_t* tmp = readNodeInfo(input);
    while(!feof(input))
    {
        node_t* tmp = readNodeInfo(input);
        add(&tmp, headNode);
    }

    return *headNode;

}
void printList(FILE* output, node_t* node)
{
    const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August",
 "September", "October", "November", "December"};
    
    node_t* iterator = node;
    fprintf(output, "\nList Info:\n");
    iterator = iterator->next;

    while(iterator != NULL)
    {
        fprintf(output, "Name: %s %s\n", iterator->fName, iterator->lName);
        fprintf(output, "Date of Birth: %s %d, %d\n", months[iterator->birthDay.month-1], iterator->birthDay.day,
        iterator->birthDay.year);
        fprintf(output, "Favorite Song: %s \n", iterator->favSong);
        fprintf(output, "Favorite Pastime: %s\n", iterator->favPast);
        fprintf(output, "Why I Chose CS: %s\n\n", iterator->whyChoice);
        iterator = iterator->next;
    }


}
void printBorder(FILE* output)
{

  for(int i = 0; i < 80; i++)
  {
      fprintf(output, "*");
  }
  fprintf(output, "\n");
}
void deleteList(node_t** node)
{
    //allocating size for iterator
    node_t* iterator = NULL;
    iterator = *node;
    //setting iterator to node to transfer the list
    while(iterator != NULL)
    {
        free(iterator);
        iterator = iterator->next;
    } 
}