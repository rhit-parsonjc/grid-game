#include <iostream>
#include "Grid.h"

using namespace std;

int main() {
	Grid grid{ 5, 5 };
	cout << "\n";
	grid.displayElements();
	return 0;
}