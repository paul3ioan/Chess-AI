#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(Color color, Position poz) : Piece(color, poz)
    {}

    std::vector<Move> getLegalMoves(const Board &board);

    PieceCode getPieceCode(Color color) override;
};

