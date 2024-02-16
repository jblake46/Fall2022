/*
 * Name: Blake Moore
 * Date Submitted: Oct 25 
 * Lab Section: 1
 * Assignment Name: Closest Pair
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename);
double closestPair(string filename)
{
  ifstream inputFile;
  int sizeOfFile;
  //creating variable for distance, and min distance
  double distance, minDistance;
  //intializing min distance to prevent a bug later on 
  distance = 1.0;
  //variable to assign which spatial hash the coordinate goes
  int xHashLocation, yHashLocation;
  inputFile.open(filename);
  //reading in size of file
  inputFile >> sizeOfFile;
  //calculating b
  //delcares b as an int so it will automatically round for me
  int b = sqrt(sizeOfFile);


  //creating the table
  vector<vector<vector<point>>> table(b, vector<vector<point>>(b));
  //creating variables to store the data into
  double x, y;

  //loop to populate the table 
  for(int i = 0; i < sizeOfFile; i++)
  {
    point filePoints;
    //reading in the points of the variable
    inputFile >> filePoints.x >> filePoints.y;
    xHashLocation = filePoints.x * b;
    yHashLocation = filePoints.y * b;

    //adding it to table
    table[xHashLocation][yHashLocation].push_back(filePoints);
    //cout << xHashLocation << " "<< yHashLocation << " x coord " << filePoints.x << " y coord " << filePoints.y << endl;
  }
  //done reading the file, so lets close it
  inputFile.close();

  //here comes the fun part, time to loop through each bucket :)
  //and check around it
  //x coordinate
  for(int i = 0; i < table.size(); i++)
  {
    //y coordinate
    for(int j = 0; j < table[i].size(); j++)
    {
      //whats actually inside each coordinate
      //so we assign the point it is at
      for(int k = 0; k < table[i][j].size(); k++)
      {
        point current = table[i][j][k];
        //loop through current bucket, find the smallest distance
        for(int currentBucket = 0; currentBucket < table[i][j].size(); currentBucket++)
        {
          //calculating the distance at this point
          point nextPoint = table[i][j][currentBucket];
          //doing some prelimenary math operations to make the code look cleaner
          double xDifference = current.x - nextPoint.x;
          double yDifference = current.y - nextPoint.y;

          //calculating x1 - x2 squared, and y1-y2 square
          double xSquared = pow(xDifference,2);
          double ySquared = pow(yDifference,2);
          //calculating distance

          minDistance = sqrt(xSquared + ySquared);
          
          if(minDistance < distance && minDistance)
          {
            distance = minDistance;
          }
        }
        //checking above the current bucket
        if((j-1) > -1)
        {
            
            for(int upper = 0; upper < table[i][j-1].size(); upper++)
            {
              
              point nextPoint = table[i][j-1][upper];
              //doing some prelimenary math operations to make the code look cleaner
              double xDifference = current.x - nextPoint.x;
              double yDifference = current.y - nextPoint.y;

              //calculating x1 - x2 squared, and y1-y2 square
              double xSquared = pow(xDifference,2);
              double ySquared = pow(yDifference,2);
              //calculating distance
              
              minDistance = sqrt(xSquared + ySquared);
              if(minDistance < distance)
              {
                distance = minDistance;
              }
            }
        }

         //checking upper left 
        if((j-1) >= 0 && (i-1) >= 0)
        {
            
            for(int upperLeft = 0; upperLeft < table[i-1][j-1].size(); upperLeft++)
            {
                point nextPoint = table[i-1][j-1][upperLeft];
                //doing some prelimenary math operations to make the code look cleaner
                double xDifference = current.x - nextPoint.x;
                double yDifference = current.y - nextPoint.y;

                //calculating x1 - x2 squared, and y1-y2 square
                double xSquared = pow(xDifference,2);
                double ySquared = pow(yDifference,2);
                //calculating distance
              
                minDistance = sqrt(xSquared + ySquared);
                if(minDistance < distance )
                {
                    distance = minDistance;
                }
            }
        }
        //checking upper right
        if((j-1) > -1 && i+1 < table.size())
        {
            for(int upperRight = 0; upperRight < table[i+1][j-1].size(); upperRight++)
            {
                point nextPoint = table[i+1][j-1][upperRight];
                //doing some prelimenary math operations to make the code look cleaner
                double xDifference = current.x - nextPoint.x;
                double yDifference = current.y - nextPoint.y;

                //calculating x1 - x2 squared, and y1-y2 square
                double xSquared = pow(xDifference,2);
                double ySquared = pow(yDifference,2);
                //calculating distance
              
                minDistance = sqrt(xSquared + ySquared);
                if(minDistance < distance)
                {
                  distance = minDistance;
                }
            }
        }
        //checking below
        if((j+1) < table.size())
        {
            for(int below =0; below < table[i][j+1].size(); below++)
            {
                    point nextPoint = table[i][j+1][below];
                    //doing some prelimenary math operations to make the code look cleaner
                    double xDifference = current.x - nextPoint.x;
                    double yDifference = current.y - nextPoint.y;
                    //calculating x1 - x2 squared, and y1-y2 square
                    double xSquared = pow(xDifference,2);
                    double ySquared = pow(yDifference,2);
                    //calculating distance
                    minDistance = sqrt(xSquared + ySquared);
                    if(minDistance < distance)
                    {
                        distance = minDistance;
                    }
            }
        }
        //checking below left 
        if((i-1) > -1 && (j+1) < table.size())
        {
            for(int belowLeft = 0; belowLeft < table[i-1][j+1].size(); belowLeft++)
            {
                point nextPoint = table[i-1][j+1][belowLeft];
                //doing some prelimenary math operations to make the code look cleaner
                double xDifference = current.x - nextPoint.x;
                double yDifference = current.y - nextPoint.y;

                //calculating x1 - x2 squared, and y1-y2 square
                double xSquared = pow(xDifference,2);
                double ySquared = pow(yDifference,2);
                //calculating distance
              
                minDistance = sqrt(xSquared + ySquared);
                if(minDistance < distance)
                {
                  distance = minDistance;
                }
            }
        }
        //checking below right 
        if((i+1) < table.size() && (j+1) < table.size())
        {
            for(int belowRight = 0; belowRight < table[i+1][j+1].size(); belowRight++)
            {
                point nextPoint = table[i+1][j+1][belowRight];
                //doing some prelimenary math operations to make the code look cleaner
                double xDifference = current.x - nextPoint.x;
                double yDifference = current.y - nextPoint.y;

                //calculating x1 - x2 squared, and y1-y2 square
                double xSquared = pow(xDifference,2);
                double ySquared = pow(yDifference,2);
                //calculating distance
              
                minDistance = sqrt(xSquared + ySquared);
                if(minDistance < distance)
                {
                  distance = minDistance;
                }
            }
        }
        //checking to the right
        if((i+1) < table.size())
        {

            for(int right = 0; right < table[i+1][j].size(); right++)
            {
                point nextPoint = table[i+1][j][right];
                //doing some prelimenary math operations to make the code look cleaner
                double xDifference = current.x - nextPoint.x;
                double yDifference = current.y - nextPoint.y;

                //calculating x1 - x2 squared, and y1-y2 square
                double xSquared = pow(xDifference,2);
                double ySquared = pow(yDifference,2);
                //calculating distance
              
                minDistance = sqrt(xSquared + ySquared);
                if(minDistance < distance)
                {
                  distance = minDistance;
                }
            }
        }
        //checking to the left   
        if((i-1) > -1)
        {

            for(int left = 0; left < table[i-1][j].size(); left++)
            {
                point nextPoint = table[i-1][j][left];
                //doing some prelimenary math operations to make the code look cleaner
                double xDifference = current.x - nextPoint.x;
                double yDifference = current.y - nextPoint.y;

                //calculating x1 - x2 squared, and y1-y2 square
                double xSquared = pow(xDifference,2);
                double ySquared = pow(yDifference,2);
                //calculating distance
              
                minDistance = sqrt(xSquared + ySquared);
                if(minDistance < distance)
                {
                  distance = minDistance;
                }
            }
        }
      }    
    }
    }
    return distance;    
}






/*
int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}*/