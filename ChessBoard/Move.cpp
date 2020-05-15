#include "Move.h"

Move::Move()
{
}

Move::~Move()
{
}

bool Move::_LookForPossibleMove(
    std::list<string>& possibleMoves,
    std::map<string, ChessMan> const boardState,
    string position,
    ChessMan const movedChessMan
)
{
    ChessMan field(boardState.at(position));
    if (field.GetType() != ChessManType::None)
    {
        if (field.GetColor() == movedChessMan.GetColor()) return true;
        else
        {
            possibleMoves.push_back(position);
            return true;
        }
    }
    possibleMoves.push_back(position);
    return false;
}

void Move::_UpdateReactionBoard(
    std::map<string, std::list<ChessMan>>& reactionBoard,
    std::map<string, ChessMan> const boardState,
    string position,
    ChessMan const movedChessMan
)
{
    std::list<ChessMan>& fields(reactionBoard.at(position));
    fields.push_back(movedChessMan);
}

void Move::_CheckMovesAheadAndUpdateReactionBoard(
    std::list<string>& possibleMoves,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    bool ifFile,
    char const file,
    char const rank
)
{
    int index;
    if (ifFile) index = range.find(file) + 1;
    else index = range.find(rank) + 1;
    
    for (auto it = range.begin() + index; it != range.end(); it++)
    {
        string possiblePosition;
        if (ifFile) possiblePosition = ConvertFileRandToPosition(*it, rank);
        else possiblePosition = ConvertFileRandToPosition(file, *it);

        if (_LookForPossibleMove(possibleMoves, boardState, possiblePosition, movedChessMan)) break;
        _UpdateReactionBoard(reactionBoard, boardState, possiblePosition, movedChessMan);
    }
}

void Move::_CheckMovesBackAndUpdateReactionBoard(
    std::list<string>& possibleMoves,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    bool ifFile,
    char const file,
    char const rank
)
{
    int index(range.length());

    if (ifFile) index -= range.find(file);
    else index -= range.find(rank);

    for (string::reverse_iterator rit = range.rbegin() + index; rit != range.rend(); ++rit)
    {
        string possiblePosition;
        if (ifFile) possiblePosition = ConvertFileRandToPosition(*rit, rank);
        else possiblePosition = ConvertFileRandToPosition(file, *rit);

        if (_LookForPossibleMove(possibleMoves, boardState, possiblePosition, movedChessMan)) break;
        _UpdateReactionBoard(reactionBoard, boardState, possiblePosition, movedChessMan);
    }
}

void Move::_RookPosibleMoves(
    std::list<string>& possibleMoves,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    char const file,
    char const rank
)
{
    _CheckMovesAheadAndUpdateReactionBoard(possibleMoves, boardState, movedChessMan, reactionBoard, fileRange, true, file, rank);
    _CheckMovesBackAndUpdateReactionBoard(possibleMoves, boardState, movedChessMan, reactionBoard, fileRange, true, file, rank);
    _CheckMovesAheadAndUpdateReactionBoard(possibleMoves, boardState, movedChessMan, reactionBoard, rankRange, false, file, rank);
    _CheckMovesBackAndUpdateReactionBoard(possibleMoves, boardState, movedChessMan, reactionBoard, rankRange, false, file, rank);
}

void Move::_BishopPosibleMoves(
    std::list<string>& possibleMoves,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    char const file,
    char const rank
)
{
    //TODO finish this function
}

std::list<string> Move::ChessManPosibleMoves(
    string actual_position,
    std::map<string, ChessMan> boardState,
    std::map<string, std::list<ChessMan>>& reactionBoard
)
{
    std::list<string> possibleMoves;
    char file(actual_position[0]);
    char rank(actual_position[1]);

    ChessMan movedChessMan(boardState.at(actual_position));
    int index;
    bool ifFile(true);
    string range(fileRange);
    if (ifFile) index = range.find(file) + 1;
    else index = range.find(rank) + 1;

    ChessManType chessManType(movedChessMan.GetType());
    switch (chessManType)
    {
    case ChessManType::None:
        break;
    case ChessManType::Rook:
        _RookPosibleMoves(possibleMoves, boardState, movedChessMan, reactionBoard, fileRange, file, rank);
        break;
    case ChessManType::Knight:
        //TODO finish this function
        break;
    case ChessManType::Bishop:
        _BishopPosibleMoves(possibleMoves, boardState, movedChessMan, reactionBoard, fileRange, file, rank);
        break;
    case ChessManType::Queen:
        //TODO finish this function
        break;
    case ChessManType::King:
        //TODO finish this function
        break;
    case ChessManType::Pawn:
        //TODO finish this function
        break;
    default:
        break;
    }
    return possibleMoves;
}
