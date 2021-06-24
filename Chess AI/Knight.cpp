#include "Knight.h"

PieceCode Knight::getPieceCode(Color color)
{
	if (color == Color::white)
		return PieceCode::whiteKnight;
	return PieceCode::blackKnight;
}

std::vector<Move >Knight::getLegalMoves(const Board& board)
{
	//std::cout << "Knight\n";
	std::vector<Move> possibleMoves;
	int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int dy[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	for (int i = 0;i <= 7;i++)
	{
		int line = poz.poz.first + dx[i]-'0';
		int col = poz.poz.second + dy[i] -'0';
		if (line < 0 or col < 0 or col > 7 or line > 7)
			continue;
		if(board.board[line][col].first == PieceCode::empty or checkDifferentColor(board, line,col, Color::white))
			possibleMoves.emplace_back(Position(poz), Position({line + '0',col + '0'}), MoveType::basic, this);
	}

	return possibleMoves;
}