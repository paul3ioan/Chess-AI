#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(Color color, Position poz): Piece(color, poz){}
	std::vector<std::pair< Position, Position> >getLegalMoves(const Board& board);
};

