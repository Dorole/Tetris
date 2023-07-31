#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GridPointData
{
public:
    Vector2i coordinates = { 0,0 };
    bool occupied = false;
    Color color = Color(0, 0, 0);

    GridPointData getGridPointFromCoordinates(int x, int y, vector<GridPointData>& gridVec);
    bool checkForDataOnCoordinates(int x, int y, vector<GridPointData>& gridVec);

};

