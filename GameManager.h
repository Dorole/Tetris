#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

using namespace std;
using namespace sf;

class GameManager
{
public:
    Tetromino* getRandomBlock(vector<Tetromino*> blocksVector);
    Color getRandomColor(vector<Color> colorsVector);
    int getIndex(vector<Tetromino*> blocksVector, Tetromino* block);
    vector<Tetromino*> resetBlocksVector();

    void checkRowFull(const unsigned int& yAxis, const unsigned int& xAxis, vector<vector<bool>>& grid, vector<int>& linesToRemove);
    void setRowValue(vector<int>& linesToRemove, const unsigned int& xAxis, vector<vector<bool>>& grid, bool value);
    void clearBlocksVector(vector<Tetromino*>& blocksVector);
};

