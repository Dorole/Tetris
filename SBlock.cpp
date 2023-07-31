#include <vector>
#include "SBlock.h"

using namespace std;

void SBlock::rotateBlock(vector<vector<bool>>& grid)
{
    switch (rotation)
    {
    case Rotation::BOTTOM:
        if (blockPosition[0].x + 1 < grid.size() && blockPosition[0].y - 1 >= 0 &&
            blockPosition[2].x + 1 < grid.size() && blockPosition[2].y + 1 < grid[0].size() &&
            blockPosition[3].y + 2 < grid[0].size() &&
            grid[blockPosition[0].x + 1][blockPosition[0].y - 1] == 0 &&
            grid[blockPosition[2].x + 1][blockPosition[2].y + 1] == 0 &&
            grid[blockPosition[3].x][blockPosition[3].y + 2] == 0)
        {
            blockPosition[0].x += 1;
            blockPosition[0].y -= 1;
            blockPosition[2].x += 1;
            blockPosition[2].y += 1;
            blockPosition[3].y += 2;

            rotation = Rotation::RIGHT;
        }
        break;
    case Rotation::RIGHT:
        if (blockPosition[0].x + 1 < grid.size() && blockPosition[0].y + 1 < grid[0].size() &&
            blockPosition[2].x - 1 >= 0 && blockPosition[2].y + 1 < grid[0].size() &&
            blockPosition[3].x - 2 >= 0 &&
            grid[blockPosition[0].x + 1][blockPosition[0].y + 1] == 0 &&
            grid[blockPosition[2].x - 1][blockPosition[2].y + 1] == 0 &&
            grid[blockPosition[3].x - 2][blockPosition[3].y] == 0)
        {
            blockPosition[0].x += 1;
            blockPosition[0].y += 1;
            blockPosition[2].x -= 1;
            blockPosition[2].y += 1;
            blockPosition[3].x -= 2;

            rotation = Rotation::TOP;
        }
        break;
    case Rotation::TOP:
        if (blockPosition[0].x - 1 >= 0 && blockPosition[0].y + 1 < grid[0].size() &&
            blockPosition[2].x - 1 >= 0 && blockPosition[2].y - 1 >= 0 &&
            blockPosition[3].y - 2 >= 0 &&
            grid[blockPosition[0].x - 1][blockPosition[0].y + 1] == 0 &&
            grid[blockPosition[2].x - 1][blockPosition[2].y - 1] == 0 &&
            grid[blockPosition[3].x][blockPosition[3].y - 2] == 0)
        {
            blockPosition[0].x -= 1;
            blockPosition[0].y += 1;
            blockPosition[2].x -= 1;
            blockPosition[2].y -= 1;
            blockPosition[3].y -= 2;

            rotation = Rotation::LEFT;
        }
        break;
    case Rotation::LEFT:
        if (blockPosition[0].x - 1 >= 0 && blockPosition[0].y - 1 >= 0 &&
            blockPosition[2].x + 1 < grid.size() && blockPosition[2].y - 1 >= 0 &&
            blockPosition[3].x + 2 < grid.size() &&
            grid[blockPosition[0].x - 1][blockPosition[0].y - 1] == 0 &&
            grid[blockPosition[2].x + 1][blockPosition[2].y - 1] == 0 &&
            grid[blockPosition[3].x + 2][blockPosition[3].y] == 0)
        {
            blockPosition[0].x -= 1;
            blockPosition[0].y -= 1;
            blockPosition[2].x += 1;
            blockPosition[2].y -= 1;
            blockPosition[3].x += 2;

            rotation = Rotation::BOTTOM;
        }
        break;
    default:
        break;
    }
}

