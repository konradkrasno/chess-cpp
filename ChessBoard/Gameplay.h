#pragma once
#include <iostream>
#include <map>
using std::string;

#include "subsidiary.h"
#include "ChessMan.h"
#include "Move.h"
#include "Board.h"


class Gameplay
{
private:
	Board board;
	std::map<char, string> players;
public:
	Gameplay();
	~Gameplay();
	bool ValidateInput(string input);
	string GetInputFromUser(char playerColor, string message);
	char SwitchPlayer(char playerColor);
	void StartGame();
	//TODO write function which make lowercase from input
	//TODO write help function
	//TODO write function for drawing board by command
};
