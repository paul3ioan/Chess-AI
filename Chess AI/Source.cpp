#include <iostream>
#include<vector>
#include "Piece.h"
//#include "King.h"
//#include "Pawn.h"
//#include "Bishop.h"
//#include "Rook.h"
//#include "Queen.h"
//#include "Knight.h"
#include "Board.h"
#include "GeneralServices.h"
using namespace std;
int main()
{
	Board board;
	//Piece* pawn = new Queen(Color::white, Position({ '7', '0' }));
	
	//board.board[7][0] = PieceCode::whiteRook;
	//Piece* pawn1= new Knight(Color::black, Position({ '7', '4' }));
	//board.board[7][4] = PieceCode::blackKnight;
				
	//Piece* pawn2 = new Bishop(Color::white, Position({ '7', '2' }));
	//board.board[7][2] = PieceCode::whiteBishop;
				 
	//Piece* pawn3= new Queen(Color::white, Position({ '7', '3' }));
	//board.board[7][3] = PieceCode::whiteQueen;
				
	//Piece* pawn4= new King(Color::white, Position({ '7', '4' }));
	//board.board[7][4] = PieceCode::whiteKing;
				
	//Piece* pawn5= new Bishop(Color::white, Position({ '7', '5' }));
	//board.board[7][5] = PieceCode::whiteBishop;
				
	//Piece* pawn6= new Knight(Color::white, Position({ '7', '6' }));
	//board.board[7][6] = PieceCode::whiteKnight;
				
	//Piece* pawn7= new Rook(Color::white, Position({ '7', '7' }));
	//board.board[7][7] = PieceCode::whiteRook;

	//board.pieceList.push_back(pawn);
	//board.pieceList.push_back(pawn1);
	//board.pieceList.push_back(pawn2);
	//board.pieceList.push_back(pawn3);
	//board.pieceList.push_back(pawn4);
	//board.pieceList.push_back(pawn5);
	//board.pieceList.push_back(pawn6);
	//board.pieceList.push_back(pawn7);
	GeneralServices::loadPosition(board);
	//cout << board.pieceList.size() << '\n';
	//generalServices.savePosition(&board);
	board.makeAttackBoard(board);
	cout << "\n\n";
	for (int i = 0;i <= 7;i++, cout << '\n')
		for (int j = 0; j<= 7;j++)
			cout << board.attackedBlack[i][j] << " ";
}