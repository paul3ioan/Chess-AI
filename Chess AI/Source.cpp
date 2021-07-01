#include <iostream>
#include<vector>
#include "Piece.h"
//#include "King.h"
//#include "Pawn.h"
//#include "Bishop.h"
//#include "Rook.h"
//#include "Queen.h"
//#include "Knight.h"
#include "Board.h"
#include "GeneralServices.h"
using namespace std;
int test(Board& board, int);
const int maxDepth = 1;
int main()
{
	
	Board board;

	GeneralServices::loadPosition(board);
	//cout << board.pieceList.size() << '\n';
	//generalServices.savePosition(&board);
	//board.makeAttackBoard();
	cout <<test(board, 0);
	//for (int i = 0; i <= 7; i++, cout << '\n')
	//	for (int j = 0; j <= 7; j++)
		//	if (board.board[i][j].first != PieceCode::empty)
		//		cout << "1 ";
		//	else
			//	cout << "0 ";
	
}
int test(Board& board, int depth)
{
	vector<Move> moves;
	int ans = 0;
	if(depth % 2 == 0)
		moves = board.getAllMoves(Color::white);
	else
		moves = board.getAllMoves(Color::black);
	for (auto move : moves)
	{
		if (board.testMove(move))
		{

			if (depth >= maxDepth)
			{
				ans++;
				continue;
			}
			Board newBoard(board);
			newBoard.makeMove(move);
			ans += test(newBoard, depth + 1);
		}
	}
	return ans;
}