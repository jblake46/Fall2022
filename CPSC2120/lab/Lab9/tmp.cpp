/*
 * Name: David Croft
 * Date Submitted: 4/12/21
 * Lab Section: 3
 * Assignment Name: Lab 9 - Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

bool validState(vector<int>spaceRow, vector<int>spaceColumn, vector<vector<int>> board){
    vector<int> rCount(board.size(), 0);
    vector<int> cCount(board.size(), 0);
    for(int i = 0; i < spaceRow.size(); i++){
        rCount[spaceRow[i]]++;
        cCount[spaceColumn[i]]++;
        if(rCount[spaceRow[i]] > 1 || cCount[spaceColumn[i]] > 1)
            return false;
        for(int j = 0; j < i; j++){
            double diagonal = (spaceRow[i] - spaceRow[j])/(double)(spaceColumn[i] - spaceColumn[j]);
            if(diagonal == 1 || diagonal == -1)
                return false;
        }
    }
    return true;
}

int checkRow(int r, vector<int>spaceRow, vector<int>spaceColumn, vector<vector<int>> board){
    if(!validState(spaceRow, spaceColumn, board))
        return 0;
    else if(r == board.size())
        return 1;
    else{
        int count = 0;
        int width = board.size();
        if(r == 0)
            width = (width + 1) / 2;
        for(int i = 0; i < width; i++){
            board[r][i] = 1;
            spaceRow.push_back(r);
            spaceColumn.push_back(i);
            if(r == 0 && i < board.size() / 2)
                count += 2* checkRow(r+1, spaceRow, spaceColumn, board);
            else
                count += checkRow(r+1, spaceRow, spaceColumn, board);
            spaceRow.pop_back();
            spaceColumn.pop_back();
            board[r][i] = 0;
        }
        return count;
    }
}

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n)
{
    vector<int> row(n,0);
    vector<vector<int>> board(n, row);
    vector<int> spaceRow;
    vector<int> spaceColumn;
    return checkRow(0, spaceRow, spaceColumn, board);
}

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
