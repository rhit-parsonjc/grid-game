#ifndef GAME
#define GAME

#include "GameGrid.h"
class Game
{
public:
	Game(short rows, short columns);
	~Game();
	void displayGrid();
	void goDirection(char direction);
private:
	GameGrid* levels;
	short playerRow;
	short playerCol;
	short playerLevel;
	Grid* visible;
};
#endif
