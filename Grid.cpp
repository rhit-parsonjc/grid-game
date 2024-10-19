#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid(short rows, short columns) : rows{rows}, columns{columns}
{
	elements = new short[rows * columns];
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			elements[row * columns + col] = row + col;
		}
	}
}

Grid::~Grid()
{
	delete elements;
}

void Grid::displayElements()
{
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			cout << elements[row * columns + col] << " ";
		}
		cout << "\n";
	}
}
