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
