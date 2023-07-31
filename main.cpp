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

using namespace std;
using namespace sf;

bool compareValueByY(const GridPointData& a, const GridPointData& b)
{
    return a.coordinates.y > b.coordinates.y;
}

int main()
{
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

    vector<Tetromino*> blocksVector = gameManager.resetBlocksVector();
    Tetromino* tetromino = gameManager.getRandomBlock(blocksVector);

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

    vector<vector<bool>> grid;
    //init grid
    for (size_t i = 0; i < xAxis; i++)
    {
        grid.push_back(vector<bool>());

        for (size_t j = 0; j < yAxis; j++)
        {
            grid.at(i).push_back(0);
        }
    }

    //test grid
    GridPointData gridData;
    vector<GridPointData> gridDataVector = {};

    Clock clock;

    vector<int> linesToRemove = {};
    bool gameOver = false;

     while (window.isOpen())
     {
         if (linesToRemove.empty()) //potencijalno ne treba ova provjera
         {
             for (size_t i = 0; i < yAxis; i++)
             {
                 bool shouldRemoveLine = true;
                 for (size_t j = 0; j < xAxis; j++)
                 {
                     if (grid.at(j).at(i) != true)
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

         while (!linesToRemove.empty())
         {
             //set entire row to false
             for (size_t i = 0; i < linesToRemove.size(); i++)
             {
                 for (size_t j = 0; j < xAxis; j++)
                 {
                     grid.at(j).at(linesToRemove.at(i)) = false;
                 }
             }

             //delete data from removed rows
			 int i = 0;
			 while (i < gridDataVector.size())
			 {
				 int xCoordinate = gridDataVector.at(i).coordinates.x;
				 int yCoordinate = gridDataVector.at(i).coordinates.y;

				 if (grid.at(xCoordinate).at(yCoordinate) == false)
				 {
					 swap(gridDataVector.at(i), gridDataVector[gridDataVector.size() - 1]);
					 gridDataVector.pop_back();
					 //cout << "Deleted data on: " << xCoordinate << ", " << yCoordinate << endl;
				 }
				 else
					 i++;
			 }

			 //sort data in the vector by descending y coordinates
			 sort(gridDataVector.begin(), gridDataVector.end(), compareValueByY);

             //push remaining data and blocks down
             for (auto dataPoint : gridDataVector)
             {
                 int xCoordinate = dataPoint.coordinates.x;
                 int yCoordinate = dataPoint.coordinates.y;

                 int nextMoveY = yCoordinate + 1;

                 if (nextMoveY >= yAxis || (grid[xCoordinate][nextMoveY] == true))
                    continue;

                 bool finishedMoving = false;
                 while (!finishedMoving)
                 {
                     if ((nextMoveY + 1 < yAxis) && grid[xCoordinate][nextMoveY] == false)
                         nextMoveY++;
                     else
                         finishedMoving = true;
                 }

				 dataPoint.coordinates.y = nextMoveY;
				 grid[xCoordinate][yCoordinate] = false;                 
				 grid[xCoordinate][dataPoint.coordinates.y] = true;
			 }

            linesToRemove.clear();
  
         }
         

         if (linesToRemove.empty()) // ova provjera ne treba?
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
                         tetromino->translateBlockHorizontally(grid, -1);
                         break;
                     case Keyboard::D:
                     case Keyboard::Right:
                         //move right by 1
                         tetromino->translateBlockHorizontally(grid, 1);
                         break;
                     case Keyboard::Space:
                         tetromino->rotateBlock(grid);
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
                 //proslo vrijeme izmedu 2 spustanja, spusti block za 1
                 //probat spustit, ako ne ide, settle
                 if (!(tetromino->hasReachedBottomBorder(lastY)) &&
                     tetromino->canTranslateDownwards(grid))
                 {
                     //moze se spustiti
                     for (size_t i = 0; i < 4; i++)
                         tetromino->blockPosition[i].y++;
                 }
                 else
                 {
                     // ne moze se spustiti > settle on grid
                     for (auto blockPoint : tetromino->blockPosition)
                     {
                         grid[blockPoint.x][blockPoint.y] = true;

                         //
                         GridPointData gridPoint =
                         {
                             Vector2i(blockPoint.x, blockPoint.y),
                             true,
                             blockSprite.getColor()
                         };
                         gridDataVector.push_back(gridPoint);

                     }

                     for (auto block : blocksVector)
                         delete block;

                     blocksVector.clear();
                     blocksVector = gameManager.resetBlocksVector();

                     //spawn new tetromino
                     //if cannot spawn new > game over

                     tetromino = gameManager.getRandomBlock(blocksVector);

                     if (!tetromino->canFitOnGrid(grid))
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
        //draw grid state
        for (int i = 0; i < xAxis; i++)
        {
            for (int j = 0; j < yAxis; j++)
            {
                if (grid.at(i).at(j) == true)
                {
                    Vector2i position = { i, j };

                    Sprite fixedBlockSprite = blockSprite;
                    fixedBlockSprite.setColor(gridData.getGridPointFromCoordinates(i, j, gridDataVector).color);
                    fixedBlockSprite.setPosition(position.x * blockOffset, position.y * blockOffset);

                    window.draw(fixedBlockSprite);
                }
            }
        }
       
        window.display();
        window.clear();
    }

    
    for (auto block : blocksVector)
        delete block;

    delete tetromino;
}
