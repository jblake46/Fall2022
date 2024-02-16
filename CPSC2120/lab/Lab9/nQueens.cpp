/*
 * Name: Blake Moore
 * Date Submitted: 11/21/2022
 * Lab Section: 1, 2:30 - 3:20 
 * Assignment Name: nQueens
 */

#include <iostream>
#include <vector>
//bad practice, but this is the only way i could get each function to be able to access and change 
//the number of solutions, sorry for the bad programming style
//static int solutions = 0;

using namespace std;

bool safePos(int n, int row, int col, vector<vector<int>> &board)
{
    //this just checks current row, up left diag and down left diag
    for(int i = 0; i < col; i++)
    {
        if(board[row][i])
        {
            return false;
        }
    }

    for(int i = row, j = col; i >= 0 && j>=0; i--, j--)
    {
        if(board[i][j])
        {
            return false;
        }
    }
    for(int i = row, j = col; i < n && j>=0; i++, j--)
    {
        if(board[i][j])
        {
            return false;
        }
    }    
    return true;
}

//helper function that sees if the queen can be placed on the board/ vector table
bool nQueenHelper(vector<vector<int>> &board, int n, int col, int *solutions)
{
    //base case or best case
    bool tmpBool = false;
    if(col == n)
    {
        (*solutions)++;
    }

    //try to place queen
    for(int i = 0; i < n; i++)
    {
        if(safePos(n, i, col, board))
        {
            //place queen
            board[i][col] = 1;
            if(nQueenHelper(board, n, col+1, solutions) || tmpBool)
            {
                tmpBool = true;
            }
            //remove queen
            board[i][col] = 0;
        }
    }
    return tmpBool;
    
}

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n)
{

    //Implement int nQueens(int n)
    //Feel free to implement any recursive helper functions
   
   //2 dimension for vector
   //intialized to all 0's
    vector<int> r(n,0);
    //creating 2d vector and populating it
    vector<vector<int>> tableSolutions(n,r);
    int solutions = 0;
    //first call is at 0 to cover the first col
    //recursion should iterate from there
    nQueenHelper(tableSolutions,  n, 0, &solutions);

    return solutions;

}

/*
int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}
*/