#include <iostream>
#include <iomanip>
#include "Game.h"
#include "GameGrid.h"

using namespace std;

Game::Game(short rows, short columns)
{
	do {
		levels = new GameGrid(rows, columns);
	} while (levels->levels->getElement(rows - 1, columns - 1) == -1);
	visible = new Grid(rows, columns);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			visible->setElement(row, col, 0);
		}
	}
	playerRow = 0;
	playerCol = 0;
	playerLevel = levels->initialPlayerLevel;
	gameComplete = false;
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
			else if (row == 0 && col == 0)
				cout << setw(5) << " ";
			else if (visible->getElement(row, col))
				cout << setw(5) << levels->levels->getElement(row, col);
			else
				cout << setw(5) << "?";
		}
		cout << "\n";
	}
	cout << "Player Level: " << playerLevel << "\n";
	string directionsAllowed = "E/S";
	if (playerRow == levels->levels->rows - 1)
		directionsAllowed = "E";
	if (playerCol == levels->levels->columns - 1)
		directionsAllowed = "S";
	cout << "Which direction do you want to go in (" << directionsAllowed << ")? ";
}

void Game::goDirection(char direction) {
	short newRow = playerRow;
	short newCol = playerCol;
	if (direction == 'E') {
		newCol++;
	}
	else if (direction == 'S') {
		newRow++;
	}
	visible->setElement(newRow, newCol, true);
	short enemyLevel = levels->levels->getElement(newRow, newCol);
	cout << "Enemy Level: " << enemyLevel << "\n";
	if (enemyLevel >= playerLevel) {
		cout << "Failed to defeat enemy\n";
		playerRow = 0;
		playerCol = 0;
		playerLevel = levels->initialPlayerLevel;
	}
	else {
		cout << "Defeated enemy\n";
		playerRow = newRow;
		playerCol = newCol;
		playerLevel += enemyLevel;
		if (playerRow == levels->levels->rows - 1 &&
			playerCol == levels->levels->columns - 1) {
			gameComplete = true;
			cout << "GAME WON!";
		}
	}
}

bool Game::isGameComplete()
{
	return gameComplete;
}
