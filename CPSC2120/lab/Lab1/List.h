/*
 * Name: BLake Moore
 * Date Submitted: 9/12
 * Lab Section:6
 * Assignment Name: Lab1
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
  //intialized head of node to null
  start =NULL;
  mySize = 0;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
	Node<T> * iterator = start;
  Node<T>* nodeDestroyer; //thats a pretty cool name right?
  nodeDestroyer = iterator;
	while(iterator != nullptr)
	{
    nodeDestroyer = iterator;
    iterator = iterator->next;
    delete nodeDestroyer;
	}
}

//Return the size of this list
template <class T> //this one works
int List<T>::size(){
  /*
  
  Node<T>* iterator = start; 
  int counter; 
  while(iterator != nullptr)
  {
    iterator = iterator->next;
    counter++;
  }
  mySize = counter;

  */
  return mySize;

}

//Return true if this list is empty
//Otherwise, return false
template <class T> //this one works 
bool List<T>::empty(){
  Node<T> * iterator;
  iterator = start;
  if(start == NULL)
  {
    return true;
  }
  else{
    return false; 
  }
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>//this one works aswell
void List<T>::insertStart(T value){
  Node<T>* userNode = new Node(value);
  Node<T>* iterator = start;

    if(start != nullptr)
    {
        while(iterator->next != NULL){
          iterator = iterator->next;
        }
        iterator->next = userNode;
    }
    if(start == nullptr)
    {
        start = userNode;
    }
  mySize++;
}
	


//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
  Node<T>* iterator = start;
  Node<T>* userNode = new Node(value); 
  if(start == NULL)
  {
    start = userNode;
  }
  else{
    
    while(iterator->next != nullptr)
    {
      iterator = iterator->next;
    }
    iterator->next = userNode;
  }
  mySize++;

 
  


}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
  Node<T>* iterator = start;
  Node<T>* tmpHolder;
  if( size() > 0 && j <size())
  {
    if(j==0)
    {
      insertStart(value);
    }
    else
    {
      for(int i = 0; i < j - 1; i++)
      {
        iterator = iterator->next;
      }
      tmpHolder = iterator->next;
      iterator->next = new Node(value);
      iterator->next->next = tmpHolder;


    }
  mySize++;
  }
}

//Remove node at start
//Make no other changes to list
template <class T>//works
void List<T>::removeStart(){

 Node<T>* tmp; 
 if(start != nullptr){
   tmp = start->next;
   delete start;
   start = tmp;
    mySize--;
 }
 

}

//Remove node at end
//Make no other changes to list
template <class T> //works
void List<T>::removeEnd(){
  Node<T>* iterator = start;
  Node<T>* follow;
  if(start != nullptr)
  {
    while(iterator->next != nullptr)
    {
      follow = iterator; 
      iterator= iterator->next;
    }
      follow->next = nullptr;
      delete iterator;
      mySize--;
  }
  

}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){//thisworks
  Node<T>* iterator = start;
  Node<T>* tmpHolder;
  if( size() > 0 && j <size())
  {
    if(j==0)
    {
      removeStart();
    }
    else
    {
      for(int i = 0; i < j - 1; i++)
      {
        iterator = iterator->next;
      }
      tmpHolder = iterator->next;
      iterator->next = tmpHolder->next;
      delete tmpHolder;
      mySize--;
    }
  }

}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T> //works
T List<T>::getFirst(){

  return start->value;
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){//work
  Node<T>* iterator;
  if(start != nullptr)
  {
    iterator = start;
    while(iterator!= nullptr)
    {
      iterator=iterator->next;
      if(iterator->next == nullptr)
      {
        return iterator->value;
      }
    }
  return iterator->value;
  }
  else
  return T();
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
  Node<T>* iterator = start;

  if( size() > 0 && j <size())
  {
    if(j==0)
    {
      return start->value;
    }
    else
    {
      for(int i = 0; i < j; i++)
      {
        iterator = iterator->next;
      }
      return iterator->value;
      
    }
  }
  return T();
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){//work
  Node<T>* iterator;
  iterator = start;

  for(int i = 0; i < size(); i++)
  {
    if(iterator->value == key)
    {
      return i;
    }
    iterator = iterator->next;

  }
  return -1;
}
