#pragma once
#include <iostream>
#include <map>
using std::string;

#include "subsidiary.h"
#include "Move.h"
#include "BoardAttributes.h"

class Board : 
    public Move
{
private:
    void _DrawMiddle(LineType const lineType, char file = 0, string chessManSymbol = "none") const;
    void _DrawEndBegin(LineEndBegin const lineEndBegin, char rank = 0) const;
    void _DrawEntireNonPositionLine(LineType const lineType, LineEndBegin const lineEndBegin, string fileRange, char rank = 0) const;
    void _DrawEntirePositionLine(string fileRange, char rank = 0) const;

public:
    Board();
    ~Board();
    void DrawBoard() const;
    ChessMan FindChessManOnBoard(char const file, char const rank) const;
    void CalculateMovesBoardAndReactionBoard();
    bool Check(char const kingColor, string const kingPosition);
    bool CheckMate(char const kingColor, string const kingPosition);
    bool MakeMove(char const playerColor, string const actualPosition, string const newPosition);
    //TODO rafactor MakeMove to handle what to do with Pawn on last position
    //TODO write Castling function
};
