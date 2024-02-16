/*
 * Name: Blake Moore
 * Date Submitted: Nov 18
 * Lab Section: 1
 * Assignment Name: Searches and Sorting
 */

#pragma once

#include <vector>
//searches for target in vector data
//returns the position of the target if found
// returns -1 if not found
template <class T>
int linearSearch(std::vector<T> data, T target)
{
    vectorSize = data.size();
    /*this iterates through the vector to find
    * the targeted value in the vector
    */
    for(int i = 0; i < vectorSize; i++)
    {
        if(data[i] == target)
        {
            return i;
        }
    }
    //this is just in case it does not find the target
    return -1;
}


template <class T>
int binarySearch(std::vector<T> data, T target)
{
    int low = 0, high = data.size() - 1;
    while(!(low == high))
    {
        int mid = (low+high)/2
        //if target is found, return the index
        if(target == data[mid])
        {
            return mid;
        }
        //x is on right side 
        else if(x > arr[mid])
        {
            low = mid+1;
        }
        //x is on left side
        else
        {
            high = mid - 1;
        }
    }
    //if it is not found, return -1
    return -1;
}
