//
// Created by paul on 27.08.2021.
//

#ifndef CHESSAI_STARTING_POSITION_H
#define CHESSAI_STARTING_POSITION_H

#include "gtest/gtest.h"
#include "BasicTest.h"
class Starting_Position :public ::testing::Test{
public:
    std::set<std::string> wrongMoves;
    int maxDepth = 0;
    int allMoves = -1;
    int possibleMoves = 0;
    Board board;
    virtual void SetUp()
    {
        std::string position  = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
//        std::string position  = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ";
        GeneralServices::restartPosition(board,position );
        board.makeAttackBoard();
        std::vector<Move> moves = board.getAllMoves(Color::white);
        allMoves = moves.size();
    }
    /// interface
    int testing(Board& board, int code)
    {

        return BasicTest::test(board, code, maxDepth);
    }
    virtual void TearDown() {
    }
};


#endif //CHESSAI_STARTING_POSITION_H
