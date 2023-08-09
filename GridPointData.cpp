#include <vector>
#include "GridPointData.h"

using namespace std;

void GridPointData::changeYCoordinate(GridPointData& gridPointData, int value)
{
    gridPointData.coordinates.y += value;
}

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

void GridPointData::deleteDataFromGrid(vector<int>& linesToRemove, vector<vector<GridPointData>>& gridDataVector, const unsigned int& xAxis)
{
    for (size_t i = 0; i < linesToRemove.size(); i++)
    {
        for (size_t j = 0; j < xAxis; j++)
        {
            gridDataVector.at(j).at(linesToRemove.at(i)).changeOccupiedState();
        }
    }
}

void GridPointData::pushDataDownOnGrid(vector<vector<GridPointData>>& gridDataVector, const unsigned int& xAxis, const unsigned int& yAxis)
{
    for (int i = 0; i < xAxis; i++)
    {
        for (int j = yAxis - 1; j > -1; j--)
        {
            if (gridDataVector.at(i).at(j).occupied && (j + 1 < yAxis) && !gridDataVector.at(i).at(j + 1).occupied)
            {
                Color c = gridDataVector.at(i).at(j).color;
                gridDataVector.at(i).at(j + 1).color = c;
                gridDataVector.at(i).at(j + 1).changeOccupiedState();
                gridDataVector.at(i).at(j).changeOccupiedState();
            }
        }
    }
}

void GridPointData::changeOccupiedState()
{
    occupied = !occupied;
}
