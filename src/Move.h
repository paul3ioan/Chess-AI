#pragma once

#include "Position.h"
#include <memory>

class Board;

class Piece;

enum class MoveType : uint8_t
{
    castle,
    promoteQueen,
    promoteKnight,
    promoteBishop,
    promoteRook,
    basic,
    enpasant,
    doubleUp,
    king,
    rook
};

class Move
{
public:
    Move(Position from, Position to, MoveType moveType, std::shared_ptr<Piece> piece) : from(from), to(to),
                                                                                        moveType(moveType), piece(piece)
    {}

    Position from, to;
    MoveType moveType;
    std::shared_ptr<Piece> piece;

    void doMove(Board &board);
};

