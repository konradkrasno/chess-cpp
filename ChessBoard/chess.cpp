#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include "Gameplay.h"

int main()
{
	Gameplay gameplay;

	while (true)
	{
		gameplay.StartGame();
		cout << "Would you like to play again? (Y/n): ";
		string agree;
		cin >> agree;
		agree = gameplay.MakeLowercase(agree);

		if (agree == "n") break;
	}

	return 0;
}
