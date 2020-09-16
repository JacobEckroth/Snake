#pragma once
#include "SDL.h"


class Box
{
public:

	static int boxWidth;
	static int boxHeight;
	void render();
	void init(int, int);
	bool empty() {
		return isEmpty;
	}
	void removeFood();
	void setFood();
	static SDL_Color foodColor;
private:
	SDL_Rect drawRect;
	bool hasFood;
	int row;
	int col;
	SDL_Color boxColor;
	bool isEmpty;
	bool isFood;


};

