#pragma once
#include <list>
using std::string;

#include "subsidiary.h"
#include "Board.h"

class Move
{
public:
    Move();
    ~Move();
    std::list<string> RookPosibleMoves(string actual_position, std::map<string, ChessMan> boardMapping);
};
