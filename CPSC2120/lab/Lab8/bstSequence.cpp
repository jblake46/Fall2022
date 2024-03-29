/*
 * Name: Blake Moore
 * Date Submitted: Nov 14
 * Lab Section: 1, 2:30 - 3:20 section
 * Assignment Name: best Sequence
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "bstSequence.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

/*
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}
*/

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
  int rank = 0;
  //checking a tree exists
  if(T != nullptr)
  {
    //checking if there is anything on the left branch
    if(T->left == nullptr)
    {
      rank = 0;
    }
    //if there is, rank is set to the left->size
    //which gives us its rank
    else
    {
      rank = T->left->size;
    }
    if(r > rank)
    {
      int tmp = r - rank - 1;
      //recursive call to get closer to the intended rank
      T->right = insert(T->right, v, tmp);
    }
    else
    {
      T->left = insert(T->left, v, r);
    }
    //update size of tree
    fix_size(T);
  }
  else
  { 
    Node* createdNode = new Node(v);
    return createdNode;
  }
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
  //Implement void split(Node *T, int r, Node **L, Node **R)
  //same functions as before right?
  //it is not
  *R = nullptr;
  *L = nullptr;
  int rank = 0;
  int tmpRank;
  vector<int> transversalTable = inorder_traversal(T);
  if(T != nullptr)
  {
    //get rank
    rank = T->left ? T->left->size : 0;
  }
  //if T is null, you cant split it
  else
  {
    return;
  }
  //checking to see which direction it needs to go
  //since r is greater, it is right side
  if(r > rank)
  {
    tmpRank = r - rank -1;
    split(T->right, tmpRank, L, R);
    T->right = *L;
    *L = T;
  }
  //if right fails, means u gotta go left
  else
  {
      split(T->left, r, L, R);
      T->left = *R;
      *R = T;
  }

  //update size
  fix_size(T);
  
}

// insert value v at rank r
Node *insert_random(Node *T, int v, int r)
{
  // If (v,r) is the Nth node inserted into T, then:
  // with probability 1/N, insert (v,r) at the root of T
  // otherwise, insert_random (v,r) recursively left or right of the root of T
  //Implement Node *insert_random(Node *T, int v, int r)
  int rank = 0;
  Node *tmp;
  int tmpRank;
  int prob;
  //making sure T is not null
  if(T == nullptr)
  {
    T = new Node(v);
    return T;
  }
  else if((rand() % (T->size + 1)) == 0)
  {
    tmp = new Node(v);
    split(T, r, &tmp->left, &tmp->right);
    fix_size(tmp);
    return tmp;
  }
  else
  {
    //checking if left part is a nullptr
    if(T->left == nullptr)
    {
      rank = 0;
    }
    else
    {
      rank = T->left->size;
    }
    //if r is > rank, deal with right side
    if( r > rank)
    {
      //tmp variable to hold a int to make it look cleaner
      int tmp= r -rank - 1;
      T->right = insert_random(T->right, v, tmp);
    }
    //dealing with left side
    else
    {
      T->left = insert_random(T->left, v, r);
    }
  }
  //update size
  fix_size(T);
  return T;
}

// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n)
{
  Node *T = nullptr;
  
  // start by inserting the first team
  T = insert_random(T, 0, 0);
  // now insert the other teams...
  for (int i=1; i<n; i++) {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key)) // can we insert at beginning?
      T = insert_random(T, i, 0);
    else if (did_x_beat_y(select(T,T->size-1)->key, i)) // can we insert at end?
	    T = insert_random(T, i, T->size);
    else {
      int start = 0;
      int end = T->size -1;

      while((start + 1 )!= (end))
      {
        int mid = (start + end)/2;
        if(did_x_beat_y(select(T, mid)->key, i))
        {
          start = mid;
        }
        else
        {
          end = mid;
        }
      }
      T = insert_random(T, i, end);
    }
  }
  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

/*
int main(void)
{
  vector<int> inorder;
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
    
  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!

  Node *S = order_n_teams(N);
  
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
        //inorder=inorder_traversal(S);
        //printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}
*/
