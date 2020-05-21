#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include "Gameplay.h"


Gameplay::Gameplay()
{
	players.insert(std::pair<char, string>('w', "White"));
	players.insert(std::pair<char, string>('b', "Black"));
}

Gameplay::~Gameplay()
{
}

char Gameplay::SwitchPlayer(char playerColor)
{
	if (playerColor == 'w') return 'b';
	return 'w';
}

bool Gameplay::ValidateInput(string input)
{
	if (input == "exit") return true;
	if (input.size() != 2) return false;

	bool validFile(false);
	bool validRank(false);
	for (char const& file : fileRange)
	{
		if (input[0] == file) validFile = true;
	}
	for (char const& rank : rankRange)
	{
		if (input[1] == rank) validRank = true;
	}
	if (validFile)
	{
		if (validRank) 	return true;
	}
	return false;
}

string Gameplay::GetInputFromUser(char playerColor, string message)
{
	while (true)
	{
		cout << players.at(playerColor) << message;
		string position;
		cin >> position;
		bool valid(ValidateInput(position));
		if (valid) return position;
	}
}

void Gameplay::StartGame()
{
	cout << "This is Chess Game" << endl;

	char playerColor('w');
	while (true)
	{
		board.DrawBoard();
		string actual_position(GetInputFromUser(playerColor, ": which chessman would you like to move? "));
		if (actual_position == "exit") break;
		string new_position(GetInputFromUser(playerColor, ": where would you like to move? "));
		if (new_position == "exit") break;
		if (board.MakeMove(playerColor, actual_position, new_position))
			playerColor = SwitchPlayer(playerColor);
		//if (board.CheckMate(playerColor, board.attributes.kingsPositions.at(playerColor))) break;
	}
}
