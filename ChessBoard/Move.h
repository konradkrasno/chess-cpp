#pragma once
#include <list>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "Board.h"

class Move
{
private:
    bool _LookForPossibleMove(
        std::list<string>& possibleMoves,
        std::map<string, ChessMan> const boardState,
        string position,
        ChessMan const movedChessMan);

    void _UpdateReactionBoard(
        std::map<string, std::list<ChessMan>>& reactionBoard,
        std::map<string, ChessMan> const boardState,
        string position,
        ChessMan const movedChessMan);

    void _CheckMovesAheadAndUpdateReactionBoard(
        std::list<string>& possibleMoves,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        bool ifFile,
        char const file,
        char const rank
    );

    void _CheckMovesBackAndUpdateReactionBoard(
        std::list<string>& possibleMoves,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        bool ifFile,
        char const file,
        char const rank
    );
    void _RookPosibleMoves(
        std::list<string>& possibleMoves,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        char const file,
        char const rank
    );
    void _BishopPosibleMoves(
        std::list<string>& possibleMoves,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        char const file,
        char const rank
    );

public:
    Move();
    ~Move();
    std::list<string> ChessManPosibleMoves(
        string actual_position,
        std::map<string, ChessMan> boardState,
        std::map<string, std::list<ChessMan>>& reactionBoard
    );
};
