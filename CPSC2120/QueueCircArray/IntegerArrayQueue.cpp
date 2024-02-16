#include "IntegerArrayQueue.h"

bool IntegerArrayQueue::enqueue(int value)
{
    //returns false if array is full
    //returns true if its not
    if(front != back)
    {
        //gives the array at front the value of value, then goes 
        //to the next element
        array[front] = value;
        front ++;
        return true;
    }
    else
    {
        //returns false if the array is full (when front == back)
        return false;
    }

}

int IntegerArrayQueue::dequeue()
{   //to deque all values in the queue must be 0
    int tmp;
    if(front == 0)
    {
        //returns 0 if array is empty
        if(array[front] == 0)
        {
            return 0;
        }
        else 
        {
            tmp = array[front];
            array[front] = 0;
            return tmp;
        }
    }
    else
    {
        //iterates through the array backwards
        front --;
        tmp = array[front];
        array[front] = 0;

        //returning the value as stated in the instructions
        return tmp;
    }
}