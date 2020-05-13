#pragma once
#include <iostream>
#include <list>
using std::string;

#include "subsidiary.h"

class ChessMan
{
private:
    string _symbol;
    string _type;
    string _color;

public:
	ChessMan(string const symbol, string const type, string const color);
	~ChessMan();
    string GetSymbol() const { return _symbol; }
    string GetType() const { return _type; }
    string GetColor() const { return _color; }
};
