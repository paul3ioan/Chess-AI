#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(Color color, Position poz) : Piece(color, poz) {}
	std::vector<std::pair< Position, Position> >getLegalMoves(const Board& board);
	PieceCode getPieceCode(Color color) override;
};

