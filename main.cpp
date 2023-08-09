#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "Tetromino.h"
#include "GridPointData.h"
#include "GameManager.h"
#include "TBlock.h";


using namespace std;
using namespace sf;

bool compareValueByY(const GridPointData& a, const GridPointData& b)
{
    return a.coordinates.y > b.coordinates.y;
}



int main()
{
#pragma region PARAMETERS
    GameManager gameManager;

    RenderWindow window(VideoMode(1000, 1250), "Tetris");
    window.setPosition({ 340, 3 });

    Texture buildingBlockTexture;
    buildingBlockTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tetris/Resources/tetris_block_white.png");
    Sprite blockSprite(buildingBlockTexture);

    vector<Color> colorsVector =
    {
        Color(255,89,143),
        Color(253,138,94),
        Color(224,227,0),
        Color(1,221,221),
        Color(0,191,175)
    };

    blockSprite.setColor(gameManager.getRandomColor(colorsVector));

    //vector<Tetromino*> blocksVector = gameManager.resetBlocksVector();
    Tetromino* tetromino = gameManager.getRandomBlock();

    // ************ BLOCK SPRITE *****************
    float targetWidth = 50.f;
    float targetHeight = 50.f;
    float scaleX = targetWidth / blockSprite.getGlobalBounds().width;
    float scaleY = targetHeight / blockSprite.getGlobalBounds().height;
    blockSprite.setScale(scaleX, scaleY);

    // ************* GAMEPLAY CONFIG *****************
    // potencijalno namjestiti u GameManageru i preuzeti od tamo?
    const unsigned int blockOffset = 50;
    const auto defaultFallingSpeed = 0.3f;
    float currentFallingSpeed = defaultFallingSpeed;
    const unsigned int xAxis = 20;
    const unsigned int yAxis = 25;
    const auto lastY = 24;

    GridPointData gridData;

	// TEST 2D DATA VEC INSTEAD OF BOOL VEC
	vector<vector<GridPointData>> testDataVector;
	for (size_t i = 0; i < xAxis; i++)
	{
		testDataVector.push_back(vector<GridPointData>());

		for (int j = 0; j < yAxis; j++)
		{
			GridPointData data =
			{
				Vector2i(i, j),
				false,
				colorsVector.at(0)
			};

			testDataVector.at(i).push_back(data);
		}
	}

    Clock clock;

    vector<int> linesToRemove = {};
    bool gameOver = false;
#pragma endregion 

     while (window.isOpen())
     {
		 gameManager.checkRowFull(yAxis, xAxis, testDataVector, linesToRemove);

		 while (!linesToRemove.empty())
		 {
			 cout << "BOARD STATE:" << endl;
			 for (size_t i = 0; i < yAxis; i++)
			 {
				 for (size_t j = 0; j < xAxis; j++)
				 {
					 cout << testDataVector[j][i].occupied << " ";
				 }
				 cout << endl;
			 }

			 //remove data from removed rows
			 gameManager.setRowValue(linesToRemove, xAxis, testDataVector);

			 //push remaining data and blocks down
			 gridData.pushDataDownOnGrid(testDataVector, xAxis, yAxis);

			 linesToRemove.clear();

			 cout << "BOARD STATE:" << endl;
			 for (size_t i = 0; i < yAxis; i++)
			 {
				 for (size_t j = 0; j < xAxis; j++)
				 {
					 cout << testDataVector[j][i].occupied << " ";
				 }
				 cout << endl;
			 }

		 }

		 if (linesToRemove.empty())
		 {
			 Time elapsedTime = clock.getElapsedTime();

			 //*********************** HANDLE EVENTS / INPUT **********************
			 Event event;
			 while (window.pollEvent(event))
			 {
				 switch (event.type)
				 {
				 case Event::Closed:
					 window.close();
					 break;
				 case Event::KeyPressed:
					 switch (event.key.code)
					 {
					 case Keyboard::A:
					 case Keyboard::Left:
						 //move left by 1
						 tetromino->translateBlockHorizontally(testDataVector, -1);
						 break;
					 case Keyboard::D:
					 case Keyboard::Right:
						 //move right by 1
						 tetromino->translateBlockHorizontally(testDataVector, 1);
						 break;
					 case Keyboard::Space:
						 tetromino->rotateBlock(testDataVector);
						 break;
					 case Keyboard::S:
					 case Keyboard::Down:
						 currentFallingSpeed = defaultFallingSpeed / 3;
						 break;
					 default:
						 break;
					 }
					 break;
				 case Event::KeyReleased:
					 switch (event.key.code)
					 {
					 case Keyboard::S:
					 case Keyboard::Down:
						 currentFallingSpeed = defaultFallingSpeed;
						 break;
					 default:
						 break;
					 }
					 break;
				 default:
					 break;
				 }

				 if (event.type == Event::Closed)
					 window.close();
			 }

			 // *********************** UPDATE WORLD *****************************

			 if (!gameOver && elapsedTime.asSeconds() >= currentFallingSpeed)
			 {
				 if (!(tetromino->hasReachedBottomBorder(lastY)) &&
					 tetromino->canTranslateDownwards(testDataVector))
				 {
					 for (size_t i = 0; i < 4; i++)
						 tetromino->blockPosition[i].y++;
				 }
				 else
				 {
					 for (auto blockPoint : tetromino->blockPosition)
					 {
						 testDataVector[blockPoint.x][blockPoint.y].occupied = true;
						 testDataVector[blockPoint.x][blockPoint.y].color = blockSprite.getColor();

					 }

					 tetromino = gameManager.getRandomBlock();
					 //tetromino = new TBlock();

					 if (!tetromino->canFitOnGrid(testDataVector))
					 {
						 cout << "GAME OVER" << endl;
						 gameOver = true;
					 }
					 else
					 {
						 Color currentColor = blockSprite.getColor();
						 do
							 blockSprite.setColor(gameManager.getRandomColor(colorsVector));
						 while (blockSprite.getColor() == currentColor);
					 }
				 }

				 clock.restart();
			 }

			 // ************************ DRAW WORLD *****************************

			 //draw tetromino
			 if (!gameOver)
			 {
				 for (auto position : tetromino->blockPosition)
				 {
					 blockSprite.setPosition(position.x * blockOffset, position.y * blockOffset);
					 window.draw(blockSprite);
				 }
			 }

		 }

		 for (int i = 0; i < xAxis; i++)
		 {
			 for (int j = 0; j < yAxis; j++)
			 {
				 if (testDataVector.at(i).at(j).occupied)
				 {
					 Sprite fixedBlockSprite = blockSprite;
					 fixedBlockSprite.setColor(testDataVector[i][j].color);
					 fixedBlockSprite.setPosition(i * blockOffset, j * blockOffset);

					 window.draw(fixedBlockSprite);
				 }
			 }
		 }

		 window.display();
		 window.clear();
     }

    delete tetromino;
}


