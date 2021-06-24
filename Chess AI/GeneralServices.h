#pragma once
#include "Board.h"
#include "Piece.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"
class Piece;
class GeneralServices
{
public:
	 void loadPosition(Board* board);
	 void savePosition(const Board* board);
	 std::string createPosition(const Board* board);
};

