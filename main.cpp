#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "Tetromino.h"
#include "GridPointData.h"
#include "GameManager.h"
#include "VisualsSetter.h"


using namespace std;
using namespace sf;

int main()
{
#pragma region PARAMETERS
	Clock clock;
	GameManager gameManager;
	GridPointData gridData;
	VisualsSetter visualsSetter;

    RenderWindow window(VideoMode(1260, 1250), "Tetris");
    window.setPosition({ 340, 3 });

	// ************* TEXTURES & SPRITES *****************
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tetris/Resources/blackboard_large.png");
	Sprite backgroundSprite(backgroundTexture);

    Texture buildingBlockTexture;
    buildingBlockTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tetris/Resources/tetris_block_white_chalk.png");
    Sprite blockSprite(buildingBlockTexture);

	Texture borderTexture;
	borderTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tetris/Resources/vertical_border.png");
	Sprite borderSprite(borderTexture);
	borderSprite.setPosition(Vector2f(1000, 0));

	vector<Color> colorsVector =
	{
		Color(210,30,120),  // purple
		Color(0,204,204),   // light blue
		Color(199,191,54),  // lemon green
		Color(241,119,112), // salmon pink
		Color(45,205,113),  // bright green
		Color(228,126,35),  // orange
		Color(234,76,61),   // red
		Color(239,196,32),  // yellow
		Color(3,146,245),   // azure blue
		Color(255,153,255)  // pink
    };

    blockSprite.setColor(gameManager.getRandomColor(colorsVector));
	visualsSetter.setSpriteScale(blockSprite, 50, 50);

	// ************* TEXT *****************
	Font font;
	font.loadFromFile("C:/Users/dorot/Desktop/C++/Tetris/Resources/sketch_font.otf");
	
	Text* scoreText = visualsSetter.createNewText(font, "SCORE", Vector2f(1060, 600), 50);
	Text* scoreNum = visualsSetter.createNewText(font, "0", Vector2f(1060, 650), 70);
	Text* nextBlockText = visualsSetter.createNewText(font, "NEXT", Vector2f(1060, 250), 60);
	Text* gameOverText = visualsSetter.createNewText(font, "", Vector2f(1060, 850), 60);

	// ************* TETROMINO *****************
	queue<Tetromino*> tetrominoQueue; 
	for (size_t i = 0; i < 2; i++)
		tetrominoQueue.push(gameManager.getRandomBlock());
	
	Tetromino* tetromino = tetrominoQueue.front();
	Tetromino* nextBlock = tetrominoQueue.back();
	Color nextBlockColor = Color::White; 

    // ************* GAMEPLAY CONFIG *****************
    const unsigned int blockOffset = 50;
	const unsigned int nextBlockPositionOffsetX = 13;
	const unsigned int nextBlockPositionOffsetY = 7;
    const auto defaultFallingSpeed = 0.3f; //NE CONST > MIJENJA SE OVISNO O BROJU BODOVA: vise bodova, veca brzina!
    float currentFallingSpeed = defaultFallingSpeed;
    const unsigned int xAxis = 20;
    const unsigned int yAxis = 25;
    const auto lastY = 24;

	vector<vector<GridPointData>> gridDataVector;
	for (size_t i = 0; i < xAxis; i++)
	{
		gridDataVector.push_back(vector<GridPointData>());

		for (int j = 0; j < yAxis; j++)
		{
			GridPointData data =
			{
				Vector2i(i, j),
				false,
				colorsVector.at(0)
			};

			gridDataVector.at(i).push_back(data);
		}
	}

	vector<int> linesToClear = {};
	int clearedLines = 0;
	int scoreMultiplier = 10;
	string scoreString = to_string(clearedLines * scoreMultiplier);
    bool gameOver = false;
#pragma endregion 

     while (window.isOpen())
     {
		 gameManager.checkRowFull(yAxis, xAxis, gridDataVector, linesToClear);

		 while (!linesToClear.empty())
		 {
			 //remove data from cleared rows
			 gameManager.setRowValue(linesToClear, xAxis, gridDataVector);

			 //push remaining data and blocks down
			 gridData.pushDataDownOnGrid(gridDataVector, xAxis, yAxis);

			 clearedLines += linesToClear.size();
			 scoreString = to_string(clearedLines * scoreMultiplier);
			 linesToClear.clear();
		 }

		 if (linesToClear.empty())
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
						 tetromino->translateBlockHorizontally(gridDataVector, -1);
						 break;
					 case Keyboard::D:
					 case Keyboard::Right:
						 //move right by 1
						 tetromino->translateBlockHorizontally(gridDataVector, 1);
						 break;
					 case Keyboard::Space:
						 tetromino->rotateBlock(gridDataVector);
						 break;
					 case Keyboard::S:
					 case Keyboard::Down:
						 currentFallingSpeed = defaultFallingSpeed / 3;
						 break;
					 case Keyboard::P: //TEST
						 clearedLines++;
						 scoreNum->setString(to_string(clearedLines * scoreMultiplier));
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
					 tetromino->canTranslateDownwards(gridDataVector))
				 {
					 for (size_t i = 0; i < 4; i++)
						 tetromino->blockPosition[i].y++;
				 }
				 else
				 {
					 for (auto blockPoint : tetromino->blockPosition)
					 {
						 gridDataVector[blockPoint.x][blockPoint.y].occupied = true;
						 gridDataVector[blockPoint.x][blockPoint.y].color = blockSprite.getColor();

					 }

					 tetrominoQueue.pop();
					 tetromino = nextBlock;
					 tetrominoQueue.push(gameManager.getRandomBlock());
					 nextBlock = tetrominoQueue.back();

					 if (!tetromino->canFitOnGrid(gridDataVector))
					 {
						 cout << "GAME OVER" << endl;
						 gameOverText->setString("GAME \nOVER");
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

			 window.draw(backgroundSprite);
			 window.draw(borderSprite);
			 window.draw(*scoreText);
			 scoreNum->setString(scoreString);
			 window.draw(*scoreNum);
			 window.draw(*nextBlockText);

			 if (gameOver)
				 window.draw(*gameOverText);

			 //draw next block preview
			 for (auto position : nextBlock->blockPosition)
			 {
				 Sprite nextBlockSprite = blockSprite;
				 nextBlockSprite.setPosition((position.x + nextBlockPositionOffsetX) * blockOffset, (position.y + nextBlockPositionOffsetY) * blockOffset);
				 nextBlockSprite.setColor(nextBlockColor);
				 window.draw(nextBlockSprite);
			 }

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
				 if (gridDataVector.at(i).at(j).occupied)
				 {
					 Sprite fixedBlockSprite = blockSprite;
					 fixedBlockSprite.setColor(gridDataVector[i][j].color);
					 fixedBlockSprite.setPosition(i * blockOffset, j * blockOffset);

					 window.draw(fixedBlockSprite);
				 }
			 }
		 }

		 window.display();
		 window.clear();
     }

    delete tetromino;
	delete nextBlock;
	delete scoreText;
	delete scoreNum;
	delete nextBlockText;
	delete gameOverText;
}


