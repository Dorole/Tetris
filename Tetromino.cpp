#include "Tetromino.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GridPointData.h"

using namespace std;
using namespace sf;


void Tetromino::translateBlockHorizontally(vector<vector<GridPointData>>& grid, int direction)
{
    for (auto positions : blockPosition)
    {
        if ((positions.x + direction) < 0 || (positions.x + direction) > (grid.size() - 1))
        {
            cout << "Grid border reached" << endl;
            return;
        }
    }


    if (
        !grid[blockPosition[0].x + direction][blockPosition[0].y].occupied &&
        !grid[blockPosition[1].x + direction][blockPosition[1].y].occupied &&
        !grid[blockPosition[2].x + direction][blockPosition[2].y].occupied &&
        !grid[blockPosition[3].x + direction][blockPosition[3].y].occupied
        )
    {
        for (size_t i = 0; i < 4; i++)
        {
            (direction > 0) ? blockPosition[i].x++ : blockPosition[i].x--;
        }
    }
}

bool Tetromino::hasReachedBottomBorder(const int bottomBorderIndex)
{
    for (auto positions : blockPosition)
    {
        if (positions.y >= bottomBorderIndex)
            return true;
    }

    return false;
}

bool Tetromino::canTranslateDownwards(vector<vector<GridPointData>>& grid)
{
    for (auto positions : blockPosition)
    {
        if (grid[positions.x][positions.y + 1].occupied)
            return false;
    }

    return true;
}

bool Tetromino::canFitOnGrid(const vector<vector<GridPointData>>& grid)
{
    for (const auto& position : startingPositions)
    {
        int x = position.x;
        int y = position.y;

        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
            return false;

        if (grid[x][y].occupied)
            return false;
    }

    return true;
}
