#ifndef _ASTAR_H
#define _ASTAR_H

#include <bits/stdc++.h>
#include <vector>

#define ROW 19
#define COL 25

typedef std::pair<int, int> Pair;

typedef std::pair<double, std::pair<int, int>> pPair;

struct cell
{
    int parent_i, parent_j;
    double f, g, h;
};

class AStar
{
private:
    std::stack<Pair> mPath;
private:
    bool isValid(int row, int col);
    bool isUnBlocked(std::vector<std::vector<int>> grid, int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void tracePath(cell cellDetails[][COL], Pair dest);

public:
    void aStarSearch(std::vector<std::vector<int>> grid, Pair src, Pair dest);
    Pair getCell();
};

#endif //_ASTAR_H