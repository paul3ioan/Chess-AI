#pragma once
#include "../Chess AI/Board.h"
#include "GeneralServices.h"
#include "Move.h"
class BasicTest : public ::testing::Test
{
protected:
	std::set<std::string> wrongMoves;
	int maxDepth = 0;
	int allMoves = -1;
	int possibleMoves = 0;
	Board board;
	virtual void SetUp()
	{	
		GeneralServices::loadPosition(board);
		GeneralServices::savePosition(board);
		board.makeAttackBoard();
		std::vector<Move> moves = board.getAllMoves(Color::white);
		allMoves = moves.size();
	}

	virtual void TearDown() {
	}
	int test(Board&, int);
};

