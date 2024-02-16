#include "List.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int main()
{   
    
    //cout <<"here" << endl;
     List<int> list1;
     //cout<<"not gonna make it here" << endl;
    List<int> listTest;
        if(list1.empty())
    {
        cout <<"THIS BITCH EMPTY" << endl;
    }
    
     for (int i=1, j = 1; i <= 10; i++){


         j = -2*j;
        list1.insertEnd(j);
    }
    //list1.insertEnd(-9);
    if(!list1.empty())
    {
        cout <<"THIS BITCH ISNT EMPTY" << endl;
    }
    list1.print("name");
    cout << list1.getLast() << endl;
    list1.print("test ");

    for(int i = 1, j = 1; i <= 10; i++){
        j = -2 * j;
        listTest.insertStart(j);
    }
    listTest.print("urmom");

    //cout<< "getat5 should be -32: " << list1.getAt() << endl;
}