#pragma once
#include <vector>
#include "Tetromino.h"

using namespace std;

class SBlock : public Tetromino
{
private:
    Vector2i startingPosition0 = { 8,1 };
    Vector2i startingPosition1 = { 9,1 };
    Vector2i startingPosition2 = { 9,0 };
    Vector2i startingPosition3 = { 10,0 };

public:
    SBlock()
    {
        startingPositions =
        {
            startingPosition0, startingPosition1, startingPosition2, startingPosition3
        };

        blockPosition[0] = startingPositions[0];
        blockPosition[1] = startingPositions[1];
        blockPosition[2] = startingPositions[2];
        blockPosition[3] = startingPositions[3];
    }

    void rotateBlock(vector<vector<bool>>& grid) override;
};
