#include "minHeap.h"
#include "math.h" 
/*
* I recieved an extension for this assignment
*Blake Moore
* Dec 5 2022
*/


void minHeap::siftUp(int pos)
{
    int size = heap.size();
    int parent = floor((pos -1)/2);

    if(pos < size)
    {
        while(pos < size && heap[parent] > heap[pos])
        {
            swap(heap[parent], heap[pos]);
            pos = parent;
            parent = floor((pos -1)/2);
        }
    }
    
}
void minHeap::siftDown(int pos)
{
    int size = heap.size();
    unsigned L = 2*pos + 1;
    unsigned R = 2*pos + 2;
    int tmp;
    //looking for smallest value 
    //and statement is to keep it from going out of scope
    if(heap[L] < heap[pos] && L < size)
    {
        tmp = L;
    }
    if(heap[R] < heap[tmp] && R < size)
    {
        tmp = R;
    }

    //recursion portion
    if(tmp != pos)
    {
        //if tmp is not at pos, then we gotta swap
        swap(heap.at(pos), heap.at(tmp));

        //recursion call
        siftDown(tmp);
    }

}
void minHeap::insert(int val)
{
    heap.push_back(val);
    //then its needed to sift up
    //getting size because i like having it as avariable rather than
    //a function call
    int size = heap.size();
    siftUp(size - 1);
}

//heap builder
minHeap::minHeap(vector<int> data)
{
    //goes through the vector and adds it to the heap
    int size = data.size();
    for(int i = 0; i < size; i++)
    {
        insert(data[i]);
    }
}

//removal

int minHeap::removeMin()
{
    int size = heap.size();
    int tmp;
    //this is to catch the special case of size 1 and size 0
    if(size == 1)
    {
        //save value
        tmp = heap[0];
        //remove value
        heap.pop_back();
        return tmp;
    }
    else if(size == 0)
    {
        //kinda confused, since there is no value in it, does it still
        //need to return something?
        return 0;
    }
    //save root
    tmp = heap[0];
    //update the heap
    heap[0] = heap.back();
    //remove the value
    heap.pop_back();
    //then sift down
    siftDown(0);
    return tmp;
}