#include <vector>
#include "GridPointData.h"

using namespace std;

GridPointData GridPointData::getGridPointFromCoordinates(int x, int y, vector<GridPointData>& gridVector)
{
    for (GridPointData point : gridVector)
    {
        if (point.coordinates.x == x && point.coordinates.y == y)
            return point;
    }
}

bool GridPointData::checkForDataOnCoordinates(int x, int y, vector<GridPointData>& gridVector)
{
    for (GridPointData point : gridVector)
    {
        if (point.coordinates.x == x && point.coordinates.y == y)
            return true;
    }

    return false;
}

void GridPointData::deleteDataFromGrid(vector<GridPointData>& gridDataVector, vector<vector<bool>>& grid)
{
    int i = 0;
    while (i < gridDataVector.size())
    {
        int xCoordinate = gridDataVector.at(i).coordinates.x;
        int yCoordinate = gridDataVector.at(i).coordinates.y;

        if (grid.at(xCoordinate).at(yCoordinate) == false)
        {
            swap(gridDataVector.at(i), gridDataVector[gridDataVector.size() - 1]);
            gridDataVector.pop_back();
            //cout << "Deleted data on: " << xCoordinate << ", " << yCoordinate << endl;
        }
        else
            i++;
    }
}

void GridPointData::pushDataDownOnGrid(vector<GridPointData>& gridDataVector, const unsigned int& yAxis, vector<vector<bool>>& grid)
{
    for (auto dataPoint : gridDataVector)
    {
        int xCoordinate = dataPoint.coordinates.x;
        int yCoordinate = dataPoint.coordinates.y;

        int nextMoveY = yCoordinate + 1;

        if (nextMoveY >= yAxis || (grid[xCoordinate][nextMoveY] == true))
            continue;

        bool finishedMoving = false;
        while (!finishedMoving)
        {
            if ((nextMoveY + 1 < yAxis) && grid[xCoordinate][nextMoveY] == false)
                nextMoveY++;
            else
                finishedMoving = true;
        }

        dataPoint.coordinates.y = nextMoveY;
        grid[xCoordinate][yCoordinate] = false;
        grid[xCoordinate][dataPoint.coordinates.y] = true;
    }
}
