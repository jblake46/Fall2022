/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below
Grouping::Grouping(string files)
{
    int row, col;
    row = 0;
    col = row;
    vector<GridSquare> groupMap;
   
    string txtHolder;
    int maxGridSize = 10;
    //opens and preps file for reading in
    ifstream file(files);

    // moves the grid from the file to the program
    while(getline(file, txtHolder))
    {   
        row = 0;
        for(int i = 0; i < maxGridSize; i++)
        {
            if(txtHolder[i] == '.')
            {
                grid[row][col] = 0;
            }
            else
            {
                grid[row][col] = 1;
            }
            col++;
        }
        row ++;
    }
    cout << "Displaying Grid" << endl;
    for(int i = 0; i < maxGridSize; i++)
    {
        for(int j = 0; j < maxGridSize; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Grid is Filled" << endl;


    //going through the grid and finding any pairs
    for(row = 0; row < maxGridSize; row++)
    {
        for(col = 0; col < maxGridSize; col++)
        {
            groupMap.clear();
            
            if(grid[row][col] == 1)
            {   
                
                groupMap = findGroup(row, col, groupMap);   

            }
            if(groupMap.size() > 0)
            {
                groups.push_back(groupMap);
            }
           
        }
    }    
}   


//this helper function sees if the group has already been found
bool Grouping::findGroupHelper(int row, int col, vector<GridSquare> groupMap)
{
    for(int i = 0; groups.size(); i++)
    {
        for(int j = 0; groups[i].size(); j++)
        {
            if(groups[i][j].getRow() == row && groups[i][j].getCol() == col)
            {
                return true;
            }
        }
    }

    for(int i = 0; i < groupMap.size(); i++)
    {
        if(groupMap[i].getRow() == row && groupMap[i].getCol() == col)
        {
            return true;
        }
    }
    return false;
}

//findGroup function iterrates through the grid and sees if there are any groups
vector<GridSquare> Grouping::findGroup(int row, int col, vector<GridSquare> groupMap)
{

    if(grid[row][col] == 1 && !findGroupHelper(row,col,groupMap))
    {
        GridSquare tmp(row,col);
        groupMap.push_back(tmp);

        //begin to search the sides
        //seaching above
        //added if statements to keep the grouping in bounds
        if(row + 1 < 8)
        {
            if(grid[row+1][col] == 1)
            {
            
                if(findGroupHelper(row+1, col, groupMap))
                {
                    groupMap = findGroup(row +1, col, groupMap);
                }
            }
        }
        //searching below
        if(row - 1 >= 2)
        {
            if(grid[row-1][col] == 1)
            {
                if(findGroupHelper(row-1, col, groupMap))
                {
                    groupMap = findGroup(row -1, col, groupMap);
                }
            }
        }
        //searching right
        if(col + 1 < 8)
        {
            
            if(grid[row][col+1] == 1)
            {
               if(findGroupHelper(row, col+1, groupMap))
                {
                    groupMap = findGroup(row, col+1, groupMap);
                }
            }
        }

        if(col - 1 >= 2)
        {
        //searching left
            if(grid[row][col-1] == 1)
            {
                if(findGroupHelper(row, col-1, groupMap))
                {
                    groupMap = findGroup(row, col-1, groupMap);
                }
            } 
        }              
    }
    return groupMap;
}



//Simple main function to test Grouping
//Be sure to comment out main() before submitting

int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}
//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}