#pragma once
#include "Piece.h"
class Pawn:public Piece
{
public:
	Pawn(Color color, Position poz) : Piece(color, poz) {}
	std::vector<std::pair< Position, Position> >getLegalMoves(const Board& board);
	PieceCode getPieceCode(Color color) override;
};

