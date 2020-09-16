#include "SnakePiece.h"
#include "Box.h"
#include "Board.h"
#include "Window.h"
#include "Snake.h"
#include <iostream>
void SnakePiece::render() {
	SDL_SetRenderDrawColor(Window::renderer, Snake::snakeColor.r, Snake::snakeColor.g, Snake::snakeColor.b, Snake::snakeColor.a);
	SDL_RenderFillRect(Window::renderer, &drawRect);
}

void SnakePiece::init(int newRow, int newCol) {
	
	next = nullptr;
	row = newRow;
	col = newCol;
	drawRect.w = Box::boxWidth;
	drawRect.h = Box::boxHeight;
	drawRect.x = Board::xPos + col * Box::boxWidth;
	drawRect.y = Board::yPos + row * Box::boxHeight;

}