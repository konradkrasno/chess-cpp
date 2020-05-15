#include "Move.h"

Move::Move()
{
}

Move::~Move()
{
}

bool Move::_LookForPossibleMove(
    string const actual_position,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, ChessMan> const boardState,
    string const position,
    ChessMan const movedChessMan
)
{
    ChessMan field(boardState.at(position));
    std::list<string>& possibleMoves(movesBoard.at(actual_position));
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
    string const position,
    ChessMan const movedChessMan
)
{
    std::list<ChessMan>& fields(reactionBoard.at(position));
    fields.push_back(movedChessMan);
}

void Move::_CheckMovesAheadAndUpdateReactionBoard(
    string const actual_position,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    bool const ifFile,
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

        if (_LookForPossibleMove(actual_position, movesBoard, boardState, possiblePosition, movedChessMan)) break;
        _UpdateReactionBoard(reactionBoard, boardState, possiblePosition, movedChessMan);
    }
}

void Move::_CheckMovesBackAndUpdateReactionBoard(
    string const actual_position,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    bool const ifFile,
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

        if (_LookForPossibleMove(actual_position, movesBoard, boardState, possiblePosition, movedChessMan)) break;
        _UpdateReactionBoard(reactionBoard, boardState, possiblePosition, movedChessMan);
    }
}

void Move::_RookPosibleMoves(
    string const actual_position,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, ChessMan> const boardState,
    ChessMan const movedChessMan,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string range,
    char const file,
    char const rank
)
{
    _CheckMovesAheadAndUpdateReactionBoard(actual_position, movesBoard, boardState, movedChessMan, reactionBoard, fileRange, true, file, rank);
    _CheckMovesBackAndUpdateReactionBoard(actual_position, movesBoard, boardState, movedChessMan, reactionBoard, fileRange, true, file, rank);
    _CheckMovesAheadAndUpdateReactionBoard(actual_position, movesBoard, boardState, movedChessMan, reactionBoard, rankRange, false, file, rank);
    _CheckMovesBackAndUpdateReactionBoard(actual_position, movesBoard, boardState, movedChessMan, reactionBoard, rankRange, false, file, rank);
}

void Move::_BishopPosibleMoves(
    string const actual_position,
    std::map<string, std::list<string>>& movesBoard,
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

void Move::ChessManPosibleMoves(
    string const actual_position,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, ChessMan> const boardState,
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
        _RookPosibleMoves(actual_position, movesBoard, boardState, movedChessMan, reactionBoard, fileRange, file, rank);
        break;
    case ChessManType::Knight:
        //TODO finish this function
        break;
    case ChessManType::Bishop:
        _BishopPosibleMoves(actual_position, movesBoard, boardState, movedChessMan, reactionBoard, fileRange, file, rank);
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
}
