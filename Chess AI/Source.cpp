#include <iostream>
#include "Piece.h"
#include "King.h"
int main()
{
	
	std::pair <uint8_t, uint8_t > poz = { 'e', '1' };
	Piece* king = new King(Color::white, Position({ 5,1 }));
	
	Board board;
	for (int i = 0;i <= 7;i++)
		for (int j = 0;j <= 7;j++)
			board.board[i][j] = PieceCode::empty;
	board.board[5][1] = PieceCode:: whiteKing;
	//Board de = new Board(board);
	std::vector<std::pair<Position, Position>> ans = king->getLegalMoves(board);
	for (auto i : ans)
	{
		std::cout << i.first.poz.first <<" "<< i.first.poz.second <<'\n' <<i.second.poz.first<<" "
			<<i.second.poz.second;
	}
}