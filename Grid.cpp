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
			short value = get_value(level);
			elements[row * columns + col] = value;
		}
	}
	elements[0] = 6;
}

Grid::~Grid()
{
	delete elements;
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

short Grid::get_value(short level)
{
	short min_value = 2;
	for (short i = 0; i < level; i++) {
		min_value += (3 * min_value) / 4;
	}
	short value = rand() % min_value + min_value;
	return value;
}
