#include "Board.h"
#include "Window.h"
#include <iostream>
int Board::xPos = 0;
int Board::yPos = 0;
int Board::rows = 0;
int Board::cols = 0;

void Board::render() {
	renderBoxes();
	snake.render();
	renderGrid();
}

void Board::updateSnakeColor() {
	
	r += 1 * rvel;
	if (r > 255) {
		r = 255;
		rvel = -1;
	}
	else if (r < 0) {
		r = 0;
		rvel = 1;
	}
	g += 2 * gvel;
	if (g > 255) {
		g = 255;
		gvel = -1;
	}
	else if (g < 0) {
		g = 0;
		gvel = 1;
	}
	b += 3 * bvel;
	if (b > 255) {
		b = 255;
		bvel = -1;
	}
	else if (b < 0) {
		b = 0;
		bvel = 1;
	}
	Snake::snakeColor.r = r;
	Snake::snakeColor.g = g;
	Snake::snakeColor.b = b;
	
}

void Board::init(int screenWidth, int screenHeight) {
	rows = 25;
	cols = 25;
	boxes = new Box * [rows];
	for (int i = 0; i < rows; i++) {
		boxes[i] = new Box[cols];
	}
	
	int maxBoxWidth = screenWidth / cols;			//make this better later, check for screenHeight

	Box::boxWidth = Box::boxHeight = maxBoxWidth;


	 xPos = (screenWidth - Box::boxWidth * cols) / 2;
	 
	yPos = (screenHeight - Box::boxHeight * rows) / 2;


	gridColor.r = gridColor.g = gridColor.b = 29;
	gridColor.a = 255;
	initializeBoxes();

	rvel = bvel = 1;
	gvel = -1;
	Snake::snakeColor.r = r=90;
	Snake::snakeColor.g = g=219;
	Snake::snakeColor.b = b=217;
	Snake::snakeColor.a = 255;
	snake.init(rows / 2, cols / 2);
	spawnInitialFood();
	timeToMove = 100;
	timeAfterGameOver = 3000;
	gameOver = false;
	lastUpdated = SDL_GetTicks();

}


void Board::checkForOverlap() {
	int snakeHeadRow, snakeHeadCol;
	snake.getHeadPos(snakeHeadRow, snakeHeadCol);
	if (snakeHeadRow >= rows || snakeHeadRow < 0 || snakeHeadCol >= cols || snakeHeadCol < 0 || snake.isOverlapping()) {
		gameOver = true;
		lastUpdated = SDL_GetTicks();
		
	}
	
}
void Board::initializeBoxes() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			boxes[i][j].init(i, j);
		}

	}
	Box::foodColor.r = 227;
	Box::foodColor.g = 70;
	Box::foodColor.b = 133;
	Box::foodColor.a = 255;
}

void Board::updateMovement(char newMove) {
	snake.updateMovement(newMove);
}


void Board::update() {
	if (gameOver) {
		if (SDL_GetTicks() - lastUpdated >= timeAfterGameOver) {
			resetBoard();
		}
	}else if (SDL_GetTicks() - lastUpdated >= timeToMove) {
		lastUpdated = SDL_GetTicks();
		snake.updateLocation();
		updateBoardStatus();
		checkForOverlap();
	}
	updateSnakeColor();
}



void Board::updateBoardStatus() {
	int snakeHeadRow, snakeHeadCol;
	snake.getHeadPos(snakeHeadRow, snakeHeadCol);
	
	if (snakeHeadRow == foodRow && snakeHeadCol == foodCol) {
		
		snake.gotFood();
		spawnNewFood();
	}
	
}


Board::~Board() {
	for (int i = 0; i < rows; i++) {
		delete[] boxes[i];
	}
	delete[] boxes;
}

void Board::spawnInitialFood() {
	int attempts = 0;
	bool foodChosen = false;
	bool outOfOptions = false;
	while (!foodChosen) {
		int row = rand() % rows;
		int col = rand() % cols;
		attempts++;
		if (boxes[row][col].empty() && snake.notAt(row,col)) {
			boxes[row][col].setFood();
			foodChosen = true;
			foodRow = row;
			foodCol = col;
		
		}
		if (attempts >= 10000) {
			outOfOptions = true;
			break;
		}
	}
	if (outOfOptions) {
		resetBoard();
	}
}

void Board::toggleWalls() {
	snake.toggleWalls();
}


void Board::spawnNewFood() {
	boxes[foodRow][foodCol].removeFood();
	spawnInitialFood();

}

void Board::resetBoard() {
	gameOver = false;
	snake.deleteSnake();
	snake.init(rows / 2, cols / 2);
	spawnNewFood();
}


void Board::renderBoxes() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			boxes[i][j].render();
		}
	}
}

void Board::renderGrid() {
	SDL_SetRenderDrawColor(Window::renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
	SDL_Rect drawRect;
	drawRect.w = Box::boxWidth;
	drawRect.h = Box::boxHeight;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			drawRect.x = xPos + j * Box::boxWidth;
			drawRect.y = yPos + i * Box::boxHeight;
			SDL_RenderDrawRect(Window::renderer, &drawRect);
		}
	}


}