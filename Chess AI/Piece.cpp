#include "Piece.h"
bool Piece::checkDifferentColor(const Board& board, int line, int col, Color color)
{
	if (board.board[line][col] == PieceCode::empty)
		return true;
	if (color == Color::white)
	{
		if (board.board[line][col] == PieceCode::whiteKing or
			board.board[line][col] == PieceCode::whiteBishop or
			board.board[line][col] == PieceCode::whiteKnight or
			board.board[line][col] == PieceCode::whitePawn or
			board.board[line][col] == PieceCode::whiteQueen or
			board.board[line][col] == PieceCode::whiteRook)
			return false;
	}
	if (color == Color::black)
	{
		if (board.board[line][col] == PieceCode::blackKing or
			board.board[line][col] == PieceCode::blackBishop or
			board.board[line][col] == PieceCode::blackKnight or
			board.board[line][col] == PieceCode::blackPawn or
			board.board[line][col] == PieceCode::blackQueen or
			board.board[line][col] == PieceCode::blackRook)
			return false;
	}
	return true;
}