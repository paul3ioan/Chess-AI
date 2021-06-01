#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:

	Queen(Color color, Position poz) : Piece(color, poz) {}
	std::vector<std::pair< Position, Position> >getLegalMoves(const Board& board);
};
