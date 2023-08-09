#include <vector>
#include "ZBlock.h"
#include "GridPointData.h"

using namespace std;

void ZBlock::rotateBlock(vector<vector<GridPointData>>& grid)
{
    switch (rotation)
    {
    case Rotation::BOTTOM:
        if (blockPosition[0].x + 2 < grid.size() && blockPosition[0].y < grid[0].size() &&
            blockPosition[1].x + 1 < grid.size() && blockPosition[1].y + 1 < grid[0].size() &&
            blockPosition[3].x - 1 >= 0 && blockPosition[3].y + 1 < grid[0].size() &&
            !grid[blockPosition[0].x + 2][blockPosition[0].y].occupied &&
            !grid[blockPosition[1].x + 1][blockPosition[1].y + 1].occupied &&
            !grid[blockPosition[3].x - 1][blockPosition[3].y + 1].occupied)
        {
            blockPosition[0].x += 2;
            blockPosition[1].x += 1;
            blockPosition[1].y += 1;
            blockPosition[3].x -= 1;
            blockPosition[3].y += 1;

            rotation = Rotation::RIGHT;
        }
        break;
    case Rotation::RIGHT:
        if (blockPosition[0].x < grid.size() && blockPosition[0].y + 2 < grid[0].size() &&
            blockPosition[1].x - 1 >= 0 && blockPosition[1].y + 1 < grid[0].size() &&
            blockPosition[3].x - 1 >= 0 && blockPosition[3].y - 1 >= 0 &&
            !grid[blockPosition[0].x][blockPosition[0].y + 2].occupied &&
            !grid[blockPosition[1].x - 1][blockPosition[1].y + 1].occupied &&
            !grid[blockPosition[3].x - 1][blockPosition[3].y - 1].occupied)
        {
            blockPosition[0].y += 2;
            blockPosition[1].x -= 1;
            blockPosition[1].y += 1;
            blockPosition[3].x -= 1;
            blockPosition[3].y -= 1;

            rotation = Rotation::TOP;
        }
        break;
    case Rotation::TOP:
        if (blockPosition[0].x - 2 >= 0 && blockPosition[0].y < grid[0].size() &&
            blockPosition[1].x - 1 >= 0 && blockPosition[1].y - 1 >= 0 &&
            blockPosition[3].x + 1 < grid.size() && blockPosition[3].y - 1 >= 0 &&
            !grid[blockPosition[0].x - 2][blockPosition[0].y].occupied &&
            !grid[blockPosition[1].x - 1][blockPosition[1].y - 1].occupied &&
            !grid[blockPosition[3].x + 1][blockPosition[3].y - 1].occupied)
        {
            blockPosition[0].x -= 2;
            blockPosition[1].x -= 1;
            blockPosition[1].y -= 1;
            blockPosition[3].x += 1;
            blockPosition[3].y -= 1;

            rotation = Rotation::LEFT;
        }
        break;
    case Rotation::LEFT:
        if (blockPosition[0].x < grid.size() && blockPosition[0].y - 2 >= 0 &&
            blockPosition[1].x + 1 < grid.size() && blockPosition[1].y - 1 >= 0 &&
            blockPosition[3].x + 1 < grid.size() && blockPosition[3].y + 1 < grid[0].size() &&
            !grid[blockPosition[0].x][blockPosition[0].y - 2].occupied &&
            !grid[blockPosition[1].x + 1][blockPosition[1].y - 1].occupied &&
            !grid[blockPosition[3].x + 1][blockPosition[3].y + 1].occupied)
        {
            blockPosition[0].y -= 2;
            blockPosition[1].x += 1;
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
