#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(Color color, Position poz) : Piece(color, poz)
    {}

    std::vector<Move> getLegalMoves(const Board &board);

    PieceCode getPieceCode(Color color) override;
};

