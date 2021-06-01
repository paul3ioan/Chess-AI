#include "Knight.h"

std::vector<std::pair< Position, Position> >Knight::getLegalMoves(const Board& board)
{
	std::vector<std::pair<Position, Position>> possibleMoves;
	int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int dy[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	for (int i = 0;i <= 7;i++)
	{
		int line = poz.poz.first + dx[i]-'0';
		int col = poz.poz.second + dy[i] -'0';
		if (line < 0 or col < 0 or col > 7 or line > 7)
			continue;
		if(checkSameColor(board, line,col, Color::white))
			possibleMoves.push_back({ Position(poz), Position({line + '0',col + '0'}) });
	}

	return possibleMoves;
}