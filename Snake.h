#pragma once
#include "SDL.h"
#include "SnakePiece.h"
class Snake
{


public:
	void render();
	void updateLocation();
	void deleteTail();
	void getHeadPos(int&, int&);
	void init(int, int);
	void gotFood();
	bool isOverlapping();
	bool notAt(int,int);
	void updateMovement(char);
	void toggleWalls();
	void deleteSnake();


	static SDL_Color snakeColor;
	~Snake();
private:
	bool walls;
	SnakePiece* head;
	int headRow, headCol;
	char direction;
	int length;
	int growLeft;	//how many pieces left to grow
	int increasePerFood;
};

