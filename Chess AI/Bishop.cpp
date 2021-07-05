#include "Bishop.h"

PieceCode Bishop::getPieceCode(Color color)
{
	if (color == Color::white)
		return PieceCode::whiteBishop;
	return PieceCode::blackBishop;
}

std::vector<Move>Bishop::getLegalMoves(const Board& board)
{
	//std::cout << "BISHOP\n";
	std::vector<Move> possibleMoves;
	int dx[] = { -1, -1, 1, 1 };
	int dy[] = { -1, 1, -1, 1 };
		for (int j = 0;j < 4;j++)
		{
			int i = 1;
			while (true)
			{
				int line = poz.poz.first + dx[j] * i ;
				int col = poz.poz.second + dy[j] * i ;
				if (line < 0 or col < 0 or line > 7 or col > 7)
					break;
				if (checkDifferentColor(board, line, col, this->color))
				{
					possibleMoves.emplace_back(Position(poz), Position({line ,col }),MoveType::basic, this);
					if (board.board[line][col].first != PieceCode::empty)
						break;
				}
				else
					break;
				i++;
			}
		}
		
	return possibleMoves;
}