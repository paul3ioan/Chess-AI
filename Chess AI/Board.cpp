#include "Board.h"
#include "Piece.h"
void Board::makeMove(std::pair<Position, Position> move)
{
	// make move on board
	auto from = move.first.poz;
	auto to = move.second.poz;
	board[to.first][to.second] = board[from.first][from.second];
	board[from.first][from.second] = PieceCode::empty;
	// make move in moveList
	// TODO: de mutat intr-o functie care converteste o mutare la string + poate facut clasa separata Move
	std::string moveCode;
	from.first = from.first + 'a' - '0';
	to.first = from.first + 'a' - '0';
	moveCode += from.first;
	moveCode += from.second;
	moveCode += to.first;
	moveCode += to.first;
	moveList += moveCode;
}
void Board::makeAttackBoard()
{
	
	for (int i = 0;i < 8;i++)
		for (int j = 0; j < 8;j++)
			attackedBlack[i][j] = 0;
	//reset attacked board for white
	for (int i = 0;i < 8;i++)
		for (int j = 0; j < 8;j++)
			attackedWhite[i][j] = 0;
	//reset attacked board for black
	
	for (auto piece : pieceList)
	{
		auto moves = piece->getLegalMoves(*this);
		
		for (auto move : moves)
		{
			if (piece->color == Color::black)
				attackedWhite[move.second.poz.first - '0'][move.second.poz.second - '0'] = 1;
			else
				attackedBlack[move.second.poz.first-'0'][move.second.poz.second-'0'] = 1;
			
		}
	}
}