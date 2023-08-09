#pragma once
#include <vector>
#include "Tetromino.h"
#include "GridPointData.h"

using namespace std;

class TBlock : public Tetromino
{
private:
    Vector2i startingPosition0 = { 8,0 };
    Vector2i startingPosition1 = { 9,0 };
    Vector2i startingPosition2 = { 10,0 };
    Vector2i startingPosition3 = { 9,1 };

public:
    TBlock()
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

    void rotateBlock(vector<vector<GridPointData>>& grid) override;
};

