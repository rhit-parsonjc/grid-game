#include <iostream>
#include "Game.h"

using namespace std;

int main() {
	Game game(5, 5);
	char direction;
	while (!game.isGameComplete()) {
		game.displayGrid();
		cin >> direction;
		game.goDirection(direction);
		cout << "\n";
	}
	return 0;
}