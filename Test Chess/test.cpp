#include "pch.h"
#include "BasicTest.h"
/*
TEST_F(BasicTest, FirstPositionDepth0) {
	maxDepth = 0;
	EXPECT_EQ(8, allMoves);
	possibleMoves = test(board, 0);
	EXPECT_EQ(6, possibleMoves);
	for (auto move : wrongMoves)
		std::cout << move << " ";
	std::cout << '\n';
	//corect
}
*/
TEST_F(BasicTest, FirstPositionDepth1) {
	maxDepth = 1;
	possibleMoves = test(board, 0);
	EXPECT_EQ(42, possibleMoves);

	//32 undo loses the capturedPiece
	for (auto move : wrongMoves)
		std::cout << move<< " ";
	std::cout << '\n';
}
TEST_F(BasicTest, PieceList) {
	maxDepth = 0;
	int pieceListSize = board.pieceList.size();
	test(board, 0);
	EXPECT_EQ(pieceListSize, board.pieceList.size());
	// for first move
	maxDepth = 1;
	 pieceListSize = board.pieceList.size();
	test(board, 0);
	EXPECT_EQ(pieceListSize, board.pieceList.size());
	// for second move

}