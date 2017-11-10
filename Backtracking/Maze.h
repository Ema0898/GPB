#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>

using namespace std;

static const int ROWS = 11;
static const int COLUMNS = 24;

class Maze
{
public:
    Maze(); //default constructor
    vector<int> path;
    vector<int> getpath();
    void printMaze(); //print out maze
    void writeBlock(); //write blocks in maze
    void writeExit(); //write exit from maze
    void setStart( int row, int col ); //set start location
    char getCell( int row, int col ); //get cell contents
    void setCell( int row, int col, char val ); //set cell contents
    bool backTrack( int row, int col ); //algorithm to recursively find exit
private:
    char maze[ ROWS ][ COLUMNS ];


}; //end class Maze


#endif
