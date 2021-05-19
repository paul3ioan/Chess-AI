#pragma once
#include <vector>
#include "Piece.h"
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
	std::vector<Piece*> pieceList;
	PieceCode board[8][8];
	void makeMove(std::pair<Position, Position> move);
	
};