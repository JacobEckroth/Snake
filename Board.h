#pragma once
#include "Box.h"
#include "Snake.h"
class Board
{

	public:
		static int xPos;
		static int yPos;
		void render();
		void update();
		void renderBoxes();
		void renderGrid();
		void initializeBoxes();

		bool waiting() {
			return gameOver;
		}
		void updateBoardStatus();
		void updateMovement(char);
		void spawnInitialFood();
		void spawnNewFood();
		void resetBoard();
		void checkForOverlap();

		void updateSnakeColor();
		void toggleWalls();


		void init(int, int);
		~Board();
		static int rows;
		static int cols;
private:
	
	Box** boxes;
	SDL_Color gridColor;
	Snake snake;
	Uint32 lastUpdated;
	int timeToMove;
	int timeAfterGameOver;
	int foodRow;
	int foodCol;
	bool gameOver;
	int r, g, b;
	int rvel, gvel, bvel;

	
};

