/* Blake Moore
* Dec 13th 2022
* 2120 with Ran Xu
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
unordered_map<string, vector<string>> neighbors;
unordered_map<string, string> bfsPred;
unordered_map<string, int> bfsDist;

//Implement breadth-first search, refer to Lab 10

void breadthSearch(string node)
{
  queue<string> needsVisit;
  needsVisit.push(node);
  bfsDist[node] = 0;


  if(needsVisit.empty())
  {
    //do nothing
  }
  else
  {
    while(!needsVisit.empty())
    {
      //create a "current" node to keep track of what 
      //is at the front of needsVisit
      string current = needsVisit.front();
      //removing element 
      needsVisit.pop();
      //using auto because i didnt exactly know how to 
      //iterate through the loop
      for(string n: neighbors[current])
      {
        int compareVar = bfsDist.count(n);
        if(compareVar == 0)
        {
          needsVisit.push(n);
          bfsDist[n] = 1+ bfsDist[current];
          bfsPred[n] = current;
        }
      }

    }
  }
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
  //taking in file ptr
  ifstream input("wordlist05.txt");
  if(!input.is_open())
  {
    //used this for debugging purposes
   // cout << "cannot open wordlist05.txt" << endl;
   //i had it as a if else statement, i would change it
   //but im scared of breaking it 
  }
  else if(input.is_open())
  {
    //this is to add the words from wordlist to the 
    string tmp;
    
    //gets the input from the file
    while(input >> tmp)
    {
      V.push_back(tmp);
    }
  }

  //is V emptty?
  if(V.empty())
  {
    //once again, this was to help debug
    //so sorry in advance, im just scared of messing up the program
    //bc i finall gout it to work
    cout << "V is empty" << endl;
  }
  else
  {
    for(string iterator: V)
    {
      //adding parts to the neighbor

      //this creates a list of neighbors for each element in V
      neighbors[iterator] = vector<string>();
      
      for(int i = 0; i < iterator.size(); i++)
      {
        string tmp = iterator;
        //looping through the alphabet
        for(char character = 'a'; character <= 'z'; character++)
        {
          //if the letter is not at the specific element of the iterator
          //reassign it
          if(character != tmp[i])
          {
            tmp[i] = character;
            //checking if the length is the same as the tmp
            int iterSize = iterator.length();
            int tmpWrdSize = tmp.length();
            if(iterSize == tmpWrdSize)
            {
              neighbors[iterator].push_back(tmp);
            } 
          }

        }
      }
    }
  }
  //call breadthsearch
  breadthSearch(s);

  //clearing p
  p.clear();
  string currentTarget = t;
  while(currentTarget != s && currentTarget.size() != 0)
  {
    p.push_back(currentTarget);
    currentTarget = bfsPred[currentTarget];
  }
  //updating size
  if(currentTarget.size() == 0)
  {
    steps = 0;
  }
  else
  {
    p.push_back(s);
    //reverse it
    reverse(p.begin(), p.end());

    //updated steps
    steps = p.size() -1;


  }
}




int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
