#include "Grid.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Grid::Grid(short rows, short columns) : rows{rows}, columns{columns}
{
	srand(time(NULL));
	elements = new short[rows * columns];
	for (short row = 0; row < rows; row++) {
		for (short col = 0; col < columns; col++) {
			short level = row + col;
			short value = getValue(level);
			elements[row * columns + col] = value;
		}
	}
	elements[0] = 6;
	elements[rows * columns - 1] = getLastElement();
}

Grid::~Grid()
{
	delete[] elements;
}

void Grid::displayElements()
{
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			cout << elements[row * columns + col] << "\t";
		}
		cout << "\n";
	}
}

short Grid::getLastElement()
{
	short* highScores = new short[rows * columns];
	for (short row = 0; row < rows; row++) {
		for (short col = 0; col < columns; col++) {
			short currValue = elements[row * columns + col];
			short aboveScore = (row == 0) ? 0 : highScores[(row - 1) * columns + col];
			short leftScore = (col == 0) ? 0 : highScores[row * columns + (col - 1)];
			short highPrevValue = (aboveScore > leftScore) ? aboveScore : leftScore;
			short highScore = 0;
			if (row == 0 && col == 0) {
				highScore = currValue;
			}
			else if (highPrevValue > currValue) {
				highScore = highPrevValue + currValue;
			}
			highScores[row * columns + col] = highScore;
			cout << highScore << "\t";
		}
		cout << "\n";
	}
	short leftValue = highScores[rows * columns - 2];
	short upValue = highScores[(rows - 1) * columns - 1];
	short returnValue = (leftValue > upValue) ? (leftValue - 1) : (upValue - 1);
	delete[] highScores;
	return returnValue;
}

short Grid::getValue(short level)
{
	short minValue = 2;
	for (short i = 0; i < level; i++) {
		minValue += (3 * minValue) / 4;
	}
	short value = rand() % minValue + minValue;
	return value;
}