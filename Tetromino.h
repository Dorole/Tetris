#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

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

    virtual void rotateBlock(vector<vector<bool>>& grid) = 0;
 
    void translateBlockHorizontally(vector<vector<bool>>& grid, int direction);

    bool hasReachedBottomBorder(const int bottomBorderIndex);

    bool canTranslateDownwards(vector<vector<bool>>& grid);
    
    bool canFitOnGrid(const vector<vector<bool>>& grid);
};

