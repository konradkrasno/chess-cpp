#include "subsidiary.h"
#include "ChessMan.h"

ChessMan::ChessMan(ChessManType const type, char const color) : _type(type), _color(color)
{
	switch (_type)
	{
	case ChessManType::None:
		_symbol += "None";
		break;
	case ChessManType::Rook:
		_symbol += _color;
		_symbol += "R";
		break;
	case ChessManType::Knight:
		_symbol += _color;
		_symbol += "Kn";
		break;
	case ChessManType::Bishop:
		_symbol += _color;
		_symbol += "B";
		break;
	case ChessManType::Queen:
		_symbol += _color;
		_symbol += "Q";
		break;
	case ChessManType::King:
		_symbol += _color;
		_symbol += "Ki";
		break;
	case ChessManType::Pawn:
		_symbol += _color;
		_symbol += "p";
		break;
	default:
		break;
	}
}

ChessMan::~ChessMan()
{
}

bool ChessMan::operator==(ChessMan const& chessMan) const
{
	return _symbol == chessMan._symbol;
}
