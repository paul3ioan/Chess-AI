#include "GeneralServices.h"
#include <fstream>
#include "Piece.h"
#include "Pawn.h"

std::string pieceToString(Piece*, const Board&);

template<class T>
void createPiece(int pozx, int pozy, uint8_t color, Board& board)
{
	if (color == 'w')
	{
		Piece* piece = new T(Color::white, Position({ pozx,pozy }));
		board.board[pozx ][pozy ] = { piece->getPieceCode(Color::white), piece };
		board.pieceList.push_back(piece);
	}
	else
	{
		Piece* piece = new T(Color::black, Position({ pozx,pozy }));
		board.board[pozx ][pozy ] = { piece->getPieceCode(Color::black), piece };
		
		board.pieceList.push_back(piece);
	}
}

 void GeneralServices::loadPosition(Board& board)
{
	std ::ifstream cin("position.txt");
	std::string position, moveList;
	cin >> position;
	cin.close();
	int i = 0;
	while (i < position.size()) 
	{
		if (position[i] >= '0' and position[i] <= '9')
			break;
		
		uint8_t pieceType = position[i];
		uint8_t color = position[i + 1];
		int pozx = position[i + 2] -'0';
		int pozy = position[i + 3] - '0';
		
		switch (pieceType)
		{
		case 'p':
			createPiece<Pawn>(pozx, pozy, color, board);
			break;
		case 'r':
			createPiece<Rook>(pozx, pozy, color, board);
			break;
		case 'k':
			createPiece<Knight>(pozx, pozy, color, board);
			break;
		case 'b':
			createPiece<Bishop>(pozx, pozy, color, board);
			break;
		case 'q':
			createPiece<Queen>(pozx, pozy, color, board);
			break;
		case 'K':
			createPiece<King>(pozx, pozy, color, board);
			break;
		default:
			throw "Invalid piece code";
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
		board.undoWhiteCastleLeft = board.whiteCastleLeft ;
		board.undoWhiteCastleRight = board.whiteCastleRight ;
		board.undoBlackCastleLeft = board.blackCastleLeft ;
		board.undoBlackCastleRight = board.blackCastleRight;
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
	int pozx = piece->poz.poz.first + '0';
	uint8_t color, pieceType='0';
	int pozy = piece->poz.poz.second+ '0';
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
