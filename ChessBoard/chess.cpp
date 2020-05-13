#include <iostream>
using std::cout;
using std::endl;

#include "ChessMan.h"
#include "Board.h"
#include "Move.h"

int main()
{
	Board board;
	board.DrawBoard();

	board.ChangeChessManPosition("b1", "c3");
	board.DrawBoard();

	board.ChangeChessManPosition("e7", "e5");
	board.DrawBoard();

	//string fileRange("abcdefgh");
	//string rankRange("12345678");

	//string actual_position("h3");
	//
	//std::list<string> possibleMoves;
	//char file(actual_position[0]);
	//char rank(actual_position[1]);

	//int index;

	//index = fileRange.find(file)+1;
	//for (auto it = fileRange.begin() + index; it != fileRange.end(); it++)
	//{
	//	cout << *it << endl;
	//}

	return 0;
}
