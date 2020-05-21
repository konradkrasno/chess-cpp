#include <iostream>
using std::cout;
using std::endl;

#include "Board.h"

Board::Board() : Move()
{
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

ChessMan Board::FindChessManOnBoard(char const file, char const rank) const
{
    string position(ConvertFileAndRankToPosition(file, rank));
    return boardAttributes.boardState.at(position);
}

void Board::CalculateMovesBoardAndReactionBoard()
{
    boardAttributes.movesBoard = boardAttributes.EmptyMovesBoard();
    boardAttributes.reactionBoard = boardAttributes.EmptyReactionBoard();

    for (char const& file : fileRange)
    {
        for (char const& rank : rankRange)
        {
            string position(ConvertFileAndRankToPosition(file, rank));
            ChessManPossibleMoves(position);
        }
    }
}

bool Board::Check(char const kingColor, string const kingPosition)
{
    std::list<ChessMan> kingFieldReactions(boardAttributes.reactionBoard.at(kingPosition));
    for (std::list<ChessMan>::iterator king_itr = kingFieldReactions.begin(); king_itr != kingFieldReactions.end(); king_itr++)
    {
        char reactingChessManColor(king_itr->GetColor());
        cout << "color: " << reactingChessManColor << endl;
        if (reactingChessManColor != kingColor) return true;
    }
    return false;
}

bool Board::CheckMate(char const kingColor, string const kingPosition)
{
    //bool checkmate(false);
    //std::list<string> kingPossibleMoves(attributes.movesBoard.at(kingPosition));
    //for (std::list<string>::iterator moves_itr = kingPossibleMoves.begin(); moves_itr != kingPossibleMoves.end(); moves_itr++)
    //{
    //    std::list<ChessMan> kingFieldReactions(attributes.reactionBoard.at(*moves_itr));
    //    for (std::list<ChessMan>::iterator reactions_itr = kingFieldReactions.begin(); reactions_itr != kingFieldReactions.end(); reactions_itr++)
    //    {
    //        char reactingChessManColor(reactions_itr->GetColor());
    //        if (reactingChessManColor != kingColor) checkmate = true;
    //    }
    //}
    return false;
}

bool Board::MakeMove(char const playerColor, string const actualPosition, string const newPosition)
{
    CalculateMovesBoardAndReactionBoard();
    ChessMan& actualPositionChessMan(boardAttributes.boardState.at(actualPosition));
    ChessMan const movedChessMan(actualPositionChessMan);
    string& kingPosition(boardAttributes.kingsPositions.at(playerColor));

    if (movedChessMan.GetColor() == playerColor)
    {
        std::list<string> allowedMoves(boardAttributes.movesBoard.at(actualPosition));
        for (std::list<string>::iterator moves_itr = allowedMoves.begin(); moves_itr != allowedMoves.end(); moves_itr++)
        {
            if (newPosition == *moves_itr)
            {
                actualPositionChessMan = ChessMan(ChessManType::None, 0);
                CalculateMovesBoardAndReactionBoard();
                if (Check(playerColor, kingPosition))
                {
                    cout << "Move is not allowed. The white King is checked!" << endl;
                    actualPositionChessMan = movedChessMan;
                    return false;
                }
                ChessMan& newPositionChessMan(boardAttributes.boardState.at(newPosition));
                newPositionChessMan = movedChessMan;
                if (movedChessMan.GetType() == ChessManType::King) kingPosition = newPosition;
                newPositionChessMan.ChangeFirstMove();
                return true;
            }
        }
    }

    if (actualPositionChessMan == movedChessMan)
    {
        cout << "Move is not allowed." << endl;
        return false;
    }
}
