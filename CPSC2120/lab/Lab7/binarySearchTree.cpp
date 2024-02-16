/*
 * Name: Blake Moore
 * Date Submitted: Nov 9
 * Lab Section: 2:30 - 3:30 section, I think its 1 
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
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

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
  //creating iterator 
  Node* iterator = T; 
 
  while(iterator != nullptr)
  {
     //to the left
    if(k < iterator->key)
    {
      iterator = iterator->left;
    }
    //to the right
    else if(k > iterator->key)
    {
      iterator = iterator->right;
    }
    //k is the key so
    else if(k == iterator->key)
    {
      return iterator;
    }
  }
  //if all cases above fail, return a null ptr
  return nullptr;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);
  //creating vector for going through the tree
  vector<int> transversal = inorder_traversal(T);
  int key = transversal[r];
 
  return find(T,key);

}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  
  //checking if L is null or if R is null
  if(R==nullptr || L == nullptr)
  {
    //if both are null, return null
    return nullptr;
  }
  //if r is null return L
  else if(R == nullptr)
  {
    return L;
  }
  else if(L == nullptr)
  {
    return R;
  }
  else
  {
    //creating probabilities
    int sizeOfBoth = L->size + R->size;
    int probDecider = rand() % (sizeOfBoth/L->size);

    if(probDecider != 0)
    {
      //using R as root in a inorder transversal
      vector<int> table = inorder_traversal(L);

      for(int i = 0; i < L->size; i++)
      {
        //inserting other root values to R root
        R = insert(R, table[i]);
        //redefining R's size
        fix_size(R);
      }
      return R;
    }
    else
    {
      //using L as root in a inorder transversal
      vector<int> table = inorder_traversal(R);
      for(int i = 0; i < R->size; i++)
      {
        //inserting other root values to L root
        L = insert(L, table[i]);
        //redefining R's size
        fix_size(L);
      }
      return L;      
    }
  }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);
  

  //remove right
  if(k > T->key)
  {
    Node* tmp = T->right;
    T->right = remove(tmp, k);
    //since removing, decrement
    T->size--;
  }
  //remove left
  else if( k < T->key)
  {
    T->left = remove(T->left, k);
    //since removing, decrement
    T->size--;
  }
  else
  {
    //if both sides exist, combine
    if((T->right != nullptr) && (T->left != nullptr))
    {
      Node* tmp;
      tmp = join(T->left, T->right);
      delete T;
      return tmp;
    }
    //no right branch, go to left
    else if(T->right == nullptr)
    {
      Node* tmp;
      tmp = T->left;
      delete T;
      return tmp;
    }
    //do the same thing but for the left branch
    else if(T->left == nullptr)
    {
      Node* tmp;
      tmp = T->right;
      delete T;
      return tmp;
    }

  }
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  //intializing R and L 
  *R = nullptr;
  *L = nullptr;
  //create vector to go through tree
  vector<int> transversal = inorder_traversal(T);
  for(int i = 0; i < transversal.size(); i ++)
  {
    if(transversal[i] > k)
    {
      //if key is greater than k, add to right
      *R = insert(*R, transversal[i]);
    }
    //otherwise key will be less than, add to left
    else
    {
      *L = insert(*L, transversal[i]);
    }
  }
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  
  //seeing if T is null
  if(T == nullptr)
  {
    T = new Node(k);
    return T;
  }
  //creating probability
  int prob = rand() % (T->size + 1);
  if(prob != 0)
  {
  
    if(k > T->key)
    {
      //greater than, so insert on the right
      T->right = insert_random(T->right, k);
    }
    else
    {
      //less than so insert on left
      T->left = insert_random(T->left, k);
  
    }
  }
  else if (prob == 0)
  {
    //creating tmp node with key == k
    Node* tmp = new Node(k);
    //splitting tree
    Node* L = nullptr;
    Node* R = nullptr;
    split(T, k, &L, &R);

    tmp->left = nullptr;
    tmp->right = nullptr;
    //updating size
    fix_size(tmp);
    T = tmp;
    //return tmp;
  }
  T->size++;
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
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    //Node *result = select(T, i);
    //if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}
*/
