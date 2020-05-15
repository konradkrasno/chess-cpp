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
        string const actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        string const position,
        ChessMan const movedChessMan
    );

    void _UpdateReactionBoard(
        std::map<string, std::list<ChessMan>>& reactionBoard,
        std::map<string, ChessMan> const boardState,
        string const position,
        ChessMan const movedChessMan
    );

    void _CheckMovesAheadAndUpdateReactionBoard(
        string const actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        bool const ifFile,
        char const file,
        char const rank
    );

    void _CheckMovesBackAndUpdateReactionBoard(
        string const actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        bool const ifFile,
        char const file,
        char const rank
    );
    void _RookPosibleMoves(
        string const actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        ChessMan const movedChessMan,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string range,
        char const file,
        char const rank
    );
    void _BishopPosibleMoves(
        string const actual_position,
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
        string const actual_position,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<ChessMan>>& reactionBoard
    );
};
