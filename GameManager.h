#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "GridPointData.h"

using namespace std;
using namespace sf;

class GameManager
{
public:
    Tetromino* getRandomBlock();
    Color getRandomColor(vector<Color> colorsVector);
    int getIndex(vector<Tetromino*> blocksVector, Tetromino* block);
    vector<Tetromino*> resetBlocksVector();

    void checkRowFull(const unsigned int& yAxis, const unsigned int& xAxis, vector<vector<GridPointData>>& grid, vector<int>& linesToRemove);
    void setRowValue(vector<int>& linesToRemove, const unsigned int& xAxis, vector<vector<GridPointData>>& grid);
    void clearBlocksVector(vector<Tetromino*>& blocksVector);
    
    void printBoardState(const unsigned int& xAxis, const unsigned int& yAxis, vector<vector<GridPointData>>& grid);
};

