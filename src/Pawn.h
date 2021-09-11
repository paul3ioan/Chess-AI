#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(Color color, Position poz) : Piece(color, poz)
    {}

    std::vector<Move> getLegalMoves(const Board &board);

    PieceCode getPieceCode(Color color) override;
};

