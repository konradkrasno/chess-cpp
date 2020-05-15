#pragma once
#include <iostream>
#include <list>
using std::string;

#include "subsidiary.h"

class ChessMan
{
private:
    string _symbol;
    ChessManType _type;
    char _color;

public:
	ChessMan(ChessManType const type, char const color);
	~ChessMan();
    string GetSymbol() const { return _symbol; }
    ChessManType GetType() const { return _type; }
    char GetColor() const { return _color; }
    bool operator==(ChessMan const& chessMan) const;
};
