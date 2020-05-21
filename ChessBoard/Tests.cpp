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
    }
    ~FakeBoardAttributesFixture()
    {
        delete move;
        delete board;
    }
    Move* move;
    Board* board;
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

BOOST_FIXTURE_TEST_CASE(testCheckIfFalseWhenFieldHasNoReactions, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("a8");

    board->CalculateMovesBoardAndReactionBoard();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckIfFalseWhenFieldHasReactions, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("e1");

    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'w');
    board->CalculateMovesBoardAndReactionBoard();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckIfTrue, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("e1");

    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'b');
    board->CalculateMovesBoardAndReactionBoard();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == true);
}

BOOST_FIXTURE_TEST_CASE(testCheckMate, FakeBoardAttributesFixture)
{
    //TODO finish this test
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
BOOST_FIXTURE_TEST_CASE(testMakeMoveToNotToEmptyField, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "d2");
    ChessMan insertedChessManD2(board->boardAttributes.boardState.at("d2"));
    ChessMan expectedChessManD2(ChessMan(ChessManType::Bishop, 'w'));
    BOOST_CHECK(insertedChessManD2 == expectedChessManD2);
    ChessMan insertedChessManB2(board->boardAttributes.boardState.at("b2"));
    ChessMan expectedChessManB2(ChessMan(ChessManType::Rook, 'w'));
    BOOST_CHECK(insertedChessManB2 == expectedChessManB2);

}
BOOST_FIXTURE_TEST_CASE(testMakeMoveWhenCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("g6") = ChessMan(ChessManType::None, 0);
    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'b');
    board->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::Rook, 'w');

    board->MakeMove('w', "f1", "f2");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("f2"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("f1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::Rook, 'w'));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByWrongColor, FakeBoardAttributesFixture)
{
    board->MakeMove('b', "b2", "b4");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b4"));
    ChessMan expectedChessMan(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}

//TODO write this test
//BOOST_FIXTURE_TEST_CASE(testMakeMoveByKing, BoardAttributesFixture)
//{
//    Board board;
//    board.MakeMove('b', *state, *moves, *reactions, "b2", "b4");
//    ChessMan insertedChessMan(state->at("b4"));
//    ChessMan expectedChessMan(ChessMan(ChessManType::None, 0));
//    BOOST_CHECK(insertedChessMan == expectedChessMan);
//}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(GameplaySuite)
BOOST_AUTO_TEST_CASE(testValidateInputIfValid)
{
    string input("f3");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidateInput(input) == true);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfInvalid)
{
    string input("ewr");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidateInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfExit)
{
    string input("exit");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidateInput(input) == true);
}
BOOST_AUTO_TEST_SUITE_END()
