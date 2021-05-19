#include "Board.h"

void Board::makeMove(std::pair<Position, Position> move)
{
	auto from = move.first.poz;
	auto to = move.second.poz;
	board[to.first][to.second] = board[from.first][from.second];
	board[from.first][from.second] = PieceCode::empty;
}
