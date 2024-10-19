#ifndef GRID
#define GRID
class Grid
{
public:
	short rows;
	short columns;
	Grid(short rows, short columns);
	~Grid();
	short getElement(short row, short col);
	void setElement(short row, short col, short value);
private:
	short* elements;
};
#endif
