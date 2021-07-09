#include "pch.h"
#include "BasicTest.h"

#include <iostream>
#include <set>


int BasicTest::test(Board& board, int depth)
{
	//boardul cand isi ia undoMove pierde capturedPieceul daca se captureaza la urm mutare o piesa
	std::vector<Move> moves;
	int ans = 0;
	if (depth % 2 == 0)
		moves = board.getAllMoves(Color::white);
	else
		moves = board.getAllMoves(Color::black);
	// moves pe black nu da mutari
	//pionii in makeAttack ataca si campul din fata DONE
	for (auto move : moves)
	{

		if (!board.makeMove(move))
		{
			auto from = move.from.poz;
			auto to = move.to.poz;
			// make move in moveList

			//make the notation of the move
			std::string moveCode;
			char fromLine = '8' - from.first, fromCol = from.second + 'a';
			char toLine = '8' - to.first, toCol = to.second + 'a';
			moveCode += fromCol;
			moveCode += fromLine;
			moveCode += toCol;
			moveCode += toLine;
			moveCode += ' ';
			wrongMoves.insert(moveCode);
			continue;
		}
		if (depth >= maxDepth)
		{
			ans++;
			board.undoMove(&move);
			continue;
		}
		Board newBoard = board;
		ans += test(newBoard, depth + 1);
		board.undoMove(&move);
	}
	return ans;
}