#include <iostream>
#include <iomanip>
#include "Game.h"
#include "GameGrid.h"

using namespace std;

Game::Game(short rows, short columns)
{
	levels = new GameGrid(rows, columns);
}

Game::~Game()
{
	delete levels;
}

void Game::displayGrid()
{
	for (short row = 0; row < levels->levels->rows; row++) {
		for (short col = 0; col < levels->levels->columns; col++) {
			cout << setw(5) << levels->levels->getElement(row, col);
		}
		cout << "\n";
	}
}
