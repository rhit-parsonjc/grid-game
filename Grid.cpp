#include "Grid.h"

Grid::Grid(short rows, short columns): rows{rows}, columns{columns}
{
	elements = new short[rows * columns];
}

Grid::~Grid()
{
	delete[] elements;
}

short Grid::getElement(short row, short col)
{
	return elements[row * rows + col];
}

void Grid::setElement(short row, short col, short value)
{
	elements[row * rows + col] = value;
}
