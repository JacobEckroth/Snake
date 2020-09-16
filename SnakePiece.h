#pragma once
#include "SDL.h"
class SnakePiece
{
public:
	void render();
	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}
	SnakePiece* getNext() {
		return next;
	}
	SnakePiece* next;
	
	void init(int,int);
private:

	
	int row;
	int col;
	SDL_Rect drawRect;

};

