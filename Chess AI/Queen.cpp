#include "Queen.h"

PieceCode Queen::getPieceCode(Color color)
{
	if (color == Color::white)
		return PieceCode::whiteQueen;
	return PieceCode::blackQueen;
}

std::vector<std::pair< Position, Position> >Queen::getLegalMoves(const Board& board)
{
	//std::cout << "QUEEN\n";
	std::vector<std::pair<Position, Position>> possibleMoves;
	int dx[] = { -1, -1, 1, 1, 0 , 0, -1, 1 };
	int dy[] = { -1, 1, -1, 1, 1 , -1, 0 ,0 };
	for (int j = 0;j < 8;j++)
	{
		int i = 1;
		while (true)
		{
			int line = poz.poz.first + dx[j] * i - 48;
			int col = poz.poz.second + dy[j] * i - 48;
			if (line < 0 or col < 0 or line > 7 or col > 7)
				break;
			if (checkDifferentColor(board, line, col, this->color))
			{
				possibleMoves.push_back({ Position(poz), Position({line + '0',col + '0'}) });
				if (board.board[line][col] != PieceCode::empty)
					break;
			}
			else
				break;
			i++;
		}
	}

	return possibleMoves;
}