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
};

