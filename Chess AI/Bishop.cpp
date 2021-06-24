#include "Bishop.h"

std::vector<std::pair< Position, Position> >Bishop::getLegalMoves(const Board& board)
{
	//std::cout << "BISHOP\n";
	std::vector<std::pair<Position, Position>> possibleMoves;
	int dx[] = { -1, -1, 1, 1 };
	int dy[] = { -1, 1, -1, 1 };
		for (int j = 0;j < 4;j++)
		{
			int i = 1;
			while (true)
			{
				int line = poz.poz.first + dx[j] * i - 48;
				int col = poz.poz.second + dy[j] * i - 48;
				if (line < 0 or col < 0 or line > 7 or col > 7)
					break;
				if (checkSameColor(board, line, col, this->color))
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