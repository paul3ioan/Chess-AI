#include "gtest/gtest.h"
#include "Starting_Position.h"

/// initial position

TEST_F(Starting_Position, FirstPositionDepth1) {
	maxDepth = 0;

	possibleMoves = testing(board, 0);
	
	EXPECT_EQ(20, possibleMoves);

}
TEST_F(Starting_Position, FirstPositionDepth2) {
	maxDepth = 1;
	possibleMoves = testing(board, 0);
	EXPECT_EQ(400, possibleMoves);
}
	TEST_F(Starting_Position, FirstPositionDepth3) {
		maxDepth = 2;
		possibleMoves = testing(board, 0);
		EXPECT_EQ(8902, possibleMoves);
	}

TEST_F(Starting_Position, FirstPositionDepth4) {
	maxDepth = 3;
	possibleMoves = testing(board, 0);
	EXPECT_EQ(197281, possibleMoves);
}
///end of initial position