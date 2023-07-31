#pragma once
#include "Tetromino.h"
#include <vector>

using namespace std;

class IBlock : public Tetromino
{

private:
    Vector2i startingPosition0 = { 8,0 };
    Vector2i startingPosition1 = { 9,0 };
    Vector2i startingPosition2 = { 10,0 };
    Vector2i startingPosition3 = { 11,0 };

public:
    IBlock()
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

