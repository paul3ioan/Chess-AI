#include "Pawn.h"
#include <iostream>
std::vector<std::pair< Position, Position> >Pawn::getLegalMoves(const Board& board)
{
	std::vector<std::pair<Position, Position>> possibleMoves;
	std::pair<uint8_t, uint8_t> poz = this->poz.poz;
	std::cout << int(poz.first) << " " << int(poz.second) << '\n';
	std::pair<uint8_t, uint8_t> ans = { poz.first - 48, poz.second - 48 };
		
	//check for white color
	if (this->color == Color::black)
	{
		// check one square up move
		
		//cout <<
		if(board.board[ans.first + 1][ans.second]==PieceCode::empty)
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first + 1, poz.second)) });
		// check two square up move
		if (board.board[ans.first + 1][ans.second] == PieceCode::empty and poz.first == '1'
			and board.board[ans.first + 2][ans.second] == PieceCode::empty)
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first + 2, poz.second)) });
		//check capture right
		
		if (ans.second + 1 < 8 and checkSameColor(board, ans.first + 1, ans.second + 1, Color::black) and
			board.board[ans.first + 1][ans.second + 1] != PieceCode::empty)
		{
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first + 1, poz.second + 1)) });
		}
		//check capture left
		if (ans.second -1 >0 and checkSameColor(board, ans.first + 1, ans.second - 1, Color::black) and
			board.board[ans.first + 1][ans.second - 1] != PieceCode::empty)
		{
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first - 1, poz.second - 1)) });
		}
		// check enpasant
		//if(generalMoves[size(generalMoves - 1)])
	}

	if (this->color == Color::white)
	{
		// check one square up move
		
		//std:: 
		if (board.board[ans.first -1 ][ans.second] == PieceCode::empty)
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first - 1, poz.second)) });
		// check two square up move
		
		if (board.board[ans.first - 1][ans.second] == PieceCode::empty and poz.first == '6'
			and board.board[ans.first - 2][ans.second] == PieceCode::empty)
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first - 2, poz.second)) });
		//check capture right
		if (ans.second + 1 < 8 and checkSameColor(board, ans.first - 1, ans.second + 1, Color::white) and
			board.board[ans.first - 1][ans.second + 1] != PieceCode::empty)
		{
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first - 1, poz.second + 1)) });
		}
		//check capture left
		if (ans.second - 1 > 0 and checkSameColor(board, ans.first - 1, ans.second - 1, Color::white) and
			board.board[ans.first - 1][ans.second - 1] != PieceCode::empty)
		{
			possibleMoves.push_back({ Position(poz), Position(std::make_pair(poz.first - 1, poz.second - 1)) });
		}
		// check enpasant
		//if(generalMoves[size(generalMoves - 1)])
	}
	return possibleMoves;
}