#pragma once
#include <iostream>
using std::string;

string const fileRange = "abcdefgh";
string const rankRange = "87654321";

string ConvertFileRandToPosition(char file, char rank);

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

enum class ChessManType
{
    None,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Pawn,
};
