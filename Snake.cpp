#include "Snake.h"
#include "Board.h"
#include <iostream>
SDL_Color Snake::snakeColor;
void Snake::render() {
	SnakePiece* traveler;
	traveler = head;
	while (traveler) {
		traveler->render();
		traveler = traveler->getNext();
	}
}


void Snake::init(int headRow, int headCol) {
	this->headRow = headRow;
	this->headCol = headCol;
	head = new SnakePiece();
	head->init(headRow, headCol);
	direction = 'l';
	length = 3;
	head->next = new SnakePiece();
	head->next->init(headRow, headCol + 1);
	head->next->next = new SnakePiece();
	head->next->next->init(headRow, headCol + 2);
	growLeft = 0;
	walls = true;
}

void Snake::updateMovement(char newDir) {
	direction = newDir;
}

void Snake::updateLocation() {
	
	SnakePiece* newHead = new SnakePiece();
	int newHeadRow, newHeadCol;
	switch (direction) {
	case 'l':
		newHeadRow = headRow;
		newHeadCol = headCol - 1;
		if (!walls) {
			if (newHeadCol < 0) {
				newHeadCol = Board::cols - 1;
			}
		}
		newHead->init(newHeadRow,newHeadCol);	
		break;
	case 'r':
		newHeadRow = headRow;
		newHeadCol = headCol + 1;
		if (!walls) {
			if (newHeadCol > Board::cols - 1) {
				newHeadCol = 0;
			}
		}
		newHead->init(newHeadRow, newHeadCol);
		
		
		break;
	case 'u':
		
		newHeadCol = headCol;
		newHeadRow = headRow - 1;
		if (!walls) {
			if (newHeadRow < 0) {
				newHeadRow = Board::rows - 1;
			}
		}
		newHead->init(newHeadRow,newHeadCol);
	
	
		break;
	case 'd':

		newHeadRow = headRow + 1;
		newHeadCol = headCol;
		if (!walls) {
			if (newHeadRow > Board::rows - 1) {
				newHeadRow = 0;
			}
		}
		newHead->init(newHeadRow, newHeadCol);
		
		
		break;
	}
	headCol = newHeadCol;
	headRow = newHeadRow;
	newHead->next = head;
	head = newHead;
	if (growLeft > 0) {
		growLeft--;
		length++;
	}
	else {
		deleteTail();
		growLeft = 0;
	}
}

void Snake::getHeadPos(int& row, int& col) {
	row = headRow;
	col = headCol;
}

bool Snake::isOverlapping() {
	SnakePiece* traveler;
	traveler = head->next;
	while (traveler) {
		if (traveler->getRow() == headRow && traveler->getCol() == headCol) {
			return true;
		}
		traveler = traveler->next;
	}
	return false;
}

bool Snake::notAt(int foodRow, int foodCol) {
	SnakePiece* traveler;
	traveler = head->next;
	while (traveler) {
		if (traveler->getRow() == foodRow && traveler->getCol() == foodCol) {
			return false;
		}
		traveler = traveler->next;
	}
	return true;
}

void Snake::gotFood() {
	growLeft += 3;
}

void Snake::toggleWalls() {
	walls = !walls;
}

void Snake::deleteTail() {
	SnakePiece* traveler;
	SnakePiece* prev;
	prev = nullptr;
	traveler = head;
	while (traveler->next) {
		prev = traveler;
		traveler = traveler->next;
	}
	if (prev->next) {
		prev->next = nullptr;
	}
	delete traveler;
}


Snake::~Snake() {
	SnakePiece* traveler;
	traveler = head;
	while (traveler) {
		traveler = head->getNext();
		delete head;
		head = traveler;
	}
}
void Snake::deleteSnake() {
	SnakePiece* traveler;
	traveler = head;
	while (traveler) {
		traveler = head->getNext();
		delete head;
		head = traveler;
	}
	head = nullptr;
}