#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GridPointData.h"

using namespace std;
using namespace sf;

class Tetromino
{

public:

    Vector2i blockPosition[4];
    vector<Vector2i> startingPositions;

    enum class Rotation { BOTTOM, LEFT, TOP, RIGHT } rotation {Rotation::BOTTOM};

    Tetromino() {}

    Tetromino(vector<Vector2i> args)
    {
        for (size_t i = 0; i < 4; i++)
            blockPosition[i] = args[i];
    }

    virtual void rotateBlock(vector<vector<GridPointData>>& grid) = 0;
 
    void translateBlockHorizontally(vector<vector<GridPointData>>& grid, int direction);

    bool hasReachedBottomBorder(const int bottomBorderIndex);

    bool canTranslateDownwards(vector<vector<GridPointData>>& grid);
    
    bool canFitOnGrid(const vector<vector<GridPointData>>& grid);
};

