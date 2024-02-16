/*
 * Name: Blake Moore
 * Date Submitted: Nov 18
 * Lab Section: 1
 * Assignment Name: Searches and Sorting
 */

#pragma once

#include <vector>

template <class T>
std::vector<T> mergeSort(std::vector<T> lst){
    std::vector<T> left;
    std::vector<T> right;

    //if list is 1 or below, cannot be sorted
    if(lst.size <= 1)
    {
        return lst;
    }
    //finding mid
    int mid = lst.size() / 2;
    //creating left side
    int i = 0;
    //doing left side
    while(i < mid)
    {
        left.push_back(lst.at(i));
        i ++;
    }
    //correcting i's position
    i = mid;
    while( i < lst.size())
    {
        right.push_back(lst.at(i));
        i++;
    }
    left = mergeSort(left);
    right = mergeSort(right);
    //merging the  vectors
    std::vector<T> tmp;
    int sizeOfL = left.size();
    int sizeOfR = right.size();
    int j = 0
    //reusing i
    i = 0;

    while(i < sizeofL && j < sizeOfR)
    {
        if(left[i] < right[i])
        {
            tmp.push_back(left[i]);
            i++;
        }
        else
        {
            tmp.push_back(right[i]);
            j++;
        }
    }
    //catching a test case that i messed up on
    if(i == sizeofL)
    {
        while(j < sizeofR)
        {
            tmp.push_back(right[j]);
            j++
        }
    }
    else if(j == sizeOfR)
    {
        while(i < sizeOfL)
        {
            tmp.push_back(left[j])
            i++;
        }
    }
    //returning the sorted and merged vector
    return tmp;
}
template <class T> 
int quickSortHelper(std::vector<T> lst, int start, int end)
{
    int pivot = lst.at(start);
    int count = 0;
    for(int i = start +1; start <= end; i++)
    {
        if(lst.at(i) <= pivot)
        {
            count++;
        }
    }
    int pivotIndex = start + count;
    swap(lst.at(pivotIndex), lst.at(start));

    int i = start, j =end;
    while(i < pivotIndex && j > pivotIndex)
    {
        while(lst.at(i) <= pivot)
        {
            i++;
        }
        while(lst.at(j) > pivot)
        {
            j--;
        }
        if(i < pivotIndex && j > pivotIndex)
        {
            tmpI = i + 1;
            tmpJ = j -1 1;
            swap(lst.at(tmpI), lst.at(tmpJ));
        }

    }
    return pivotIndex;
}

template <class T>
std::vector<T> quickSort(std::vector<T> lst)
{
    int start = 0;
    int end = sizeof(lst) -1;

    int p = quickSortHelper(lst, start, end);
    

    //sorting left side
    quickSort(lst, start, p-1);
    //sorting right
    quickSort(lst, p+1, end);

}
