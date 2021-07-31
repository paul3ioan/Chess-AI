#include "GeneralServices.h"
#include <fstream>
#include "Piece.h"
#include "Pawn.h"

char pieceToString(PieceCode);

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
	 
	 std::ifstream fin("../Chess AI/position.txt");
	std::string position, moveList;
	fin >> position;
	int line = 0, col = 0;
	for (char c : position)
	{
		if (c <= '9' and c >= '0')
		{
			col += c - '0';
		}
		else
			if (c == '/')
				line++, col = 0;
			else
			{
				switch (c)
				{
					case 'r':
						createPiece<Rook>(line, col, 'b', board);
						break;
					case 'b':
						createPiece<Bishop>(line, col, 'b', board);
						break;
					case 'k':
						createPiece<King>(line, col, 'b', board);
						break;
					case 'q':
						createPiece<Queen>(line, col, 'b', board);
						break;
					case 'p':
						createPiece<Pawn>(line, col, 'b', board);
						break;
					case 'n':
						createPiece<Knight>(line, col, 'b', board);
						break;
					case 'R':
						createPiece<Rook>(line, col, 'w', board);
						break;
					case 'N':
						createPiece<Knight>(line, col, 'w', board);
						break;
					case 'B':
						createPiece<Bishop>(line, col, 'w', board);
						break;
					case 'Q':
						createPiece<Queen>(line, col, 'w', board);
						break;
					case 'K':
						createPiece<King>(line, col, 'w', board);
						break;
					case 'P':
						createPiece<Pawn>(line, col, 'w', board);
						break;
				}
				col++;
			}
	}
	/// <summary>
	/// fain   de facut cin  
	/// </summary>
	/// <param name="board"></param>
	/// <param name="position"></param>
	fin >> position;
	if (position == "w")
		board.whoMove = Color::white;
	else
		board.whoMove = Color::black;
	fin >> position;
	if (position == "-")
		;
	else
	{
		for (char x : position)
		{
			if (x == 'q') board.blackCastleLeft = true;
			if (x == 'k') board.blackCastleRight = true;
			if (x == 'Q') board.whiteCastleLeft = true;
			if (x == 'K') board.whiteCastleRight = true;
		}
	}
	fin >> position;
	if (position != "-")
	{
		int xCoord = position[0] - 'a';
		int yCoord = position[1] - '1';
		Color whichColor = (yCoord == 1 ? Color::white : Color::black);
		Move enpasant(Position ({xCoord, whichColor == Color::white ? 1 : 6 }),
			Position({xCoord, whichColor == Color::white ? 3 : 4
	}), MoveType::doubleUp, board.board[xCoord][yCoord].second);
		board.moveList.push_back(enpasant);
	}
	char numberOfMoves;
	
	while (fin >>numberOfMoves)
	{
		board.numberOfMovesWhite = int(numberOfMoves - '0');
		fin >> numberOfMoves;
		board.numberOfMovesBlack = int(numberOfMoves - '0');
		break;
	}
	fin.close();
}

void GeneralServices::savePosition(const Board& board)
{
	//std::ofstream fout("position.txt");
	std::cout<< createPosition(board)<< '\n';
	//fout.close();
}

std::string GeneralServices::createPosition(const Board& board)
{
	
	std::string output = "";
	int empty = 0;
		for (int i = 0 ; i < 8 ; i ++, (i != 8 ? output += "/" : output += "") )
		{
			empty = 0;
			for (int j = 0;j < 8;j++ )
			{
				if (board.board[i][j].first == PieceCode::empty)
					empty++;
				else
				{
					if (empty)
					{
						char number = empty +'0';
						output+= number;
						empty = 0;
						
					}
					output += pieceToString(board.board[i][j].first);
				}
			}
			if (empty)
			{
				char number = empty + '0';
				output += number;
			}

		}
		output += " ";
		if (board.whoMove == Color::white)
			output += 'w';
		else
			output += 'b';
		output += " ";
		

		// check for castle
		std::string castles = "";
		if (board.blackCastleLeft) castles += 'q';
		if (board.blackCastleRight) castles += 'k';
		if (board.whiteCastleLeft) castles += 'Q';
		if (board.whiteCastleRight) castles += 'K';
		if (castles == "")
			output += "- ";
		else
			output += castles, output +=" ";
		if (board.moveList.size() != 0)
		{
			Move lastMove = board.moveList[board.moveList.size() - 1];
			if (lastMove.moveType == MoveType::doubleUp)
			{
				std::string move = "";
				char col = lastMove.from.poz.first + 'a';
				char line = lastMove.from.poz.second == 1 ? '3' : '5';
				move = line + col;
				output += move;
				output += " ";
			}
			else
				output += "- ";
		}
		else
			output += "- ";
		output += board.numberOfMovesWhite + '0';
		output += " ";
		output += board.numberOfMovesBlack + '0';
		return output;
}

char pieceToString(PieceCode piece)
{
	switch (piece)
	{
	case PieceCode::whiteKing:
		return 'K';
	case PieceCode::whiteQueen:
		return 'Q';
	case PieceCode::whiteBishop:
		return 'B';
	case PieceCode::whiteKnight:
		return 'N';
	case PieceCode::whiteRook:
		return 'R';
	case PieceCode::whitePawn:
		return 'P';
	case PieceCode::blackKing:
		return 'k';
	case PieceCode::blackQueen:
		return 'q';
	case PieceCode::blackBishop:
		return 'b';
	case PieceCode::blackKnight:
		return 'n';
	case PieceCode::blackRook:
		return 'r';
	case PieceCode::blackPawn:
		return 'p';
	case PieceCode::empty:
		throw NAN;
	}
}
