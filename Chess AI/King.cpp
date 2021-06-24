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
	if (this->color == Color::white and board.whiteCastleLeft == true)
	{
		if (board.attackedWhite[7][4] or board.attackedWhite[7][3] or board.attackedWhite[7][2])
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(7 + '0', 2 + '0')) });
	}
	if (this->color == Color::white and board.whiteCastleRight == true)
	{
		if (board.attackedWhite[7][4] or board.attackedWhite[7][5] or board.attackedWhite[7][6])
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(7 + '0', 6 + '0')) });
	}
	if (this->color == Color::black and board.blackCastleLeft == true)
	{
		if (board.attackedBlack[0][4] or board.attackedBlack[0][3] or board.attackedBlack[0][2])
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(0 + '0', 2 + '0')) });
	}
	if (this->color == Color::black and board.blackCastleRight == true)
	{
		if (board.attackedBlack[0][4] or board.attackedBlack[0][5] or board.attackedBlack[0][6])
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(0 + '0', 6 + '0')) });
	}
	return possibleMoves;

}