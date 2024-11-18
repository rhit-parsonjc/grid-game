#include <iostream>
#include <iomanip>
#include "Game.h"
#include "GameGrid.h"

using namespace std;

void Game::setup(short rowCount, short columnCount) {
	playerRow = 0;
	playerCol = 0;
	gameComplete = false;
	gameGrid.setup(rowCount, columnCount);
	visibleSpaces.setDimensions(rowCount, columnCount);
	for (int row = 0; row < rowCount; row++)
		for (int col = 0; col < columnCount; col++)
			visibleSpaces.setElement(row, col, 0);
	playerLevel = gameGrid.getInitialPlayerLevel();
}

void Game::displayGrid()
{
	int elementWidth = 10;
	short rowCount = gameGrid.getRowCount();
	short colCount = gameGrid.getColumnCount();
	for (short row = 0; row < rowCount; row++) {
		for (short col = 0; col < colCount; col++) {
			if (row == playerRow && col == playerCol)
				cout << setw(elementWidth) << "X"; // Player symbol
			else if (row == 0 && col == 0)
				cout << setw(elementWidth) << " "; // Unoccupied left corner
			else if (visibleSpaces.getElement(row, col) == 1)
				cout << setw(elementWidth) << gameGrid.getEnemyLevel(row, col); // Known enemy
			else
				cout << setw(elementWidth) << "?"; // Unknown spot
		}
		cout << "\n";
	}
	cout << "Player Level: " << playerLevel << "\n";
	string directionsAllowed = "E/S";
	if (playerRow == rowCount - 1 && playerCol == colCount - 1)
		cout << "You have reached the bottom right corner.";
	if (playerRow == rowCount - 1)
		directionsAllowed = "E";
	if (playerCol == colCount - 1)
		directionsAllowed = "S";
	cout << "Which direction do you want to go in (" << directionsAllowed << ")? ";
}

void Game::goDirection(char direction) {
	if (gameComplete)
		throw "The game is already over";
	short newRow = playerRow;
	short newCol = playerCol;
	short rowCount = gameGrid.getRowCount();
	short colCount = gameGrid.getColumnCount();
	if (direction == 'E') {
		newCol++;
		if (newCol >= colCount)
			throw "Cannot go east";
	}
	else if (direction == 'S') {
		newRow++;
		if (newRow >= rowCount)
			throw "Cannot go south";
	}
	else
		throw "Invalid direction";
	visibleSpaces.setElement(newRow, newCol, 1);
	int enemyLevel = gameGrid.getEnemyLevel(newRow, newCol);
	cout << "Enemy Level: " << enemyLevel << "\n";
	if (enemyLevel >= playerLevel) {
		cout << "Failed to defeat enemy\n";
		playerRow = 0;
		playerCol = 0;
		playerLevel = gameGrid.getInitialPlayerLevel();
	}
	else {
		cout << "Defeated enemy\n";
		playerRow = newRow;
		playerCol = newCol;
		playerLevel += enemyLevel;
		if (playerRow == rowCount - 1 &&
			playerCol == colCount - 1) {
			gameComplete = true;
			cout << "GAME WON!\n";
		}
	}
}

bool Game::isGameComplete()
{
	return gameComplete;
}
