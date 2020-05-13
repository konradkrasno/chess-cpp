#include "Move.h"

Move::Move()
{
}

Move::~Move()
{
}

std::list<string> Move::RookPosibleMoves(string actual_position, std::map<string, ChessMan> boardMapping)
{
    // TODO test it!

    std::list<string> possibleMoves;
    int fileIndex;
    int rankIndex;

    ChessMan movedChessMan(boardMapping.at(actual_position));

    fileIndex = fileRange.find(actual_position[0]) + 1;
    for (auto it = fileRange.begin() + fileIndex; it != fileRange.end(); it++)
    {
        string possiblePosition(ConvertFileRandToPosition(*it, actual_position[1]));
        ChessMan possiblePositionChessMan(boardMapping.at(possiblePosition));

        if (possiblePositionChessMan.GetSymbol == "none")
        {
            possibleMoves.push_back(possiblePosition);
        }
        if (possiblePositionChessMan.GetColor() != movedChessMan.GetColor())
        {
            possibleMoves.push_back(possiblePosition);
        }
        break;
    }

    return possibleMoves;
}
