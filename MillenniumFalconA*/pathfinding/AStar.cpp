#include "AStar.h"

bool AStar::isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool AStar::isUnBlocked(std::vector<std::vector<int>> grid, int row, int col)
{
    if (grid[row][col] != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AStar::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
    {
        return true;
    }
    else
    {
        return false;
    }

}

double AStar::calculateHValue(int row, int col, Pair dest)
{
    return (sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

void AStar::tracePath(cell cellDetails[][COL], Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        mPath.push (std::make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    mPath.push (std::make_pair (row, col));

    /*while (!mPath.empty())
    {
        std::pair<int,int> p = mPath.top();
        mPath.pop();
        std::cout << "-> (" << p.first << ", " << p.second << ")" << std::endl;
    }*/
}

Pair AStar::getCell()
{
    std::stack<Pair> temp = mPath;
    temp.pop();
    return temp.top();
}

void AStar::aStarSearch(std::vector<std::vector<int>> grid, Pair src, Pair dest)
{
    if (!isValid (src.first, src.second))
    {
        //std::cout << "Source is invalid" << src.first << std::endl;
        return;
    }

    if (!isValid (dest.first, dest.second))
    {
        //std::cout << "Destination is invalid" << std::endl;
        return;
    }

    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second))
    {
        //std::cout << "Source or the destination is blocked" << std::endl;
        return;
    }

    if (isDestination(src.first, src.second, dest))
    {
        //std::cout << "We are already at the destination" << std::endl;
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof (closedList));

    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    std::set<pPair> openList;

    openList.insert(std::make_pair (0.0, std::make_pair (i, j)));

    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();

        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        /*
         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)*/

        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------
        if (isValid(i-1, j))
        {
            if (isDestination(i-1, j, dest))
            {
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i-1][j] && isUnBlocked(grid, i-1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j].f == FLT_MAX ||
                    cellDetails[i-1][j].f > fNew)
                {
                    openList.insert(std::make_pair(fNew, std::make_pair(i-1, j)));

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------
        if (isValid(i+1, j))
        {
            if (isDestination(i+1, j, dest))
            {
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i+1][j] && isUnBlocked(grid, i+1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i+1][j].f == FLT_MAX ||
                    cellDetails[i+1][j].f > fNew)
                {
                    openList.insert(std::make_pair (fNew, std::make_pair (i+1, j)));

                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------
        if (isValid (i, j+1))
        {
            if (isDestination(i, j+1, dest))
            {
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i][j+1] && isUnBlocked (grid, i, j+1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j+1].f == FLT_MAX ||
                    cellDetails[i][j+1].f > fNew)
                {
                    openList.insert(std::make_pair(fNew, std::make_pair (i, j+1)));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------
        if (isValid(i, j-1))
        {
            if (isDestination(i, j-1, dest))
            {
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i][j-1] && isUnBlocked(grid, i, j-1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j-1].f == FLT_MAX ||
                    cellDetails[i][j-1].f > fNew)
                {
                    openList.insert(std::make_pair (fNew, std::make_pair (i, j-1)));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
    }

    if (foundDest == false)
        std::cout << "Failed to find the Destination Cell" << std::endl;
}
