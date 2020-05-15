#include <iostream>
using std::cout;
using std::endl;
#define BOOST_TEST_MODULE testChess
#include <boost/test/included/unit_test.hpp>
#include "Move.h"
#include "ChessMan.h"

struct BoardFixture
{
    BoardFixture()
    {
        std::map<string, ChessMan> boardState;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileRandToPosition(file, rank));
                boardState.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
            }
        }
        boardState.at("b2") = ChessMan(ChessManType::Rook, 'w');
        boardState.at("e2") = ChessMan(ChessManType::Knight, 'w');
        boardState.at("d2") = ChessMan(ChessManType::Bishop, 'w');
        boardState.at("d1") = ChessMan(ChessManType::Queen, 'w');
        boardState.at("e1") = ChessMan(ChessManType::King, 'w');
        boardState.at("a6") = ChessMan(ChessManType::Pawn, 'w');
        boardState.at("d6") = ChessMan(ChessManType::Pawn, 'w');
        boardState.at("g4") = ChessMan(ChessManType::Pawn, 'w');
        boardState.at("g3") = ChessMan(ChessManType::Pawn, 'w');
        boardState.at("b6") = ChessMan(ChessManType::Pawn, 'b');
        boardState.at("e5") = ChessMan(ChessManType::Pawn, 'b');
        boardState.at("d5") = ChessMan(ChessManType::Pawn, 'b');
        boardState.at("f4") = ChessMan(ChessManType::Pawn, 'b');
        boardState.at("h5") = ChessMan(ChessManType::Pawn, 'b');
        state = new std::map<string, ChessMan>;
        *state = boardState;

        std::map<string, std::list<string>> movesBoard;
        std::list<string> emptyStringList;

        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileRandToPosition(file, rank));
                movesBoard.insert(std::pair<string, std::list<string>>(position, emptyStringList));
            }
        }
        moves = new std::map<string, std::list<string>>;
        *moves = movesBoard;


        std::map<string, std::list<ChessMan>> reactionBoard;
        std::list<ChessMan> emptyChessManList;

        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileRandToPosition(file, rank));
                reactionBoard.insert(std::pair<string, std::list<ChessMan>>(position, emptyChessManList));
            }
        }
        reactions = new std::map<string, std::list<ChessMan>>;
        *reactions = reactionBoard;
    }
    ~BoardFixture()
    {
        delete state;
        delete moves;
        delete reactions;
    }
    std::map<string, ChessMan>* state;
    std::map<string, std::list<string>>* moves;
    std::map<string, std::list<ChessMan>>* reactions;
};

BOOST_AUTO_TEST_SUITE(MoveSuite)
BOOST_FIXTURE_TEST_CASE(testChassManPosibleMovesForRook, BoardFixture)
{
    string testPosition("b2");
    Move rook;
    rook.ChessManPosibleMoves(testPosition, *moves, *state, *reactions);

    std::map<string, std::list<string>> moves(*moves);
    std::list<string> possibleMoves(moves.at(testPosition));
    std::list<string>::iterator it;
    cout << "moves: " << endl;
    for (it = possibleMoves.begin(); it != possibleMoves.end(); ++it) cout << *it << endl;

    std::list<string> expectedMoves({ "c2", "a2", "b1", "b3", "b4", "b5", "b6" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testWorkingUpdateReactionBoard, BoardFixture)
{
    Move rook;
    rook.ChessManPosibleMoves("b2", *moves, *state, *reactions);

    std::map<string, std::list<ChessMan>> reactions(*reactions);
    std::list<ChessMan> fields;
    fields = reactions.at("c2");
    std::list<ChessMan>::iterator it = fields.begin();
    ChessMan insertedChessMan(*it);
    ChessMan expectedChessMan(ChessManType::Rook, 'w');
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
BOOST_FIXTURE_TEST_CASE(testCalculateStateBoardAndReactionBoard, BoardFixture)
{
    // TODO finih this test and write code to do it
    Board board;
    board.CalculateMovesBoardAndReactionBoard(*moves, *reactions);

}
BOOST_AUTO_TEST_SUITE_END()
