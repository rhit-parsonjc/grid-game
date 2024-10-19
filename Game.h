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
	bool isGameComplete();
private:
	GameGrid* levels;
	short playerRow;
	short playerCol;
	short playerLevel;
	Grid* visible;
	bool gameComplete;
};
#endif
