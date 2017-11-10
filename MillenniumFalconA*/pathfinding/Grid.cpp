#include "Grid.h"

Grid* Grid::sInstance = nullptr;

Grid* Grid::instance()
{
    if (sInstance == nullptr)
        sInstance = new Grid();

    return sInstance;
}

void Grid::release()
{
    delete sInstance;
    sInstance = nullptr;
}

Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::set_matrix_pos_astar(int x, int y)
{
    for (int i = 0; i < 19; ++i)
    {
        for (int j = 0; j < 25; ++j)
        {
            if (i == y && j == x)
            {
                mMatrix[i][j] = 0;

                if (((i + 1) < 19) && ((i - 1) > 0) && ((j - 1) > 0) && ((j + 1) < 25))
                {
                    mMatrix[i + 1][j] = 1;
                    mMatrix[i - 1][j] = 1;
                    mMatrix[i][j - 1] = 1;
                    mMatrix[i][j + 1] = 1;
                }
                else if (((i + 1) < 19) && ((i - 1) > 0) && ((j - 1) > 0))
                {
                    mMatrix[i + 1][j] = 1;
                    mMatrix[i - 1][j] = 1;
                    mMatrix[i][j - 1] = 1;
                }
                else if (((i + 1) < 19) && ((i - 1) > 0) && ((j + 1) < 25))
                {
                    mMatrix[i + 1][j] = 1;
                    mMatrix[i - 1][j] = 1;
                    mMatrix[i][j + 1] = 1;
                }
                else if (((i - 1) > 0) && ((j - 1) > 0) && ((j + 1) < 25))
                {
                    mMatrix[i - 1][j] = 1;
                    mMatrix[i][j - 1] = 1;
                    mMatrix[i][j + 1] = 1;
                }
                else if (((i + 1) < 19) && ((j - 1) > 0) && ((j + 1) < 25))
                {
                    mMatrix[i + 1][j] = 1;
                    mMatrix[i][j - 1] = 1;
                    mMatrix[i][j + 1] = 1;
                }
            }
        }
    }
}

void Grid::set_matrix_pos(int x, int y)
{
    for (int i = 0; i < 19; ++i)
    {
        for (int j = 0; j < 25; ++j)
        {
            if (i == y && j == x)
            {
                mMatrix[i][j] = 1;

                if ((i + 1) < 19)
                {
                    mMatrix[i + 1][j] = 0;
                }
            }
        }
    }
}

void Grid::print_matrix()
{
    int x = 0;
    int y = 0;

    for(x = 0 ; x < 19 ; x++) {
        printf(" ");
        for(y = 0 ; y < 25 ; y++){
            printf("%d ", mMatrix[x][y]);
        }
        printf("\n");
    }
}

std::vector<std::vector<int>> Grid::get_matrix()
{
    return mMatrix;
}

