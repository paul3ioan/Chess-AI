#include <iostream>
#include "Piece.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"

int main()
{
	//Piece* king = new King(Color::white, Position({ '6','4' }));
	//Piece* pawn = new Pawn(Color::black, Position({'1','2'}));
	//Piece* pawn2 = new Pawn(Color::white, Position({ '2','3' }));
	//Piece* pawn3 = new Pawn(Color::white, Position({ '2', '1' }));
	//Piece* bishop = new Bishop(Color::white, Position({ '4','4' }));
	//Piece* rook = new Rook(Color::white, Position({ '4','4' }));
	Piece* knight = new Queen(Color::white, Position({ '0','4' }));
	Board board;
	board.board[0][4] = PieceCode::whiteQueen;
//	board.board[5][4] = PieceCode::whiteKing;
	//board.board[1][2] = PieceCode::blackPawn;
	//board.board[2][3] = PieceCode::whitePawn;
	//board.board[2][1] = PieceCode::whitePawn;
	//board.board[4][4] = PieceCode::whiteBishop;
//	board.board[4][4] = PieceCode::whiteRook;
	//Board de = new Board(board);
	std::vector<std::pair<Position, Position>> ans = knight->getLegalMoves(board);
	std::cout << ans.size() << '\n';
	for (auto i : ans)
	{
		std::cout  <<i.second.poz.first<<" "
			<<i.second.poz.second<< '\n';
	}
}