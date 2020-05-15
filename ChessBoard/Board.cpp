#include <iostream>
using std::cout;
using std::endl;

#include "Board.h"
#include "subsidiary.h"

Board::Board()
{
    _boardState = _StartingBoard();
    _reactionBoard = _EmptyReactionBoard();
}

Board::~Board()
{
}

void Board::_DrawMiddle(LineType const lineType, char file, string chessManSymbol) const
{
    switch (lineType)
    {
    case LineType::FileHeader:
        cout << "  " << file << "    ";
        break;
    case LineType::TopHorizontalLine:
        cout << " ______";
        break;
    case LineType::VerticalLines:
        cout << "|" << "      ";
        break;
    case LineType::ChessManPlace:
        if (chessManSymbol.length() == 2)
        {
            cout << "|" << "  " << chessManSymbol << "  ";
        }
        else
        {
            cout << "|" << "  " << chessManSymbol << " ";
        }
        break;
    case LineType::VerticalAndHorizontalLines:
        cout << "|" << "______";
        break;
    default:
        break;
    }
}

void Board::_DrawEndBegin(LineEndBegin const lineEndBegin, char rank) const
{
    switch (lineEndBegin)
    {
    case LineEndBegin::TopLine:
        cout << endl;
        cout << "   ";
        break;
    case LineEndBegin::RankHeader:
        cout << "|" << endl;
        cout << " " << rank << " ";
        break;
    case LineEndBegin::InnerLine:
        cout << "|" << endl;
        cout << "   ";
        break;
    default:
        break;
    }
}

void Board::_DrawEntireNonPositionLine(LineType const lineType, LineEndBegin const lineEndBegin, string fileRange, char rank) const
{
    for (char const& file : fileRange)
    {
        Board::_DrawMiddle(lineType, file);
    }
    Board::_DrawEndBegin(lineEndBegin, rank);
}

void Board::_DrawEntirePositionLine(string fileRange, char rank) const
{
    for (char const& file : fileRange)
    {
        string chessManOnCurrentPositionSymbol(FindChessManOnBoard(file, rank).GetSymbol());
        if (chessManOnCurrentPositionSymbol != "None")
        {
            Board::_DrawMiddle(LineType::ChessManPlace, 0, chessManOnCurrentPositionSymbol);
        }
        else
        {
            Board::_DrawMiddle(LineType::VerticalLines);
        }
    }
    Board::_DrawEndBegin(LineEndBegin::InnerLine);
}

void Board::DrawBoard() const
{
    cout << "    ";
    Board::_DrawEntireNonPositionLine(LineType::FileHeader, LineEndBegin::TopLine, fileRange);
    Board::_DrawEntireNonPositionLine(LineType::TopHorizontalLine, LineEndBegin::TopLine, fileRange);

    for (char const& rank : rankRange)
    {
        Board::_DrawEntireNonPositionLine(LineType::VerticalLines, LineEndBegin::RankHeader, fileRange, rank);
        Board::_DrawEntirePositionLine(fileRange, rank);
        Board::_DrawEntireNonPositionLine(LineType::VerticalAndHorizontalLines, LineEndBegin::InnerLine, fileRange);
    }
    cout << endl;
}

std::map<string, ChessMan> Board::_StartingBoard()
{
    std::map<string, ChessMan> mapping;

    mapping.insert(std::pair<string, ChessMan>("a1", ChessMan(ChessManType::Rook, 'w')));
    mapping.insert(std::pair<string, ChessMan>("b1", ChessMan(ChessManType::Knight, 'w')));
    mapping.insert(std::pair<string, ChessMan>("c1", ChessMan(ChessManType::Bishop, 'w')));
    mapping.insert(std::pair<string, ChessMan>("d1", ChessMan(ChessManType::Queen, 'w')));
    mapping.insert(std::pair<string, ChessMan>("e1", ChessMan(ChessManType::King, 'w')));
    mapping.insert(std::pair<string, ChessMan>("f1", ChessMan(ChessManType::Bishop, 'w')));
    mapping.insert(std::pair<string, ChessMan>("g1", ChessMan(ChessManType::Knight, 'w')));
    mapping.insert(std::pair<string, ChessMan>("h1", ChessMan(ChessManType::Rook, 'w')));
    mapping.insert(std::pair<string, ChessMan>("a2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("b2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("c2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("d2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("e2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("f2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("g2", ChessMan(ChessManType::Pawn, 'w')));
    mapping.insert(std::pair<string, ChessMan>("h2", ChessMan(ChessManType::Pawn, 'w')));

    mapping.insert(std::pair<string, ChessMan>("a8", ChessMan(ChessManType::Rook, 'b')));
    mapping.insert(std::pair<string, ChessMan>("b8", ChessMan(ChessManType::Knight, 'b')));
    mapping.insert(std::pair<string, ChessMan>("c8", ChessMan(ChessManType::Bishop, 'b')));
    mapping.insert(std::pair<string, ChessMan>("d8", ChessMan(ChessManType::Queen, 'b')));
    mapping.insert(std::pair<string, ChessMan>("e8", ChessMan(ChessManType::King, 'b')));
    mapping.insert(std::pair<string, ChessMan>("f8", ChessMan(ChessManType::Bishop, 'b')));
    mapping.insert(std::pair<string, ChessMan>("g8", ChessMan(ChessManType::Knight, 'b')));
    mapping.insert(std::pair<string, ChessMan>("h8", ChessMan(ChessManType::Rook, 'b')));
    mapping.insert(std::pair<string, ChessMan>("a7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("b7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("c7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("d7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("e7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("f7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("g7", ChessMan(ChessManType::Pawn, 'b')));
    mapping.insert(std::pair<string, ChessMan>("h7", ChessMan(ChessManType::Pawn, 'b')));

    string emptyRankRange = "6543";
    for (char const& file : fileRange)
    {
        for (char const& rank : emptyRankRange)
        {
            string position(ConvertFileRandToPosition(file, rank));
            mapping.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
        }
    }
    return mapping;
}

std::map<string, std::list<string>> Board::_EmptyMovesBoard()
{
    std::map<string, std::list<string>> movesBoard;
    std::list<string> fields;

    for (char const& file : fileRange)
    {
        for (char const& rank : rankRange)
        {
            string position(ConvertFileRandToPosition(file, rank));
            movesBoard.insert(std::pair<string, std::list<string>>(position, fields));
        }
    }
    return movesBoard;
}

std::map<string, std::list<ChessMan>> Board::_EmptyReactionBoard()
{
    std::map<string, std::list<ChessMan>> reactionBoard;
    std::list<ChessMan> fields;

    for (char const& file : fileRange)
    {
        for (char const& rank : rankRange)
        {
            string position(ConvertFileRandToPosition(file, rank));
            reactionBoard.insert(std::pair<string, std::list<ChessMan>>(position, fields));
        }
    }
    return reactionBoard;
}

void Board::ChangeChessManPosition(string actual_position, string new_position)
{
    ChessMan& actual_cc = _boardState.at(actual_position);
    _boardState.at(new_position) = actual_cc;
    actual_cc = ChessMan(ChessManType::None, 0);
}

ChessMan Board::FindChessManOnBoard(char const file, char const rank) const
{
    string position(ConvertFileRandToPosition(file, rank));
    return _boardState.at(position);
}

void Board::MakeMove(string actual_position, string new_position)
{
    // TODO finish this function
}
