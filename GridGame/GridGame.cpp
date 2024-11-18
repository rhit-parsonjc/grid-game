#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

int main() {
	char direction;
	short rowCount;
	short columnCount;
	string inputString;
	bool playAgain = true;
	cout << "GRID GAME\n";
	cout << "Move to the right and down to reach the bottom-right corner.\n";
	cout << "At each spot, you will encounter an enemy.\n";
	cout << "If your level is above the enemy's, your level will increase by the enemy's level.\n";
	cout << "If your level is below the enemy's, you will be defeated.\n";
	string digits = "23456789";
	do {
		Game game;
		while (true) {
			cout << "Enter the number of rows (2-9): ";
			try {
				getline(cin, inputString);
				if (inputString.length() != 1 || digits.find(inputString) == -1)
					throw "Invalid row count";
				else
					rowCount = digits.find(inputString) + 2;
				break;
			}
			catch (...) {
				cout << "Invalid value\n";
			}
		}
		while (true) {
			cout << "Enter the number of columns (2-9): ";
			try {
				getline(cin, inputString);
				if (inputString.length() != 1 || digits.find(inputString) == -1)
					throw "Invalid column count";
				else
					columnCount = digits.find(inputString) + 2;
				break;
			}
			catch (...) {
				cout << "Invalid value\n";
			}
		}
		game.setup(rowCount, columnCount);
		while (!game.isGameComplete()) {
			while (true) {
				game.displayGrid();
				try {
					cin >> direction;
					game.goDirection(direction);
					break;
				}
				catch (...) {
					cout << "Invalid direction\n";
				}
			}
			cout << "\n";
		}
		cout << "Play again (Y/N)? ";
		while (true) {
			getline(cin, inputString);
			if (inputString == "Y") {
				playAgain = true;
				break;
			}
			else if (inputString == "N") {
				playAgain = false;
				break;
			}
			else
				cout << "Enter Y or N.\n";
		}
	} while (playAgain);
	return 0;
}