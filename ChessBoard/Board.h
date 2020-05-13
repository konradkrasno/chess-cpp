#pragma once
#include <iostream>
#include <map>
using std::string;

#include "subsidiary.h"
#include "ChessMan.h"

class Board
{
private:
    std::map <string, ChessMan> _boardMapping;
    std::map<string, ChessMan> _StartingBoard();
    void _DrawMiddle(LineType const lineType, char file = 0, string chessMan = "none") const;
    void _DrawEndBegin(LineEndBegin const lineEndBegin, char rank = 0) const;
    void _DrawEntireNonPositionLine(LineType const lineType, LineEndBegin const lineEndBegin, string fileRange, char rank = 0) const;
    void _DrawEntirePositionLine(string fileRange, char rank = 0) const;

public:
    Board();
    ~Board();
    void DrawBoard() const;
    ChessMan FindChessManOnBoard(char const file, char const rank) const;
    void ChangeChessManPosition(string actual_position, string new_position);
    void MakeMove(string actual_position, string new_position);
};
