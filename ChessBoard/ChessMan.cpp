#include "subsidiary.h"
#include "ChessMan.h"

ChessMan::ChessMan(ChessManType const type, char const color, string position) : _type(type), _color(color), _position(position)
{
	switch (_type)
	{
	case ChessManType::None:
		_symbol += "None";
		_firstMove = false;
		break;
	case ChessManType::Rook:
		_symbol += _color;
		_symbol += "R";
		_firstMove = true;
		break;
	case ChessManType::Knight:
		_symbol += _color;
		_symbol += "Kn";
		_firstMove = false;
		break;
	case ChessManType::Bishop:
		_symbol += _color;
		_symbol += "B";
		_firstMove = false;
		break;
	case ChessManType::Queen:
		_symbol += _color;
		_symbol += "Q";
		_firstMove = false;
		break;
	case ChessManType::King:
		_symbol += _color;
		_symbol += "Ki";
		_firstMove = true;
		break;
	case ChessManType::Pawn:
		_symbol += _color;
		_symbol += "p";
		_firstMove = true;
		if (_color == 'w') _moveDirection = "increase";
		else _moveDirection = "decrease";
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
	return (_symbol == chessMan._symbol && _position == chessMan._position);
}
bool ChessMan::operator!=(ChessMan const& chessMan) const
{
	return (_symbol != chessMan._symbol || _position != chessMan._position);
}
