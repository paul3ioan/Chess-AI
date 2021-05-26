#pragma once
#include <vector>
#include "Position.h"
//#include "Piece.h"
enum class PieceCode : uint8_t
{
	whiteKing,
	whiteQueen,
	whiteBishop,
	whiteKnight,
	whiteRook,
	whitePawn,

	blackKing,
	blackQueen,
	blackBishop,
	blackKnight,
	blackRook,
	blackPawn,

	empty
};
class Board {
public:
	//std::vector<Piece*> pieceList;
	Board()
	{
		for(int i =0 ;i <7; i ++)
			for (int j = 0; j < 7;j++)
			{
				this->board[i][j] = PieceCode::empty;
			}
	}
	Board(const Board& board) {
		for (int i = 0;i < 7; i++)
			for (int j = 0; j < 7;j++)
			{
				this->board[i][j] = board.board[i][j];
			}
//		std::cout << "MERGEMERGE";
	//	exit(0);
	}
	PieceCode board[8][8];
	void makeMove(std::pair<Position, Position> move);
	
};