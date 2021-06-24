#include "Rook.h"

PieceCode Rook::getPieceCode(Color color)
{
	if (color == Color::white)
		return PieceCode::whiteRook;
	return PieceCode::blackRook;
}

std::vector<Move >Rook::getLegalMoves(const Board& board)
{
	//std::cout << "ROOK\n";
	std::vector<Move> possibleMoves;
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };
	for (int j = 0;j < 4;j++)
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
				possibleMoves.emplace_back( Position(poz), Position({line + '0',col + '0'}),MoveType::rook,this);
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