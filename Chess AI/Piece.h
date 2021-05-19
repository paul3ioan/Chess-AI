#pragma once
#include <vector>
#include "Position.h"
enum class Color : uint8_t
{
	white, black
};
class Piece {
	Color color;
	std::pair<uint8_t, uint8_t> poz;
public:
	Piece(Color color, std::pair< uint8_t, uint8_t> poz ) : color(color), poz(poz)  {

	}
	virtual std::vector<std::pair< Position, Position> >getLegalMoves(/*tabla*/) = 0;
};