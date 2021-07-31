#include "pch.h"
#include "BasicTest.h"

#include <iostream>
#include <set>


int BasicTest::test(Board& board, int depth)
{
	//boardul cand isi ia undoMove pierde capturedPieceul daca se captureaza la urm mutare o piesa
	std::vector<Move> moves;
	int ans = 0;
	int see = 0;
	if (board.whoMove == Color::white)
		moves = board.getAllMoves(Color::white);
	else
		moves = board.getAllMoves(Color::black);
	// moves pe black nu da mutari
	//pionii in makeAttack ataca si campul din fata DONE
	int contor = 0;
	for (auto move : moves)
	{
	//	std::cout << char(move.from.poz.second + 'a') << 8 - move.from.poz.first <<
		//	char(move.to.poz.second + 'a') << 8 - move.to.poz.first << '\n';

		if (depth == 0)
			see = 0;
		if (!board.makeMove(move))
		{
			auto from = move.from.poz;
			auto to = move.to.poz;
			// make move in moveList
		//	if (board.capturedPiece != nullptr)
			//	captureMoves++;
			///make the notation of the move
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
			// aici ceva nu e bine
			if (move.moveType == MoveType::promote)
				ans += 4, see +=4;
			else
				ans++, see ++;
			board.undoMove(&move);
			continue;
		}
		Board newBoard = board;
		newBoard.whoMove = (newBoard.whoMove == Color::white ? Color::black : Color::white);
		ans +=see = test(newBoard, depth + 1);
		
		board.undoMove(&move);
		if (depth == 0) std::cout <<char(move.from.poz.second+'a') <<8 - move.from.poz.first<<
			char(move.to.poz.second + 'a') << 8 -move.to.poz.first <<": " <<see << '\n';
	}
	return ans;
}