#include "Grid.h"

Grid::Grid()
{
	elements = nullptr;
}

Grid::~Grid()
{
	if (elements != nullptr)
		delete[] elements;
}

void Grid::setDimensions(short rowCount, short colCount) {
	if (elements != nullptr)
		throw "Dimensions cannot be set twice";
	else if (rowCount <= 0)
		throw "Row count must be positive";
	else if (colCount <= 0)
		throw "Column count must be positive";
	this->rowCount = rowCount;
	this->colCount = colCount;
	elements = new int[rowCount * colCount];
}

short Grid::getRowCount() {
	verifyInitialized();
	return rowCount;
}

short Grid::getColumnCount() {
	verifyInitialized();
	return colCount;
}

int Grid::getElement(short row, short col)
{
	return elements[getIndex(row, col)];
}

void Grid::setElement(short row, short col, int value)
{
	elements[getIndex(row, col)] = value;
}

void Grid::verifyInitialized() {
	if (elements == nullptr)
		throw "Grid dimensions have not been set yet";
}

int Grid::getIndex(short row, short col) {
	verifyInitialized();
	if (row < 0 || row >= rowCount)
		throw "Row index is invalid";
	else if (col < 0 || col >= colCount)
		throw "Column index is invalid";
	return row * rowCount + col;
}
