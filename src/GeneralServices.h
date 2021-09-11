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
    static void loadPosition(Board &board);

    static void savePosition(const Board &board);

    static std::string createPosition(const Board &board);

    static void restartPosition(Board &board, std::string positon);
};

