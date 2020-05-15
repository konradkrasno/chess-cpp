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
        string actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        string position,
        ChessMan const movedChessMan
    );

    void _UpdateReactionBoard(
        std::map<string, std::list<ChessMan>>& reactionBoard,
        std::map<string, ChessMan> const boardState,
        string position,
        ChessMan const movedChessMan
    );

    void _CheckMovesAheadAndUpdateReactionBoard(
        string actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        bool ifFile,
        char const file,
        char const rank
    );

    void _CheckMovesBackAndUpdateReactionBoard(
        string actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        bool ifFile,
        char const file,
        char const rank
    );
    void _RookPosibleMoves(
        string actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        char const file,
        char const rank
    );
    void _BishopPosibleMoves(
        string actual_position,
        std::map<string, std::list<string>>& movesBoard,
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
    void ChessManPosibleMoves(
        string actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> boardState,
        std::map<string, std::list<ChessMan>>& reactionBoard
    );
};
