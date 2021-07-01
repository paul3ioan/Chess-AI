#pragma once
#include <vector>
#include "Position.h"
//#include "King.h"
//#include "Pawn.h"
//#include "Bishop.h"
//#include "Rook.h"
//#include "Queen.h"
//#include "Knight.h"

//#include "Piece.h"
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
	bool whiteCastleLeft = true, whiteCastleRight = true;
	bool blackCastleLeft = true, blackCastleRight = true;
	std::vector<Move> moveList;
	std::string moveNotationList;
	short int attackedWhite[8][8], attackedBlack[8][8];
	std::vector<Piece*> pieceList;

	Board();
	Board(const Board& board);
	~Board();
	std::pair<PieceCode, Piece*> board[8][8];
	bool makeMove(Move move);
	void doMove(Move* move);
	void makeAttackBoard();
	void basicMove(Move*, Color color);
	bool isValid(Move* move);
	bool testMove(Move move);
	std::vector<Move>getAllMoves(Color color);
};