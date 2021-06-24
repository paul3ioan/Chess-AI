#include "GeneralServices.h"
#include <fstream>
#include "Piece.h"
#include "Pawn.h"

std::string pieceToString(Piece*, const Board&);

		}
		if (typee == 'r')
		{
			if (color == 'w')
			{
				Piece* rook = new Rook(Color::white, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::whiteRook;
				board->pieceList.push_back(rook);
			}
			else
			{
				Piece* pawn = new Rook(Color::black, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::blackRook;
				board->pieceList.push_back(pawn);
			}


		}
		if (typee == 'k')
		{
			if (color == 'w')
			{
				Piece* knight = new Knight(Color::white, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::whiteKnight;
				board->pieceList.push_back(knight);
			}
			else
			{
				Piece* knight = new Knight(Color::black, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::blackKnight;
				board->pieceList.push_back(knight);
			}


		}
		if (typee == 'b')
		{
			if (color == 'w')
			{
				Piece* bishop = new Bishop(Color::white, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::whiteBishop;
				board->pieceList.push_back(bishop);
			}
			else
			{
				Piece* bishop = new Bishop(Color::black, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::blackBishop;
				board->pieceList.push_back(bishop);
			}


		}
		if (typee == 'q')
		{
			if (color == 'w')
			{
				Piece* queen = new Queen(Color::white, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::whiteBishop;
				board->pieceList.push_back(queen);
			}
			else
			{
				Piece* queen = new Queen(Color::black, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::blackQueen;
				board->pieceList.push_back(queen);
			}


		}
		if (typee == 'K')
		{
			if (color == 'w')
			{
				Piece* king = new King(Color::white, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::whiteKing;
				board->pieceList.push_back(king);
			}
			else
			{
				Piece* king = new King(Color::black, Position({ pozx,pozy }));
				board->board[pozx - '0'][pozy - '0'] = PieceCode::blackKing;
				board->pieceList.push_back(king);
			}


		}
		i += 4;
	}

	// TODO: De testat ca e doar 0/1, altfel dam o eroare
	if (i != position.size())
	{
		if (position[i] == '1')
			board.whiteCastleLeft = true;
		else
			board.whiteCastleLeft = false;

		if (position[i + 1] == '1')
			board.whiteCastleRight = true;
		else
			board.whiteCastleRight = false;

		if (position[i + 2] == '1')
			board.blackCastleLeft = true;
		else
			board.blackCastleLeft = false;

		if (position[i + 3] == '1')
			board.blackCastleRight = true;
		else
			board.blackCastleRight = false;
	}
	//parcurgere de string	
	//board.pieceList.push_back(//create piece)
}

void GeneralServices::savePosition(const Board& board)
{
	std::ofstream fout("position.txt");
	fout << createPosition(board)<< '\n';
	//cout <<moveList;
	fout.close();
}

std::string GeneralServices::createPosition(const Board& board)
{
	std::string position;

	for (auto* piece : board.pieceList)
	{
		position += pieceToString(piece, board);
	}
	//std::cout <<'\n'<< position<<'\n';
	if (board.whiteCastleLeft)
		position += "1";
	else
		position += "0";

	if (board.whiteCastleRight)
		position += "1";
	else
		position += "0";

	if (board.blackCastleLeft)
		position += "1";
	else
		position += "0";

	if (board.blackCastleRight)
		position += "1";
	else
		position += "0";
	//std::cout << '\n' << position << '\n';
	return position;
}

std::string pieceToString(Piece* piece, const Board& board)
{
	//uint8_t leftCastle, rightCastle;
	uint8_t pozx = piece->poz.poz.first;
	uint8_t color, pieceType='0';
	uint8_t pozy = piece->poz.poz.second;
	std::string pieceString;
	if (piece->color == Color::white)
		color = 'w';
	else
		color = 'b';
	PieceCode pieceName = piece->getPieceCode(piece->color);
	if (pieceName == PieceCode::blackBishop or pieceName == PieceCode::whiteBishop)
		pieceType = 'b';
	if (pieceName == PieceCode::blackQueen or pieceName == PieceCode::whiteQueen)
		pieceType = 'q';
	if (pieceName == PieceCode::blackKing or pieceName == PieceCode::whiteKing)
		pieceType = 'K';
	if (pieceName == PieceCode::blackKnight or pieceName == PieceCode::whiteKnight)
		pieceType = 'k';
	if (pieceName == PieceCode::blackRook or pieceName == PieceCode::whiteRook)
		pieceType = 'r';
	if (pieceName == PieceCode::blackPawn or pieceName == PieceCode::whitePawn)
		pieceType = 'p';
	pieceString += pieceType;
	pieceString += color;
	pieceString += pozx;
	pieceString += pozy;

	return pieceString;
}
