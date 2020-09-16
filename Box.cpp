#include "Box.h"
#include "Window.h"
#include "Board.h"
int Box::boxWidth = 0;
int Box::boxHeight = 0;
#include <iostream>
SDL_Color Box::foodColor;

void Box::render() {
	if (hasFood) {
		
		SDL_SetRenderDrawColor(Window::renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
		SDL_RenderFillRect(Window::renderer, &drawRect);
	}
}

void Box::removeFood() {
	hasFood = false;
	isEmpty = false;

}
void Box::init(int row, int col) {
	this->row = row;
	this->col = col;
	hasFood = false;
	isEmpty = true;
	drawRect.x = Board::xPos + boxWidth * col;
	drawRect.y = Board::yPos + boxHeight * row;
	drawRect.w = boxWidth;
	drawRect.h = boxHeight;
	boxColor.r = boxColor.g = boxColor.b = 0;
	boxColor.a = 255;
}

void Box::setFood() {
	hasFood = true;
	isEmpty = false;

	boxColor.r = foodColor.r;
	boxColor.g = foodColor.g;
	boxColor.b = foodColor.b;
	boxColor.a = foodColor.a;
}