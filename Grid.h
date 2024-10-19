#ifndef GRID
#define GRID
class Grid
{
public:
	Grid(short rows, short columns);
	~Grid();
	void displayElements();
private:
	short rows;
	short columns;
	short* elements;
};
#endif