#ifndef GAMEGRID
#define GAMEGRID

/*
 * GameGrid stores the levels of the enemies on the grid.
 * The setup method must be called after the object is constructed.
 */

#include "Grid.h"
class GameGrid
{
	public:
		GameGrid();
		void setup(short rowCount, short columnCount);
		int getInitialPlayerLevel();
		int getEnemyLevel(short row, short col);
		short getRowCount();
		short getColumnCount();
	private:
		Grid levels;
		int initialPlayerLevel;
		double incrementFactor;
		bool initialized;
		int getEnemyLevel(int distance);
		int getLastLevel();
		void verifyInitialized();
};
#endif