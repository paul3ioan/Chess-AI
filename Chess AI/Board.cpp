#include "Board.h"
#include "Piece.h"
void Board::makeMove(Move move)
{
	// make move on board
	move.doMove(*this);
	auto from = move.from.poz;
	auto to = move.to.poz;
	// make move in moveList
	// TODO: de mutat intr-o functie care converteste o mutare la string + poate facut clasa separata Move
	//make the notation of the move
	std::string moveCode;
	from.first = from.first + 'a' - '0';
	to.first = from.first + 'a' - '0';
	moveCode += from.first;
	moveCode += from.second;
	moveCode += to.first;
	moveCode += to.first;
	moveCode += ' ' ;
	moveNotationList += moveCode;
	/// problem moveCode for promotion
	//put move in moveList
	//moveList.emplace_back(Position({ '1','2' }), Position({ '2','3' }), MoveType::basic); crapa
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

	//std::cout << board.pieceList.size() << '\n';
	for (auto piece : pieceList)
	{
		auto moves = piece->getLegalMoves(*this);
		
		for (auto move : moves)
		{
			if (piece->color == Color::black)
				attackedWhite[move.to.poz.first - '0'][move.to.poz.second - '0'] = 1;
			else
			{
				attackedBlack[move.to.poz.first - '0'][move.to.poz.second - '0'] = 1;
				//std::cout << move.from.poz.first << " " << move.from.poz.second << " " << move.to.poz.first << " " << move.to.poz.second << '\n';
			}
			
		}
	}
}