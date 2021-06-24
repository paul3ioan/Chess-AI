#include "King.h"
#include <iostream>
std::vector<std::pair< Position, Position> >King::getLegalMoves(const Board& board)
{
//	std::cout << "King\n";
	//king merge in orice camp liber sau neocupat de o piesa de aceasi culoare
	std::vector<std::pair<Position, Position>> possibleMoves;
	int dx[] = { -1,-1,-1, 0 ,0, 1, 1, 1 };
	int dy[] = { -1, 0 , 1, -1, 1, 0 ,-1, 1 };

	for (int i = 0;i < 8; i++)
	{

		int line = poz.poz.first + dx[i]- 48;
		int col = poz.poz.second + dy[i]- 48;
		
		if (line < 0 or col < 0 or line >7 or col > 7)
			continue;
		
		if (this->checkSameColor(board, line, col, this->color))
		{
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(line + 48,col +48)) });
		}
	}

	return possibleMoves;

}