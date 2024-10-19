#ifndef GAME
#define GAME

#include "GameGrid.h"
class Game
{
public:
	Game(short rows, short columns);
	~Game();
	void displayGrid();
private:
	GameGrid* levels;
};
#endif
