#include "Move.h"
#include "Board.h"
#include "Piece.h"
void basicMove(Board&, Move*, Color);
void Move::doMove(Board& board)
{
	Color variabila = Color::white;
	Piece* piece = this->piece;
	if (this->moveType == MoveType::basic or this->moveType == MoveType::doubleUp)
		basicMove(board, this, variabila);
	if (this->moveType == MoveType::king)
	{
		if (variabila == Color::white)
		{
			board.whiteCastleLeft = board.whiteCastleRight = 0;
			basicMove(board, this,variabila);
		}
		else
		{
			board.blackCastleLeft = board.blackCastleRight = 0;
			basicMove(board, this,variabila);
		}
	}
	if (this->moveType == MoveType::castle)
	{
		
		if(variabila == Color::white)
			board.whiteCastleLeft = board.whiteCastleRight = 0;
		else
			board.blackCastleLeft = board.blackCastleRight = 0;
		//move the king first
		basicMove(board, this,variabila);
		//move the rook
		int whichLine = variabila == Color::white ? 0 : 7;
		if (this->from.poz.second == 6)
		{
			
			Piece* movedRook = board.board[whichLine][7].second;
			board.board[whichLine][5] = { movedRook->getPieceCode(variabila),movedRook };
			board.board[whichLine][7] = { PieceCode::empty, nullptr };
		}
		if (this->from.poz.second == 2)
		{

			Piece* movedRook = board.board[whichLine][0].second;
			board.board[whichLine][3] = { movedRook->getPieceCode(variabila),movedRook };
			board.board[whichLine][0] = { PieceCode::empty, nullptr };
		}
	}
	if (this->moveType == MoveType::rook)
	{
		int whichLine = variabila == Color::white ? 0 : 7;
		if (this->from.poz.first == this->from.poz.second and this->from.poz.second == whichLine)
		{
			if (whichLine == 0)
			{
				this->from.poz.second == 0 ? board.whiteCastleLeft = 0 : board.whiteCastleRight = 0;
			}
			else
				this->from.poz.second == 0 ? board.blackCastleLeft = 0 : board.blackCastleRight = 0;
		}
		basicMove(board, this, variabila);
	}
	if (this->moveType == MoveType::promote)
	{
		remove(board.pieceList.begin(), board.pieceList.end(), this->piece);
		delete this->piece;
		// for now the new piece is a queen
			//Piece* newPiece = new Queen()
			//board.pieceList.push_back(newPiece);
			//board.board[this->to.poz.first][this->to.poz.second] = {newPiece->getPieceCode(variabila), newPiece};
	}
	if (this->moveType == MoveType::enpasant)
	{
		Piece* capturedPiece = board.board[this->from.poz.first][this->to.poz.second].second;
		remove(board.pieceList.begin(), board.pieceList.end(), capturedPiece);
		delete capturedPiece;
		board.board[this->from.poz.first][this->to.poz.second] = { PieceCode::empty, nullptr };
	}
}
void basicMove(Board& board, Move* move, Color color)
{
	Piece* piece = move->piece;
	// basic move implementation
		if (board.board[move->to.poz.first][move->to.poz.second].first == PieceCode::empty)
		{
			//hardcode Color::white 
			Color variabila = Color::white;
			board.board[move->to.poz.first][move->to.poz.second] = { piece->getPieceCode(variabila),piece };
			board.board[move->from.poz.first][move->from.poz.second] = { PieceCode::empty, nullptr };
		}
		else
		{
			Piece* capturedPiece = board.board[move->to.poz.first][move->to.poz.second].second;
			remove(board.pieceList.begin(), board.pieceList.end(), capturedPiece);
			delete capturedPiece;
			board.board[move->to.poz.first][move->to.poz.second] = { piece->getPieceCode(Color::white),piece };
			board.board[move->from.poz.first][move->from.poz.second] = { PieceCode::empty, nullptr };
		}
}