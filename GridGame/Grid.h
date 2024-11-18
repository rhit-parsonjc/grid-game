#ifndef GRID
#define GRID

/*
 * Grid represents a 2D grid of integers.
 * When constructed, it cannot be used until the dimensions are set.
 * The dimensions can only be set once.
 */
class Grid
{
	public:
		Grid();
		~Grid();
		void setDimensions(short rowCount, short colCount);
		short getRowCount();
		short getColumnCount();
		int getElement(short row, short col);
		void setElement(short row, short col, int value);
	private:
		int* elements;
		short rowCount;
		short colCount;
		void verifyInitialized();
		int getIndex(short row, short col);
};
#endif