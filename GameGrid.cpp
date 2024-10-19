#include <iostream>
#include <cstdlib>
#include "GameGrid.h"
#include "Grid.h"

using namespace std;

GameGrid::GameGrid(short rows, short columns)
{
	levels = new Grid(rows, columns);
	srand(time(NULL));
	for (short row = 0; row < rows; row++) {
		for (short col = 0; col < columns; col++) {
			levels->setElement(row, col, getValue(row + col));
		}
	}
	initialPlayerLevel = 6;
	levels->setElement(0, 0, initialPlayerLevel);
	levels->setElement(rows - 1, columns - 1, getLastLevel());
	levels->setElement(0, 0, 0);
}

GameGrid::~GameGrid()
{
	delete levels;
}

short GameGrid::getValue(short difficulty)
{
	short minValue = 2;
	for (short i = 0; i < difficulty; i++)
		minValue += (3 * minValue) / 4;
	short value = rand() % minValue + minValue;
	return value;
}

short GameGrid::getLastLevel()
{
	Grid* maxLevels = new Grid(levels->rows, levels->columns);
	for (short row = 0; row < levels->rows; row++) {
		for (short col = 0; col < levels->columns; col++) {
			short currLevel = levels->getElement(row, col);
			short levelAbove = (row == 0) ? 0 : maxLevels->getElement(row - 1, col);
			short levelLeft = (col == 0) ? 0 : maxLevels->getElement(row, col - 1);
			short maxPrevLevel = max(levelAbove, levelLeft);
			short maxLevel = 0;
			if (row == 0 && col == 0)
				maxLevel = currLevel;
			else if (maxPrevLevel > currLevel)
				maxLevel = maxPrevLevel + currLevel;
			maxLevels->setElement(row, col, maxLevel);
		}
	}
	short returnValue = max(
		maxLevels->getElement(levels->rows - 1, levels->columns - 2),
		maxLevels->getElement(levels->rows - 2, levels->columns - 1));
	delete maxLevels;
	return returnValue;
}
