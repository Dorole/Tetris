#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "Tetromino.h"
#include "TBlock.h";
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "SBlock.h"
#include "ZBlock.h"

using namespace std;
using namespace sf;

Tetromino* GameManager::getRandomBlock(vector<Tetromino*> blocksVector)
{
	random_device randDev;
	mt19937 generator(randDev());

	uniform_int_distribution<unsigned> distribution(0, (blocksVector.size() - 1));

	unsigned randIndex = distribution(generator);

	cout << "Spawned new block" << endl;
	return blocksVector[randIndex];
}

Color GameManager::getRandomColor(vector<Color> colorsVector)
{
	random_device randDev;
	mt19937 generator(randDev());

	uniform_int_distribution<unsigned> distribution(0, (colorsVector.size() - 1));

	unsigned randIndex = distribution(generator);

	return colorsVector[randIndex];
}

int GameManager::getIndex(vector<Tetromino*> blocksVector, Tetromino* block)
{
	auto it = find(blocksVector.begin(), blocksVector.end(), block);
	return distance(blocksVector.begin(), it);

}

vector<Tetromino*> GameManager::resetBlocksVector()
{
	Tetromino* tBlock = new TBlock();
	Tetromino* lBlock = new LBlock();
	Tetromino* jBlock = new JBlock();
	Tetromino* oBlock = new OBlock();
	Tetromino* iBlock = new IBlock();
	Tetromino* sBlock = new SBlock();
	Tetromino* zBlock = new ZBlock();

	return { tBlock, lBlock, jBlock, oBlock, iBlock, sBlock, zBlock };
}
