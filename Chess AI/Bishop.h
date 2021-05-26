#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(Color color, Position poz) : Piece(color, poz) {}
	std::vector<std::pair< Position, Position> >getLegalMoves(const Board& board);
};

