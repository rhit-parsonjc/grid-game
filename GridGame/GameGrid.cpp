#include <iostream>
#include <cstdlib>
#include "GameGrid.h"
#include "Grid.h"

using namespace std;

GameGrid::GameGrid() {
	// These parameters configure the grid difficulty.
	incrementFactor = 1.5;
	initialPlayerLevel = 3;
	srand(time(NULL));
	initialized = false;
}

void GameGrid::setup(short rowCount, short colCount) {
	if (rowCount < 2)
		throw "There must be at least 2 rows";
	if (colCount < 2)
		throw "There must be at least 2 columns";
	levels.setDimensions(rowCount, colCount);
	while (true) {
		for (short row = 0; row < rowCount; row++) {
			for (short col = 0; col < colCount; col++) {
				if (row == 0 && col == 0)
					levels.setElement(row, col, 0);
				else if (row == rowCount - 1 && col == colCount - 1) {
					int lastLevel = getLastLevel();
					levels.setElement(row, col, lastLevel);
					if (lastLevel > -1) {
						initialized = true;
						return;
					}
				}
				else
					levels.setElement(row, col, getEnemyLevel(row + col));
			}
		}
	}
}

int GameGrid::getInitialPlayerLevel() {
	verifyInitialized();
	return initialPlayerLevel;
}

int GameGrid::getEnemyLevel(short row, short col) {
	verifyInitialized();
	if (row < 0 || row >= levels.getRowCount())
		throw "Row index invalid";
	else if (col < 0 || col >= levels.getColumnCount())
		throw "Column index invalid";
	else if (row == 0 && col == 0)
		throw "Top left corner has no enemy";
	else
		return levels.getElement(row, col);
}

short GameGrid::getRowCount() {
	verifyInitialized();
	return levels.getRowCount();
}

short GameGrid::getColumnCount() {
	verifyInitialized();
	return levels.getColumnCount();
}

/*
 * The level of an enemy is a random number.
 * The larger the Manhattan distance from the top-left corner,
 * The larger the level of the enemy.
 * The level ranges increase exponentially according to incrementFactor.
 * For example, if incrementFactor is 1.5:
 *   Distance 0: Range 1-2
 *   Distance 1: Range 2-2
 *   Distance 2: Range 2-3
 *   Distance 3: Range 3-5
 *   Distance 4: Range 5-8
 *   Distance 5: Range 8-11
 *   Distance 6: Range 11-17
 */
int GameGrid::getEnemyLevel(int distance) {
	double minValue = pow(incrementFactor, distance);
	double maxValue = pow(incrementFactor, distance + 1);
	int minValueInt = static_cast<int>(round(minValue));
	int maxValueInt = static_cast<int>(round(maxValue));
	return rand() % (maxValueInt - minValueInt + 1) + minValueInt;
}

/*
 * The enemy level is set so that the path must be optimal.
 * This determines the maximum level that the player can be at each grid spot.
 * A return value of -1 indicates that the bottom right corner is unreachable.
 */
int GameGrid::getLastLevel()
{
	/*
	 * The maximum level that the player can reach at each grid spot.
	 * A value of 0 indicates that the player cannot reach that spot.
	 */
	Grid maxPlayerLevels;
	short rowCount = levels.getRowCount();
	short colCount = levels.getColumnCount();
	maxPlayerLevels.setDimensions(rowCount, colCount);
	for (short row = 0; row < rowCount; row++) {
		for (short col = 0; col < colCount; col++) {
			int maxPlayerLevel;
			// At the top left corner, the player level is initialPlayerLevel
			if (row == 0 && col == 0)
				maxPlayerLevel = initialPlayerLevel;
			// The bottom right corner can be skipped.
			else if (row == rowCount - 1 && col == colCount - 1)
				continue;
			else {
				/*
				 * There are two ways to approach each spot in the grid : from the left and from above.
				 * The maximum player level at a grid spot is whichever is larger, plus the enemy level at this spot.
				 * However, if neither player level exceeds the current enemy level, this spot is unreachable.
				 */
				short currEnemyLevel = levels.getElement(row, col);
				short maxPlayerLevelAbove = (row == 0) ? 0 : maxPlayerLevels.getElement(row - 1, col);
				short maxPlayerLevelLeft = (col == 0) ? 0 : maxPlayerLevels.getElement(row, col - 1);
				short maxPrevLevel = max(maxPlayerLevelAbove, maxPlayerLevelLeft);
				maxPlayerLevel = (maxPrevLevel > currEnemyLevel) ? maxPrevLevel + currEnemyLevel : 0;
			}
			maxPlayerLevels.setElement(row, col, maxPlayerLevel);
		}
	}
	// Determine the max player level at the bottom-right corner.
	short maxFinalPlayerLevel = max(
		maxPlayerLevels.getElement(rowCount - 1, colCount - 2),
		maxPlayerLevels.getElement(rowCount - 2, colCount - 1));
	return maxFinalPlayerLevel - 1;
}

void GameGrid::verifyInitialized() {
	if (!initialized)
		throw "GameGrid has not been initialized yet";
}