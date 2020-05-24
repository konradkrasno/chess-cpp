#include <iostream>
using std::cout;
using std::endl;
#define BOOST_TEST_MODULE testChess
#include <boost/test/included/unit_test.hpp>
#include "Move.h"
#include "ChessMan.h"
#include "Gameplay.h"


struct FakeBoardAttributesFixture
{
    FakeBoardAttributesFixture()
    {
        std::map<string, ChessMan> fakeBoardState;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                fakeBoardState.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
            }
        }
        fakeBoardState.at("b2") = ChessMan(ChessManType::Rook, 'w');
        fakeBoardState.at("g6") = ChessMan(ChessManType::Rook, 'w');
        fakeBoardState.at("e2") = ChessMan(ChessManType::Knight, 'w');
        fakeBoardState.at("b8") = ChessMan(ChessManType::Knight, 'w');
        fakeBoardState.at("d2") = ChessMan(ChessManType::Bishop, 'w');
        fakeBoardState.at("d1") = ChessMan(ChessManType::Queen, 'w');
        fakeBoardState.at("e1") = ChessMan(ChessManType::King, 'w');
        fakeBoardState.at("a6") = ChessMan(ChessManType::Pawn, 'w');
        fakeBoardState.at("g4") = ChessMan(ChessManType::Pawn, 'w');
        fakeBoardState.at("e4") = ChessMan(ChessManType::Pawn, 'w');

        fakeBoardState.at("b6") = ChessMan(ChessManType::Pawn, 'b');
        fakeBoardState.at("e5") = ChessMan(ChessManType::Pawn, 'b');
        fakeBoardState.at("d5") = ChessMan(ChessManType::Pawn, 'b');
        fakeBoardState.at("f4") = ChessMan(ChessManType::Pawn, 'b');
        fakeBoardState.at("h7") = ChessMan(ChessManType::Pawn, 'b');

        std::map<string, std::list<string>> fakeMovesBoard;
        std::list<string> emptyStringList;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                fakeMovesBoard.insert(std::pair<string, std::list<string>>(position, emptyStringList));
            }
        }

        std::map<string, std::list<ChessMan>> fakeReactionBoard;
        std::list<ChessMan> emptyChessManList;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                fakeReactionBoard.insert(std::pair<string, std::list<ChessMan>>(position, emptyChessManList));
            }
        }

        BoardAttributes fakeBoardAttributes;
        fakeBoardAttributes.boardState = fakeBoardState;
        fakeBoardAttributes.movesBoard = fakeMovesBoard;
        fakeBoardAttributes.reactionBoard = fakeReactionBoard;

        Move fakeMove;
        fakeMove.boardAttributes = fakeBoardAttributes;
        move = new Move;
        *move = fakeMove;

        Board fakeBoard;
        fakeBoard.boardAttributes = fakeBoardAttributes;
        board = new Board;
        *board = fakeBoard;

        Gameplay fakeGameplay;
        fakeGameplay.board = *board;
        gameplay = new Gameplay;
        *gameplay = fakeGameplay;
    }
    ~FakeBoardAttributesFixture()
    {
        delete move;
        delete board;
        delete gameplay;
    }
    Move* move;
    Board* board;
    Gameplay* gameplay;
};

struct FakeBoardFixture
{
    FakeBoardFixture()
    {
        Board board;
        fakeBoard = new Board;
        *fakeBoard = board;

        Gameplay gameplay;
        gameplay.board = *fakeBoard;
        fakeGameplay = new Gameplay;
        *fakeGameplay = gameplay;

    }
    ~FakeBoardFixture()
    {
        delete fakeBoard;
        delete fakeGameplay;
    }
    Board* fakeBoard;
    Gameplay* fakeGameplay;
};

struct EmptyBoardFixture
{
    EmptyBoardFixture()
    {
        std::map<string, ChessMan> emptyBoardState;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                emptyBoardState.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
            }
        }

        Board board;
        board.boardAttributes.boardState = emptyBoardState;
        emptyBoard = new Board;
        *emptyBoard = board;

        Gameplay gameplay;
        gameplay.board = *emptyBoard;
        emptyGameplay = new Gameplay;
        *emptyGameplay = gameplay;

    }
    ~EmptyBoardFixture()
    {
        delete emptyBoard;
        delete emptyGameplay;
    }
    Board* emptyBoard;
    Gameplay* emptyGameplay;
};



BOOST_AUTO_TEST_SUITE(MoveSuite)
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForRook, FakeBoardAttributesFixture)
{
    string testPosition("b2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "c2", "b1", "a2", "b3", "b4", "b5", "b6" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKnight, FakeBoardAttributesFixture)
{
    string testPosition("e2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "g1", "f4", "g3", "c1", "d4", "c3" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKnightOnEdge, FakeBoardAttributesFixture)
{
    string testPosition("b8");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "c6", "d7" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForBishop, FakeBoardAttributesFixture)
{
    string testPosition("d2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "e3", "f4", "c1", "c3", "b4", "a5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForQueen, FakeBoardAttributesFixture)
{
    string testPosition("d1");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "c1", "b1", "a1", "c2", "b3", "a4" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKing, FakeBoardAttributesFixture)
{
    string testPosition("e1");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;
    
    std::list<string> expectedMoves({ "f1", "f2" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForPawn, FakeBoardAttributesFixture)
{
    string testPosition("g4");
    move->boardAttributes.boardState.at("g4").ChangeFirstMove();
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "g5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForPawnWhenBlocked, FakeBoardAttributesFixture)
{
    string testPosition("e4");
    move->boardAttributes.boardState.at("g4").ChangeFirstMove();
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "d5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForPawnOnFirstLine, FakeBoardAttributesFixture)
{
    string testPosition("h7");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "g6", "h6", "h5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForEmptyField, FakeBoardAttributesFixture)
{
    string testPosition("a8");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    std::list<string> expectedMoves({});
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testWorkingUpdateReactionBoardForRook, FakeBoardAttributesFixture)
{
    move->ChessManPossibleMoves("b2");

    std::list<ChessMan> fields;
    fields = move->boardAttributes.reactionBoard.at("c2");
    std::list<ChessMan>::iterator it = fields.begin();
    ChessMan insertedChessMan(*it);
    ChessMan expectedChessMan(ChessManType::Rook, 'w');
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testWorkingUpdateReactionBoardForPawn, FakeBoardAttributesFixture)
{
    move->ChessManPossibleMoves("h7");

    std::list<ChessMan> fields;
    fields = move->boardAttributes.reactionBoard.at("g6");
    std::list<ChessMan>::iterator it = fields.begin();
    ChessMan insertedChessMan(*it);
    ChessMan expectedChessMan(ChessManType::Pawn, 'b');
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ChessManSuite)
BOOST_AUTO_TEST_CASE(testGetSymbol)
{
    ChessMan whiteRook(ChessMan(ChessManType::Rook, 'w'));
    BOOST_CHECK(whiteRook.GetSymbol() == "wR");
}
BOOST_AUTO_TEST_CASE(testlEqualOperator)
{
    ChessMan whiteRook1(ChessManType::Rook, 'w');
    ChessMan whiteRook2(ChessManType::Rook, 'w');
    BOOST_CHECK(whiteRook1 == whiteRook2);
}
BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(BoardSuite)
BOOST_FIXTURE_TEST_CASE(testCalculateStateBoardAndReactionBoard, FakeBoardAttributesFixture)
{
    string testPosition1("b2");
    string testPosition2("g6");

    board->CalculateMovesBoardAndReactionBoard();
    board->CalculateMovesBoardAndReactionBoard();

    std::list<string> possibleMovesFromPosition1(board->boardAttributes.movesBoard.at(testPosition1));
    cout << "moves: " << endl;
    for (auto it = possibleMovesFromPosition1.begin(); it != possibleMovesFromPosition1.end(); it++) cout << *it << endl;
    std::list<string> expectedMovesFromPosition1({ "c2", "b1", "a2", "b3", "b4", "b5", "b6" });

    std::list<string> possibleMovesFromPosition2(board->boardAttributes.movesBoard.at(testPosition2));
    cout << "moves: " << endl;
    for (auto it = possibleMovesFromPosition2.begin(); it != possibleMovesFromPosition2.end(); it++) cout << *it << endl;
    std::list<string> expectedMovesFromPosition2({ "h6", "g5", "f6", "e6", "d6", "c6", "b6", "g7", "g8" });

    BOOST_CHECK(possibleMovesFromPosition1 == expectedMovesFromPosition1);
    BOOST_CHECK(possibleMovesFromPosition2 == expectedMovesFromPosition2);

    std::list<ChessMan> fields;
    fields = board->boardAttributes.reactionBoard.at("b6");
    std::list<ChessMan>::iterator fields_itr;
    for (auto fields_itr = fields.begin(); fields_itr != fields.end(); fields_itr++)
    {
        ChessMan insertedChessMan(*fields_itr);
        ChessMan expectedChessMan(ChessManType::Rook, 'w');
        BOOST_CHECK(insertedChessMan == expectedChessMan);
    }
    BOOST_CHECK(fields.size() == 2);
}

BOOST_FIXTURE_TEST_CASE(testCheckIsFalseWhenFieldHasNoReactions, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("a8");

    board->CalculateMovesBoardAndReactionBoard();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckIsFalseWhenFieldHasReactions, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("e1");

    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'w');
    board->CalculateMovesBoardAndReactionBoard();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckIsTrue, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("e1");

    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'b');
    board->CalculateMovesBoardAndReactionBoard();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == true);
}

BOOST_FIXTURE_TEST_CASE(testMakeMoveToEmptyField, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "b4");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b4"));
    ChessMan expectedChessMan(ChessMan(ChessManType::Rook, 'w'));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testCapture, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "b6");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b6"));
    ChessMan expectedChessMan(ChessMan(ChessManType::Rook, 'w'));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveToNotEmptyField, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "d2");
    ChessMan insertedChessManD2(board->boardAttributes.boardState.at("d2"));
    ChessMan expectedChessManD2(ChessMan(ChessManType::Bishop, 'w'));
    BOOST_CHECK(insertedChessManD2 == expectedChessManD2);
    ChessMan insertedChessManB2(board->boardAttributes.boardState.at("b2"));
    ChessMan expectedChessManB2(ChessMan(ChessManType::Rook, 'w'));
    BOOST_CHECK(insertedChessManB2 == expectedChessManB2);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByDifferentColor, FakeBoardAttributesFixture)
{
    board->MakeMove('b', "b2", "b4");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b4"));
    ChessMan expectedChessMan(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}

////////////////////////////
// MakeMove when Check tests
////////////////////////////
BOOST_FIXTURE_TEST_CASE(testMakeMoveByNotKingCauseCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("a1") = ChessMan(ChessManType::Rook, 'b');

    board->MakeMove('w', "d1", "b3");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("b3"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("d1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::Queen, 'w'));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByKingCauseCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("c5") = ChessMan(ChessManType::Bishop, 'b');

    board->MakeMove('w', "e1", "f2");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("f2"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("e1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::King, 'w'));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByNotKingWhenCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Bishop, 'b');

    board->MakeMove('w', "d1", "d3");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("d3"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("d1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::Queen, 'w'));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testEscapeByKingWhenCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Bishop, 'b');

    board->MakeMove('w', "e1", "f1");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("f1"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::King, 'w'));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("e1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}

BOOST_FIXTURE_TEST_CASE(testMakeMoveByQueenToAvoidCheck, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("e7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("e4") = ChessMan(ChessManType::Queen, 'w');

    fakeBoard->MakeMove('b', "d8", "e7");
    ChessMan insertedChessManF2(fakeBoard->boardAttributes.boardState.at("e7"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Queen, 'b'));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(fakeBoard->boardAttributes.boardState.at("d8"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByBishopToAvoidCheck, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("a4") = ChessMan(ChessManType::Bishop, 'w');

    fakeBoard->MakeMove('b', "c8", "d7");
    ChessMan insertedChessManF2(fakeBoard->boardAttributes.boardState.at("d7"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Bishop, 'b'));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(fakeBoard->boardAttributes.boardState.at("c8"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testCaptureByPawnToAvoidCheck, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b5") = ChessMan(ChessManType::Bishop, 'w');
    fakeBoard->boardAttributes.boardState.at("a7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("a6") = ChessMan(ChessManType::Pawn, 'b');

    fakeBoard->MakeMove('b', "a6", "b5");
    ChessMan insertedChessManF2(fakeBoard->boardAttributes.boardState.at("b5"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Pawn, 'b'));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(fakeBoard->boardAttributes.boardState.at("a6"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}

///////////////////////////
// Castling tests for Board
///////////////////////////
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenCollision, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenRookIsMoved, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("a8").ChangeFirstMove();

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenKingIsMoved, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("e8").ChangeFirstMove();

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenOneCastlingWithRookA, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 1);
    BOOST_CHECK(rookFileForCastling == 'a');
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenOneCastlingWithRookH, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 1);
    BOOST_CHECK(rookFileForCastling == 'h');
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenTwoCastlings, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 2);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingWhenKingIsChecked, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("f6") = ChessMan(ChessManType::Knight, 'w');

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenCastlingFieldIsCheckedVariant1, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("g7") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("g5") = ChessMan(ChessManType::Rook, 'w');

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenCastlingFieldIsCheckedVariant2, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f7") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("f5") = ChessMan(ChessManType::Rook, 'w');

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}

BOOST_FIXTURE_TEST_CASE(testMakeCastlingForRookOnFileA, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);

    fakeBoard->MakeCastling('w', 'a', '1');

    ChessMan insertedKing(fakeBoard->boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w'));
    ChessMan insertedRook(fakeBoard->boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w'));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testMakeCastlingForRookOnFileH, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("g1") = ChessMan(ChessManType::None, 0);

    fakeBoard->MakeCastling('w', 'h', '1');

    ChessMan insertedKing(fakeBoard->boardAttributes.boardState.at("g1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w'));
    ChessMan insertedRook(fakeBoard->boardAttributes.boardState.at("f1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w'));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}

////////////////////////////
// CheckMate tests for Board
////////////////////////////
BOOST_FIXTURE_TEST_CASE(testCheckMateIfTrueVariant1, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w');
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";

    emptyBoard->boardAttributes.boardState.at("g2") = ChessMan(ChessManType::Queen, 'b');
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b');

    emptyBoard->CalculateMovesBoardAndReactionBoard();
    bool checkMate(emptyBoard->CheckMate(playerColor));
    
    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateIfTrueVariant2, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w');
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";
    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Rook, 'w');

    emptyBoard->boardAttributes.boardState.at("g2") = ChessMan(ChessManType::Queen, 'b');
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b');
    emptyBoard->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Rook, 'b');

    emptyBoard->CalculateMovesBoardAndReactionBoard();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateIfFalseVariant1, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w');
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";
    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Rook, 'w');

    emptyBoard->boardAttributes.boardState.at("g2") = ChessMan(ChessManType::Queen, 'b');
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b');

    emptyBoard->CalculateMovesBoardAndReactionBoard();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateIfFalseVariant2, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w');
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";
    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Rook, 'w');

    emptyBoard->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Rook, 'b');
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b');

    emptyBoard->CalculateMovesBoardAndReactionBoard();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == false);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(GameplaySuite)
BOOST_AUTO_TEST_CASE(testValidateInputIfValid)
{
    string input("f3");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == true);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfToLong)
{
    string input("ewr");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfInverted)
{
    string input("4d");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfFileOutOfRange)
{
    string input("k4");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfRankOutOfRange)
{
    string input("c9");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}

BOOST_AUTO_TEST_CASE(testMakeLowercaseWithCoordinates)
{
    string input("D6");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.MakeLowercase(input) == "d6");
}
BOOST_AUTO_TEST_CASE(testMakeLowercaseWithString)
{
    string input("Draw BOArD");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.MakeLowercase(input) == "draw board");
}

//////////////////////////////
// Castling tests for Gameplay
//////////////////////////////
BOOST_FIXTURE_TEST_CASE(testCastlingWhenNoCastling, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenOneCastling, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w'));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w'));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenTwoCastlings, FakeBoardFixture)
{
    //    TODO mock input

    //board->boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    //board->boardAttributes.boardState.at("b2") = ChessMan(ChessManType::None, 0);
    //board->boardAttributes.boardState.at("a1") = ChessMan(ChessManType::Rook, 'w');

    //board->boardAttributes.boardState.at("g6") = ChessMan(ChessManType::None, 0);
    //board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'w');

    //gameplay->Castling('w');

    //ChessMan insertedKing(gameplay->board.boardAttributes.boardState.at("g1"));
    //ChessMan expectedKing(ChessMan(ChessManType::King, 'w'));
    //ChessMan insertedRook(gameplay->board.boardAttributes.boardState.at("f1"));
    //ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w'));

    //BOOST_CHECK(insertedKing == expectedKing);
    //BOOST_CHECK(insertedRook == expectedRook);
}

BOOST_FIXTURE_TEST_CASE(testCastlingWhenKingWasMoved, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("e1").ChangeFirstMove();

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenRookWasMoved, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("g1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("h1").ChangeFirstMove();

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("f1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("g1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenKingIsChecked, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("e2") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("e5") = ChessMan(ChessManType::Rook, 'b');

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenCastlingFieldsIsChecked, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("d2") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d5") = ChessMan(ChessManType::Rook, 'b');

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}

///////////////////////////////
// CheckMate tests for Gameplay
///////////////////////////////
BOOST_FIXTURE_TEST_CASE(testCheckMateVariant1, FakeBoardAttributesFixture)
{
    //TODO finish this test
}
BOOST_AUTO_TEST_SUITE_END()
