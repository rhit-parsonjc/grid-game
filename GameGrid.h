#ifndef GAMEGRID
#define GAMEGRID

#include "Grid.h"
class GameGrid
{
public:
	GameGrid(short rows, short columns);
	~GameGrid();
	Grid* levels;
	short initialPlayerLevel;
private:
	short getValue(short difficulty);
	short getLastLevel();
};
#endif