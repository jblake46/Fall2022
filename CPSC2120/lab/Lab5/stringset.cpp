/*
 * Name: Blake Moore
 * Date Submitted: 10.7.2022
 * Lab Section: 
 * Assignment Name: Spell Checker Using a Hash Table
 */


#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word)
{ 
    int insert_location;
    hash<string> hashValue;
    insert_location = hashValue(word) % size;
    if(!find(word))
    {
    /* this is to double the size worry abt it later*/
        if(num_elems == size)
        {
            int newSize = 2 * size;
            vector<list<string>> newHashTable(newSize);
            //insert_location = hashValue(word) % newSize;
            //looping through old vector to rehash values into a new 
            //bigger vector 
            for(int i = 0; i < size; i++)
            {

                for(auto it = table[i].begin(); it!= table[i].end(); ++it)
                {
                    insert_location = hashValue(*it) % newSize;
                    newHashTable[insert_location].push_front(*it);
                }
            }
            //updating the old values
            table = newHashTable;
            size = newSize;
        }
    

    table[insert_location].push_front(word);
    num_elems++;
    }

    //Implement this function
}

bool Stringset::find(string word) const
{
    //creating necesarry variables to determine where location
    //of the word should be
    int location;
    hash<string> hashValue;
    location = hashValue(word)% size;
    //iterate through the list if word is found return true
    for(auto it = table[location].begin(); it!= table[location].end(); ++it)
    {
        if(*it == word)
        {
            return true;
        }
        
    }
    //returns false if it is not found
    return false;

    
}

void Stringset::remove(string word)
{
    int location;
    hash<string> hashValue;
    location = hashValue(word)% size;
    table[location].remove(word);
    if(num_elems > 0)
    {
        num_elems--;
    } 
}