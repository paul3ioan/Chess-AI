#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:

    Queen(Color color, Position poz) : Piece(color, poz)
    {}

    std::vector<Move> getLegalMoves(const Board &board);

    PieceCode getPieceCode(Color color) override;
};

