#include <iostream>
#include <iomanip>
#include "Game.h"
#include "GameGrid.h"

using namespace std;

Game::Game(short rows, short columns)
{
	do {
		levels = new GameGrid(rows, columns);
	} while (levels->levels->getElement(rows - 1, columns - 1) == 0);
	visible = new Grid(rows, columns);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			visible->setElement(row, col, 0);
		}
	}
	playerRow = 0;
	playerCol = 0;
}

Game::~Game()
{
	delete levels;
}

void Game::displayGrid()
{
	for (short row = 0; row < levels->levels->rows; row++) {
		for (short col = 0; col < levels->levels->columns; col++) {
			if (row == playerRow && col == playerCol)
				cout << setw(5) << "X";
			else if (visible->getElement(row, col))
				cout << setw(5) << levels->levels->getElement(row, col);
			else
				cout << setw(5) << "?";
		}
		cout << "\n";
	}
	cout << "Level " << levels->initialPlayerLevel << "\n";
}
