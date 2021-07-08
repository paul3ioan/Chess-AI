#include "pch.h"
#include "BasicTest.h"

void BasicTest::Init()
{
	GeneralServices::loadPosition(board);
	std::vector<Move> moves = board.getAllMoves(Color::white);
	allMoves = moves.size();
}