#include "Tetromino.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


void Tetromino::translateBlockHorizontally(vector<vector<bool>>& grid, int direction)
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
        grid[blockPosition[0].x + direction][blockPosition[0].y] == false &&
        grid[blockPosition[1].x + direction][blockPosition[1].y] == false &&
        grid[blockPosition[2].x + direction][blockPosition[2].y] == false &&
        grid[blockPosition[3].x + direction][blockPosition[3].y] == false
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

bool Tetromino::canTranslateDownwards(vector<vector<bool>>& grid)
{
    for (auto positions : blockPosition)
    {
        if (grid[positions.x][positions.y + 1] != 0)
            return false;
    }

    return true;
}

bool Tetromino::canFitOnGrid(const vector<vector<bool>>& grid)
{
    for (const auto& position : startingPositions)
    {
        int x = position.x;
        int y = position.y;

        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
            return false;

        if (grid[x][y] == true)
            return false;
    }

    return true;
}
