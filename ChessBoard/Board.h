#pragma once
#include <iostream>
#include <map>
using std::string;

#include "subsidiary.h"
#include "Move.h"
#include "BoardAttributes.h"

enum class LineType
{
    FileHeader,
    TopHorizontalLine,
    VerticalLines,
    VerticalAndHorizontalLines,
    ChessManPlace
};

enum class LineEndBegin
{
    TopLine,
    RankHeader,
    InnerLine
};

class Board : 
    public Move
{
private:
    void _DrawMiddle(LineType const lineType, char file = 0, string chessManSymbol = "none") const;
    void _DrawEndBegin(LineEndBegin const lineEndBegin, char rank = 0) const;
    void _DrawEntireNonPositionLine(LineType const lineType, LineEndBegin const lineEndBegin, string fileRange, char rank = 0) const;
    void _DrawEntirePositionLine(string fileRange, char rank = 0) const;
    void PawnOnEndLine();
    bool NotFirstMove(char const file, char const rank);
    bool NotEmpty(char const file, char const rank);
    void LookForCastling(char const playerColor, char const file, char const rank, string const file_range, int& cast, char& rookFileForCastling);

public:
    Board();
    ~Board();
    void DrawBoard(char const playerColor) const;
    ChessMan FindChessManOnBoard(char const file, char const rank) const;
    void CalculateMovesBoardAndReactionBoard();
    bool Check(char const kingColor, string const kingPosition);
    bool CheckMate(char const kingColor);
    bool MakeMove(char const playerColor, string const actualPosition, string const newPosition);
    int FindCastlings(char const playerColor, char& rookFileForCastling, char const castlingRank);
    void MakeCastling(char const playerColor, char const rookFile, char const castlingRank);
};
