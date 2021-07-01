#pragma once
#include <vector>
#include <iostream>
#include "Position.h"
#include "Board.h"
#include "Move.h"
enum class Color : uint8_t
{
	white, black
};
class Piece {

public:
	Color color;
	Position poz;
	
	Piece(Color color, Position poz ) : color(color), poz(poz)  {}
	
	virtual std::vector<Move> getLegalMoves(const Board& board) = 0;
	virtual PieceCode getPieceCode(Color color) = 0;
	bool checkDifferentColor(const Board& board, int line, int col, Color color);
	
};