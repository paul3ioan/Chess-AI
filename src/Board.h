#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <memory>
#include "Position.h"

enum class PieceCode : uint8_t
{
    whiteKing,
    whiteQueen,
    whiteBishop,
    whiteKnight,
    whiteRook,
    whitePawn,

    blackKing,
    blackQueen,
    blackBishop,
    blackKnight,
    blackRook,
    blackPawn,

    empty
};
enum class Color : uint8_t;

class Piece;

class Move;

class Board
{
public:
    bool whiteCastleLeft = false, whiteCastleRight = false;
    bool blackCastleLeft = false, blackCastleRight = false;
    int numberOfMovesWhite = 0, numberOfMovesBlack = 0;
    Color whoMove;
    std::stack<std::shared_ptr<Piece>> capturedPieces;
    bool undoWhiteCastleLeft = false, undoWhiteCastleRight = false;
    bool undoBlackCastleLeft = false, undoBlackCastleRight = false;
    std::vector<Move> moveList;
    std::string moveNotationList;
    short int attackedWhite[8][8], attackedBlack[8][8];
    std::vector<std::shared_ptr<Piece>> pieceList;

    //Piece* capturedPiece;
    // stack capturedPieces
    Board();

    Board(const Board &board);

    ~Board();

    std::pair<PieceCode, std::shared_ptr<Piece>> board[8][8];

    bool makeMove(const Move &move);

    void doMove(const Move &move);

    void makeAttackBoard();

    void basicMove(const Move &move);

    bool isValid(const Move &move);

    bool testMove(const Move &move);

    void undoMove(const Move &move);

    void basicUndoMove(const Move &move);

    std::vector<Move> getAllMoves(Color color);
};