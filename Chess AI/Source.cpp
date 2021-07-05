#include <iostream>
#include<vector>
#include "Piece.h"

#include "Board.h"
#include "GeneralServices.h"
using namespace std;
int test(Board& board, int);
const int maxDepth = 2;
int main()
{
	
	Board board;

	GeneralServices::loadPosition(board);
	vector<Move> moves;
	cout <<test(board, 0);
	//for (int i = 0; i <= 7; i++, cout << '\n')
	//	for (int j = 0; j <= 7; j++)
		//	if (board.board[i][j].first != PieceCode::empty)
		//		cout << "1 ";
		//	else
			//	cout << "0 ";
	
	//for (auto piece : board.pieceList)
//	{
	//	auto piece_moves = piece->getLegalMoves(board);
	//	if (piece->getPieceCode(piece->color) == PieceCode::whitePawn)
	//	{
	//		cout << piece->poz.poz.first << " " << piece->poz.poz.second << ":  ";
	//	}

		
	//	cout <<(piece->color == Color::white ? "white " : "black ")<< piece_moves.size() << '\n';
	
}
int test(Board& board, int depth)
{
	vector<Move> moves;
	int ans = 0;
	if (depth % 2 == 0)
		moves = board.getAllMoves(Color::white);
	
	else
		moves = board.getAllMoves(Color::black);
	for (auto move : moves)
	{
		
		board.makeMove(move);
		if (depth >= maxDepth)
		{
			ans++;
			board.undoMove(&move);
			continue;
		}
		ans += test(board, depth + 1);
		board.undoMove(&move);
	}
	return ans;
}