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
	std::string moveCode;
	from.first = from.first + 'a' - '0';
	to.first = from.first + 'a' - '0';
	moveCode += from.first;
	moveCode += from.second;
	moveCode += to.first;
	moveCode += to.first;
	moveList += moveCode;
}
void Board::makeAttackBlack( Board& board)
{
	
	for (int i = 0;i < 8;i++)
		for (int j = 0; j < 8;j++)
			attackedWhite[i][j] = 0;
	//reset attacked board for white
	
	std::cout << board.pieceList.size() << '\n';
	for (auto piece : pieceList)
	{
		
		//if (piece->color == Color::white)
			//continue;
		auto moves = piece->getLegalMoves(board);
		//std::cout <<'\n' moves.size() << '\n';
		for (auto move : moves)
		{
			//std::cout << contor++<<" ";
			
			attackedWhite[move.second.poz.first-'0'][move.second.poz.second-'0'] = 1;
			
		}
	}
}