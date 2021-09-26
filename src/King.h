#pragma once

#include "Piece.h"

class King : public Piece
{
public:
    King(Color color, Position poz) : Piece(color, poz)
    {}

    std::vector<Move> getLegalMoves(const Board &board);

    PieceCode getPieceCode(Color color) override;
};

