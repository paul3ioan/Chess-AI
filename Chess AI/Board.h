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
	Board()
	{
		for(int i =0 ;i <=7; i ++)
			for (int j = 0; j <= 7;j++)
			{
				this->board[i][j].first = PieceCode::empty;
				this->board[i][j].second = nullptr;
			}
	}
	Board(const Board& board) {
		for (int i = 0;i <= 7; i++)
			for (int j = 0; j <= 7;j++)
			{
				this->board[i][j] = board.board[i][j];
			}
//		std::cout << "MERGEMERGE";
	//	exit(0);
	}
	std::pair<PieceCode, Piece*> board[8][8];
	void makeMove(Move move);
	void makeAttackBoard();
};