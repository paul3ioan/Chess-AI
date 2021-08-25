#include "pch.h"
#include "BasicTest.h"

TEST_F(BasicTest, FirstPositionDepth0) {
	maxDepth = 0;
	//debug();
	possibleMoves = test(board, 0);
	
	EXPECT_EQ(0, possibleMoves);
	//for (auto move : wrongMoves)
	//std::cout << move << " ";
	//std::cout << '\n';
		
	//corect
}
TEST_F(BasicTest, FirstPositionDepth1) {
	maxDepth = 1;
	possibleMoves = test(board, 0);
	EXPECT_EQ(42, possibleMoves);
}
	TEST_F(BasicTest, FirstPositionDepth2) {
		maxDepth = 2;
		possibleMoves = test(board, 0);
		EXPECT_EQ(42, possibleMoves);
	}

	//32 undo loses the capturedPiece
//	for (auto move : wrongMoves)
	//	std::cout << move<< " ";
//	std::cout << '\n';
/*
TEST_F(BasicTest, FirstPositionDepth2) {
	maxDepth = 2;
	possibleMoves = test(board, 0);
	EXPECT_EQ(42, possibleMoves);

}/*
TEST_F(BasicTest, FirstPositionDepth3) {
	maxDepth = 3;
	possibleMoves = test(board, 0);
	EXPECT_EQ(42, possibleMoves);


}*/