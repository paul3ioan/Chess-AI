#pragma once
#include <vector>
#include <iostream>
#include "Position.h"
#include "Board.h"
enum class Color : uint8_t
{
	white, black
};
class Piece {
protected:
	Color color;
	Position poz;
public:
	Piece(Color color, Position poz ) : color(color), poz(poz)  {}
	virtual std::vector<std::pair< Position, Position>> getLegalMoves(const Board& board) = 0;
};