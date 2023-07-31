#include <vector>
#include "JBlock.h"

using namespace std;

void JBlock::rotateBlock(vector<vector<bool>>& grid) 
{
    switch (rotation)
    {
    case Rotation::BOTTOM:
        if (blockPosition[0].x + 2 < grid.size() && blockPosition[0].y >= 0 &&
            blockPosition[1].x + 1 < grid.size() && blockPosition[1].y - 1 >= 0 &&
            blockPosition[3].x - 1 >= 0 && blockPosition[3].y + 1 < grid[0].size() &&
            grid[blockPosition[0].x + 2][blockPosition[0].y] == 0 &&
            grid[blockPosition[1].x + 1][blockPosition[1].y - 1] == 0 &&
            grid[blockPosition[3].x - 1][blockPosition[3].y + 1] == 0)
        {
            blockPosition[0].x += 2;
            blockPosition[1].x += 1;
            blockPosition[1].y -= 1;
            blockPosition[3].x -= 1;
            blockPosition[3].y += 1;

            rotation = Rotation::RIGHT;
        }
        break;
    case Rotation::RIGHT:
        if (blockPosition[0].x < grid.size() && blockPosition[0].y + 2 < grid[0].size() &&
            blockPosition[1].x + 1 < grid.size() && blockPosition[1].y + 1 < grid[0].size() &&
            blockPosition[3].x - 1 >= 0 && blockPosition[3].y - 1 >= 0 &&
            grid[blockPosition[0].x][blockPosition[0].y + 2] == 0 &&
            grid[blockPosition[1].x + 1][blockPosition[1].y + 1] == 0 &&
            grid[blockPosition[3].x - 1][blockPosition[3].y - 1] == 0)
        {
            blockPosition[0].y += 2;
            blockPosition[1].x += 1;
            blockPosition[1].y += 1;
            blockPosition[3].x -= 1;
            blockPosition[3].y -= 1;

            rotation = Rotation::TOP;
        }
        break;
    case Rotation::TOP:
        if (blockPosition[0].x - 2 >= 0 && blockPosition[0].y < grid[0].size() &&
            blockPosition[1].x - 1 >= 0 && blockPosition[1].y + 1 < grid[0].size() &&
            blockPosition[3].x + 1 < grid.size() && blockPosition[3].y - 1 >= 0 &&
            grid[blockPosition[0].x - 2][blockPosition[0].y] == 0 &&
            grid[blockPosition[1].x - 1][blockPosition[1].y + 1] == 0 &&
            grid[blockPosition[3].x + 1][blockPosition[3].y - 1] == 0)
        {
            blockPosition[0].x -= 2;
            blockPosition[1].x -= 1;
            blockPosition[1].y += 1;
            blockPosition[3].x += 1;
            blockPosition[3].y -= 1;

            rotation = Rotation::LEFT;
        }
        break;
    case Rotation::LEFT:
        if (blockPosition[0].x >= 0 && blockPosition[0].y - 2 >= 0 &&
            blockPosition[1].x - 1 >= 0 && blockPosition[1].y - 1 >= 0 &&
            blockPosition[3].x + 1 < grid.size() && blockPosition[3].y + 1 < grid[0].size() &&
            grid[blockPosition[0].x][blockPosition[0].y - 2] == 0 &&
            grid[blockPosition[1].x - 1][blockPosition[1].y - 1] == 0 &&
            grid[blockPosition[3].x + 1][blockPosition[3].y + 1] == 0)
        {
            blockPosition[0].y -= 2;
            blockPosition[1].x -= 1;
            blockPosition[1].y -= 1;
            blockPosition[3].x += 1;
            blockPosition[3].y += 1;

            rotation = Rotation::BOTTOM;
        }
        break;
    default:
        break;
    }
}
