#pragma once
#include <vector>
#include <stack>
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
enum class Color:uint8_t;
class Piece;
class Move;
class Board {
public:
	bool whiteCastleLeft = false, whiteCastleRight = false;
	bool blackCastleLeft = false, blackCastleRight = false;
	int numberOfMovesWhite = 0, numberOfMovesBlack = 0;
	Color whoMove;
	bool undoWhiteCastleLeft = false, undoWhiteCastleRight = false;
	bool undoBlackCastleLeft = false, undoBlackCastleRight = false;
	std::vector<Move> moveList;
	std::string moveNotationList;
	short int attackedWhite[8][8], attackedBlack[8][8];
	std::vector<Piece*> pieceList;
	Piece* capturedPiece;
	// stack capturedPieces
	Board();
	Board(const Board& board);
	~Board();
	std::pair<PieceCode, Piece*> board[8][8];
	bool makeMove(Move move);
	void doMove(Move* move);
	void makeAttackBoard();
	void basicMove(Move*);
	bool isValid(Move* move);
	bool testMove(Move move);
	void undoMove(Move* move);
	void basicUndoMove(Move* move);
	std::vector<Move>getAllMoves(Color color);
};