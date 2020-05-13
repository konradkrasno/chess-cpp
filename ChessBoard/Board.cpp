#include <iostream>
using std::cout;
using std::endl;

#include "Board.h"
#include "subsidiary.h"

Board::Board()
{
    _boardMapping = _StartingBoard();
}

Board::~Board()
{
}

void Board::_DrawMiddle(LineType const lineType, char file, string chessMan) const
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
        if (chessMan.length() == 2)
        {
            cout << "|" << "  " << chessMan << "  ";
        }
        else
        {
            cout << "|" << "  " << chessMan << " ";
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
        string chessManOnCurrentPosition(FindChessManOnBoard(file, rank).GetSymbol());
        if (chessManOnCurrentPosition != "none")
        {
            Board::_DrawMiddle(LineType::ChessManPlace, 0, chessManOnCurrentPosition);
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

    mapping.insert(std::pair<string, ChessMan>("a1", ChessMan("wR", "Rook", "white")));
    mapping.insert(std::pair<string, ChessMan>("b1", ChessMan("wKn", "Knight", "white")));
    mapping.insert(std::pair<string, ChessMan>("c1", ChessMan("wB", "Bishop", "white")));
    mapping.insert(std::pair<string, ChessMan>("d1", ChessMan("wQ", "Queen", "white")));
    mapping.insert(std::pair<string, ChessMan>("e1", ChessMan("wKi", "King", "white")));
    mapping.insert(std::pair<string, ChessMan>("f1", ChessMan("wB", "Bishop", "white")));
    mapping.insert(std::pair<string, ChessMan>("g1", ChessMan("wKn", "Knight", "white")));
    mapping.insert(std::pair<string, ChessMan>("h1", ChessMan("wR", "Rook", "white")));
    mapping.insert(std::pair<string, ChessMan>("a2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("b2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("c2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("d2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("e2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("f2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("g2", ChessMan("wp", "Pawn", "white")));
    mapping.insert(std::pair<string, ChessMan>("h2", ChessMan("wp", "Pawn", "white")));

    mapping.insert(std::pair<string, ChessMan>("a8", ChessMan("bR", "Rook", "black")));
    mapping.insert(std::pair<string, ChessMan>("b8", ChessMan("bKn", "Knight", "black")));
    mapping.insert(std::pair<string, ChessMan>("c8", ChessMan("bB", "Bishop", "black")));
    mapping.insert(std::pair<string, ChessMan>("d8", ChessMan("bQ", "Queen", "black")));
    mapping.insert(std::pair<string, ChessMan>("e8", ChessMan("bKi", "King", "black")));
    mapping.insert(std::pair<string, ChessMan>("f8", ChessMan("bB", "Bishop", "black")));
    mapping.insert(std::pair<string, ChessMan>("g8", ChessMan("bKn", "Knight", "black")));
    mapping.insert(std::pair<string, ChessMan>("h8", ChessMan("bR", "Rook", "black")));
    mapping.insert(std::pair<string, ChessMan>("a7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("b7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("c7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("d7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("e7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("f7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("g7", ChessMan("bp", "Pawn", "black")));
    mapping.insert(std::pair<string, ChessMan>("h7", ChessMan("bp", "Pawn", "black")));

    string emptyRankRange = "3456";
    for (char const& file : fileRange)
    {
        for (char const& rank : emptyRankRange)
        {
            string position(ConvertFileRandToPosition(file, rank));
            mapping.insert(std::pair<string, ChessMan>(position, ChessMan("none", "none", "none")));
        }
    }
    return mapping;
}

void Board::ChangeChessManPosition(string actual_position, string new_position)
{
    ChessMan& actual_cc = _boardMapping.at(actual_position);
    _boardMapping.at(new_position) = actual_cc;
    actual_cc = ChessMan("none", "none", "none");
}

ChessMan Board::FindChessManOnBoard(char const file, char const rank) const
{
    string position(ConvertFileRandToPosition(file, rank));
    return _boardMapping.at(position);
}

void Board::MakeMove(string actual_position, string new_position)
{
    // TODO finish this function
}
