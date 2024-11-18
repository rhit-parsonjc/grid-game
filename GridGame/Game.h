#ifndef GAME
#define GAME

#include "GameGrid.h"
class Game
{
	public:
		void setup(short rows, short columns);
		void displayGrid();
		void goDirection(char direction);
		bool isGameComplete();
	private:
		short playerRow;
		short playerCol;
		short playerLevel;
		bool gameComplete;
		GameGrid gameGrid;
		Grid visibleSpaces;
};
#endif
