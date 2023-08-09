#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "Tetromino.h"
#include "GridPointData.h"
#include "TBlock.h";
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "SBlock.h"
#include "ZBlock.h"

using namespace std;
using namespace sf;

Tetromino* GameManager::getRandomBlock()
{
	vector<Tetromino*> blocksVector = { new TBlock(), new LBlock(), new JBlock(), new OBlock(), new IBlock(), new SBlock(), new ZBlock() };

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

void GameManager::clearBlocksVector(vector<Tetromino*>& blocksVector)
{
	for (auto block : blocksVector)
		delete block;

	blocksVector.clear();
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

void GameManager::checkRowFull(const unsigned int& yAxis, const unsigned int& xAxis, vector<vector<GridPointData>>& grid, vector<int>& linesToRemove)
{
	for (size_t i = 0; i < yAxis; i++)
	{
		bool shouldRemoveLine = true;
		for (size_t j = 0; j < xAxis; j++)
		{
			if (!grid.at(j).at(i).occupied)
			{
				shouldRemoveLine = false;
				break;
			}
		}

		if (shouldRemoveLine)
		{
			//cout << "Remove line " << i << endl;
			linesToRemove.push_back(i);
		}
	}
}

void GameManager::setRowValue(vector<int>& linesToRemove, const unsigned int& xAxis, vector<vector<GridPointData>>& grid)
{
	for (size_t i = 0; i < linesToRemove.size(); i++)
	{
		for (size_t j = 0; j < xAxis; j++)
		{
			grid.at(j).at(linesToRemove.at(i)).changeOccupiedState();
		}
	}
}


