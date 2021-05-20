#include "King.h"

std::vector<std::pair< Position, Position> >King::getLegalMoves(const Board& board)
{
	std::vector<std::pair<Position, Position>> possibleMoves;
	int dx[] = { -1,-1,-1, 0 ,0, 1, 1, 1 };
	int dy[] = { -1, 0 , 1, -1, 1, 0 ,-1, 1 };
	for (int i = 0;i < 8; i++)
	{

		int line = poz.poz.first + dx[i];
		int col = poz.poz.second + dy[i];
		if (line < 0 or col < 0 or line >7 or col > 7)
			continue;
		if (board.board[line][col] == PieceCode::empty)
		{
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(line, col)) });
		}
		if (color == Color::white)
		{
			if (board.board[line][col] == PieceCode::whiteBishop or
				board.board[line][col] == PieceCode::whiteKnight or
				board.board[line][col] == PieceCode::whitePawn or
				board.board[line][col] == PieceCode::whiteQueen or
				board.board[line][col] == PieceCode::whiteRook)
				continue;
		}
	}
	return possibleMoves;

}