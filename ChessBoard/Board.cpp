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

void Board::DrawBoard(char const playerColor) const
{
    string rank_range(rankRange);
    //string rank_range;
    //if (playerColor == 'w') rank_range = rankRange;
    //else rank_range = inverted_rankRange;

    cout << "    ";
    Board::_DrawEntireNonPositionLine(LineType::FileHeader, LineEndBegin::TopLine, fileRange);
    Board::_DrawEntireNonPositionLine(LineType::TopHorizontalLine, LineEndBegin::TopLine, fileRange);

    for (char const& rank : rank_range)
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
    for (std::list<ChessMan>::iterator king_it = kingFieldReactions.begin(); king_it != kingFieldReactions.end(); king_it++)
    {
        char reactingChessManColor(king_it->GetColor());
        if (reactingChessManColor != kingColor) return true;
    }
    return false;
}

bool Board::CheckMate(char const kingColor)
{
    //TODO write CheckMate function

    bool checkMate(true);

    string kingPosition(boardAttributes.kingsPositions.at(kingColor));

    std::list<string> kingMoves(boardAttributes.movesBoard.at(kingPosition));
    for (std::list<string>::iterator kingMoves_it = kingMoves.begin(); kingMoves_it != kingMoves.end(); kingMoves_it++)
    {
        if (!Check(kingColor, *kingMoves_it))
        {
            checkMate = false;
            break;
        }
    }

    std::list<ChessMan> kingFieldReactions(boardAttributes.reactionBoard.at(kingPosition));
    for (std::list<ChessMan>::iterator kingReactions_it = kingFieldReactions.begin(); kingReactions_it != kingFieldReactions.end(); kingReactions_it++)
    {
        //char reactingChessManColor(kingReactions_it->GetColor());
        //if (reactingChessManColor != kingColor) return true;
    }


    return checkMate;
}

bool Board::MakeMove(char const playerColor, string const actualPosition, string const newPosition)
{
    //TODO rafactor MakeMove to handle what to do with Pawn on last position

    CalculateMovesBoardAndReactionBoard();
    ChessMan& actualPositionChessMan(boardAttributes.boardState.at(actualPosition));
    ChessMan const copy_actualPositionChessMan(actualPositionChessMan);
    ChessMan& newPositionChessMan(boardAttributes.boardState.at(newPosition));
    ChessMan const copy_newPositionChessMan(newPositionChessMan);

    string& kingPosition(boardAttributes.kingsPositions.at(playerColor));

    if (copy_actualPositionChessMan.GetColor() == playerColor)
    {
        std::list<string> allowedMoves(boardAttributes.movesBoard.at(actualPosition));
        for (std::list<string>::iterator moves_itr = allowedMoves.begin(); moves_itr != allowedMoves.end(); moves_itr++)
        {
            if (newPosition == *moves_itr)
            {
                actualPositionChessMan = ChessMan(ChessManType::None, 0);
                newPositionChessMan = copy_actualPositionChessMan;
                if (copy_actualPositionChessMan.GetType() == ChessManType::King) kingPosition = newPosition;

                CalculateMovesBoardAndReactionBoard();
                if (Check(playerColor, kingPosition))
                {
                    cout << "Move is not allowed. The King is checked!" << endl;
                    actualPositionChessMan = copy_actualPositionChessMan;
                    newPositionChessMan = copy_newPositionChessMan;
                    if (copy_actualPositionChessMan.GetType() == ChessManType::King) kingPosition = actualPosition;
                    return false;
                }
                newPositionChessMan.ChangeFirstMove();
                return true;
            }
        }
    }

    cout << "Move is not allowed." << endl;
    return false;
}

void Board::PawnOnEndLine()
{
    //TODO finish
}


bool Board::NotFirstMove(char const file, char const rank)
{
    string chessManPosition(ConvertFileAndRankToPosition(file, rank));
    ChessMan chessManField(boardAttributes.boardState.at(chessManPosition));
    if (chessManField.CheckFirstMove() != true) return true;
    return false;
}

bool Board::NotEmpty(char const file, char const rank)
{
    string chessManPosition(ConvertFileAndRankToPosition(file, rank));
    ChessMan kingField(boardAttributes.boardState.at(chessManPosition));
    if (kingField.GetType() != ChessManType::None) return true;
    return false;
}

void Board::LookForCastling(char const playerColor, char const file, char const rank, string const file_range, int& cast, char& rookFileForCastling)
{
    if (NotFirstMove(file, rank))
    {
        cout << "Rook on " << file << rank << " was moved" << endl;
        cast = 0;
    }
    else
    {
        for (auto file_it = file_range.begin(); file_it != file_range.end(); file_it++)
        {
            if (Check(playerColor, ConvertFileAndRankToPosition(*file_it, rank)))
            {
                cout << "Move is not allowed. The King is checked!" << endl;
                cast = 0;
                break;
            }
            if (NotEmpty(*file_it, rank))
            {
                cast = 0;
                break;
            }
        }
        if (cast) rookFileForCastling = file;
    }
}

int Board::FindCastlings(char const playerColor, char& rookFileForCastling, char const castlingRank)
{
    int castlingA(1);
    int castlingH(1);

    char rook_fileA('a');
    char rook_fileH('h');
    char king_file('e');
    string empty_files_rookA("bcd");
    string empty_files_rookH("fg");

    if (NotFirstMove(king_file, castlingRank))
    {
        cout << "King was moved" << endl;
        return 0;
    }

    CalculateMovesBoardAndReactionBoard();
    if (Check(playerColor, ConvertFileAndRankToPosition(king_file, castlingRank)))
    {
        cout << "Move is not allowed. The King is checked!" << endl;
        return 0;
    }

    LookForCastling(playerColor, rook_fileA, castlingRank, empty_files_rookA, castlingA, rookFileForCastling);
    LookForCastling(playerColor, rook_fileH, castlingRank, empty_files_rookH, castlingH, rookFileForCastling);

    int castling(castlingA + castlingH);
    if (castling == 2) rookFileForCastling = 0;

    return castling;
}

void Board::MakeCastling(char const playerColor, char const rookFile, char const castlingRank)
{
    string file_range;
    if (rookFile == 'a') file_range = fileRange;
    else file_range = inverted_fileRange;

    string actualRookPosition(ConvertFileAndRankToPosition(rookFile, castlingRank));
    string actualKingPosition(ConvertFileAndRankToPosition('e', castlingRank));

    char const newRookFile(file_range[2]);
    char const newKingFile(file_range[1]);
    string newRookPosition(ConvertFileAndRankToPosition(newRookFile, castlingRank));
    string newKingPosition(ConvertFileAndRankToPosition(newKingFile, castlingRank));

    ChessMan& actualRookPositionField(boardAttributes.boardState.at(actualRookPosition));
    ChessMan& newRookPositionField(boardAttributes.boardState.at(newRookPosition));
    newRookPositionField = actualRookPositionField;
    newRookPositionField.ChangeFirstMove();
    actualRookPositionField = ChessMan(ChessManType::None, 0);

    ChessMan& actualKingPositionField(boardAttributes.boardState.at(actualKingPosition));
    ChessMan& newKingPositionField(boardAttributes.boardState.at(newKingPosition));
    newKingPositionField = actualKingPositionField;
    newKingPositionField.ChangeFirstMove();
    actualKingPositionField = ChessMan(ChessManType::None, 0);
}
