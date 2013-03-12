#include "console_colors.h"

#include <iostream>

using namespace std;

int main(int, char**) {
	ccset(FG_RED);
	cout << "red ";

	ccset(FG_GREEN);
	cout << "green ";

	ccset(FG_BLUE);
	cout << "blue" << endl;

	ccset(FG_BLACK|BG_WHITE);
	cout << "highlighted" << endl;

	ccset(CONSOLE_DEFAULT);
	cout << "and back to normal";	

	return 0;
}