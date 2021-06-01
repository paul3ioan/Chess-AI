#include "Board.h"

void Board::makeMove(std::pair<Position, Position> move)
{
	// make move on board
	auto from = move.first.poz;
	auto to = move.second.poz;
	board[to.first][to.second] = board[from.first][from.second];
	board[from.first][from.second] = PieceCode::empty;
	// make move in moveList
	std::string moveCode;
	from.first = from.first + 'a' - '0';
	to.first = from.first + 'a' - '0';
	moveCode += from.first;
	moveCode += from.second;
	moveCode += to.first;
	moveCode += to.first;
	moveList += moveCode;
}
void Board::makeAttackBlack(const Board* board)
{
	for (int i = 0;i < 8;i++)
		for (int j = 0; j < 8;j++)
			attackedWhite[i][j] = false;
	//reset attacked board for white
	for (auto piece : pieceList)
	{
		if (piece->color == Color::white)
			continue;
		auto moves = piece->getLegalMoves(*board);
		for (auto move : moves)
		{
			if(piece)
			attackedWhite[move.first.poz.first][move.first.poz.second] = true;
		}
	}
}