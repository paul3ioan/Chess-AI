#include "Piece.h"
bool Piece::checkDifferentColor(const Board& board, int line, int col, Color color)
{
	if (board.board[line][col].first== PieceCode::empty)
		return true;
	if (color == Color::white)
	{
		if (board.board[line][col].first == PieceCode::whiteKing or
			board.board[line][col].first == PieceCode::whiteBishop or
			board.board[line][col].first == PieceCode::whiteKnight or
			board.board[line][col].first == PieceCode::whitePawn or
			board.board[line][col].first == PieceCode::whiteQueen or
			board.board[line][col].first == PieceCode::whiteRook)
			return false;
	}
	if (color == Color::black)
	{
		if (board.board[line][col].first == PieceCode::blackKing or
			board.board[line][col].first == PieceCode::blackBishop or
			board.board[line][col].first == PieceCode::blackKnight or
			board.board[line][col].first == PieceCode::blackPawn or
			board.board[line][col].first == PieceCode::blackQueen or
			board.board[line][col].first == PieceCode::blackRook)
			return false;
	}
	return true;
}