//
// Created by paul on 12.09.2021.
//

#ifndef CHESSAI_POSITION2_H
#define CHESSAI_POSITION2_H
#include "gtest/gtest.h"
#include "BasicTest.h"

class Position2 :public::testing::Test{
public:
    std::set<std::string> wrongMoves;
    int maxDepth = 0;
    int allMoves = -1;
    int possibleMoves = 0;
    Board board;
    virtual void SetUp()
    {
//        std::string position  = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/1R2K2R b KQkq - 0 1";
        std::string position  = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/1R2K2R w Kkq - 0 1 ";
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


#endif //CHESSAI_POSITION2_H
