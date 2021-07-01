#include "Board.h"
#include "Piece.h"
#include "GeneralServices.h"
Board::Board()
{
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
		{
			this->board[i][j].first = PieceCode::empty;
			this->board[i][j].second = nullptr;
		}
}
Board::Board(const Board& board) {
	this->whiteCastleLeft = board.whiteCastleLeft;
	this->whiteCastleRight = board.whiteCastleRight;
	this->blackCastleLeft = board.blackCastleLeft;
	this->blackCastleRight = board.blackCastleRight;
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
		{
			
			this->board[i][j].first = board.board[i][j].first;
			if (this->board[i][j].first == PieceCode::empty)
			{
				this->board[i][j].second = nullptr;
				continue;
			}
			switch (board.board[i][j].second->getPieceCode(board.board[i][j].second->color))
			{
			case PieceCode::whiteKing:
			case PieceCode::blackKing:
				this->board[i][j].second = new King(board.board[i][j].second->color, board.board[i][j].second->poz);
				break;
			case PieceCode::whiteQueen:
			case PieceCode::blackQueen:
				this->board[i][j].second = new Queen(board.board[i][j].second->color, board.board[i][j].second->poz);
				break;
			case PieceCode::whiteBishop:
			case PieceCode::blackBishop:
				this->board[i][j].second = new Bishop(board.board[i][j].second->color, board.board[i][j].second->poz);
				break;
			case PieceCode::whiteKnight:
			case PieceCode::blackKnight:
				this->board[i][j].second = new Knight(board.board[i][j].second->color, board.board[i][j].second->poz);
				break;
			case PieceCode::whiteRook:
			case PieceCode::blackRook:
				this->board[i][j].second = new Rook(board.board[i][j].second->color, board.board[i][j].second->poz);
				break;
			case PieceCode::whitePawn:
			case PieceCode::blackPawn:
				this->board[i][j].second = new Pawn(board.board[i][j].second->color, board.board[i][j].second->poz);
				break;
			
			case PieceCode::empty:
				this->board[i][j].second = nullptr;
				break;
			}
			if (this->board[i][j].second != nullptr)
				this->pieceList.push_back(this->board[i][j].second);
		}

}
Board::~Board()
{
	for (auto* piece : this->pieceList)
		delete piece;
}
bool Board::makeMove(Move move)
{
	Board copyBoard(*this);
	copyBoard.doMove(&move);
	// make move on board
	if (copyBoard.isValid(&move))
	{
		this->doMove(&move);
		this->makeAttackBoard();
	}
	else
		return false;
	auto from = move.from.poz;
	auto to = move.to.poz;
	// make move in moveList
	
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
	return true;
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

	//std::cout << this->pieceList.size() << '\n';
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
void Board::doMove(Move* move)
{
	int tox = move->to.poz.first - '0';
	int toy = move->to.poz.second - '0';
	int fromx = move->from.poz.first - '0';
	int fromy = move->from.poz.second - '0';
	Color variabila = move->piece->color;
	Piece* piece = move->piece;
	if (move->moveType == MoveType::basic or move->moveType == MoveType::doubleUp)
		basicMove( move, variabila);
	if (move->moveType == MoveType::king)
	{
		if (variabila == Color::white)
		{
			this->whiteCastleLeft = this->whiteCastleRight = 0;
			basicMove( move, variabila);
		}
		else
		{
			this->blackCastleLeft = this->blackCastleRight = 0;
			basicMove(move, variabila);
		}
	}
	if (move->moveType == MoveType::castle)
	{

		if (variabila == Color::white)
			this->whiteCastleLeft = this->whiteCastleRight = 0;
		else
			this->blackCastleLeft = this->blackCastleRight = 0;
		//move the king first
		basicMove( move, variabila);
		//move the rook
		int whichLine = variabila == Color::white ? 0 : 7;
		if (fromy == 6)
		{

			Piece* movedRook = this->board[whichLine][7].second;
			this->board[whichLine][5] = { movedRook->getPieceCode(variabila),movedRook };
			this->board[whichLine][7] = { PieceCode::empty, nullptr };
		}
		if (fromy == 2)
		{

			Piece* movedRook = this->board[whichLine][0].second;
			this->board[whichLine][3] = { movedRook->getPieceCode(variabila),movedRook };
			this->board[whichLine][0] = { PieceCode::empty, nullptr };
		}
	}
	if (move->moveType == MoveType::rook)
	{
		int whichLine = variabila == Color::white ? 0 : 7;
		if (fromx == fromy and fromy == whichLine)
		{
			if (whichLine == 0)
			{
				fromy == 0 ? this->whiteCastleLeft = 0 : this->whiteCastleRight = 0;
			}
			else
				fromy == 0 ? this->blackCastleLeft = 0 : this->blackCastleRight = 0;
		}
		basicMove( move, variabila);
	}
	if (move->moveType == MoveType::promote)
	{
		remove(this->pieceList.begin(), this->pieceList.end(), move->piece);
		delete move->piece;
		// for now the new piece is a queen
			//Piece* newPiece = new Queen()
			//this->pieceList.push_back(newPiece);
			//this->board[tox][toy] = {newPiece->getPieceCode(variabila), newPiece};
	}
	if (move->moveType == MoveType::enpasant)
	{
		Piece* capturedPiece = this->board[fromx][toy].second;
		remove(this->pieceList.begin(), this->pieceList.end(), capturedPiece);
		delete capturedPiece;
		this->board[fromx][toy] = { PieceCode::empty, nullptr };
	}
}
void Board::basicMove( Move* move, Color color)
{
	int tox = move->to.poz.first - '0';
	int toy = move->to.poz.second - '0';
	int fromx = move->from.poz.first - '0';
	int fromy = move->from.poz.second - '0';
	Piece* piece = move->piece;
	// basic move implementation
	if (this->board[tox][toy].first == PieceCode::empty)
	{
		//hardcode Color::white 
		Color variabila = move->piece->color;
		this->board[tox][toy] = { piece->getPieceCode(variabila),piece };
		this->board[fromx][fromy] = { PieceCode::empty, nullptr };
	}
	else
	{
		Piece* capturedPiece = this->board[tox][toy].second;
		remove(this->pieceList.begin(), this->pieceList.end(), capturedPiece);
		delete capturedPiece;
		this->board[tox][toy] = { piece->getPieceCode(move->piece->color),piece };
		this->board[fromx][fromy] = { PieceCode::empty, nullptr };
	}
}
bool Board::isValid(Move* move)
{
	Color color = move->piece->color;
	this->makeAttackBoard();
	if (color == Color::white)
	{
		for (Piece* piece : this->pieceList)
		{
			if (piece->getPieceCode(piece->color) == PieceCode::whiteKing)
			{
				if (this->attackedWhite[piece->poz.poz.first-'0'][piece->poz.poz.second-'0'])
					return false;
				return true;
			}
		}
	}
	else
	{
		for (Piece* piece : this->pieceList)
		{
			if (piece->getPieceCode(piece->color) == PieceCode::blackKing)
			{
				if (this->attackedBlack[piece->poz.poz.first-'0'][piece->poz.poz.second-'0'])
					return false;
				return true;
			}
		}
	}
}
std::vector<Move> Board::getAllMoves(Color color)
{
	std::vector<Move> allMoves;
	for (Piece* piece : this->pieceList)
	{
		if (piece->color != color)
			continue;
		auto moves = piece->getLegalMoves(*this);
		for (auto move : moves)
			allMoves.push_back(move);
	}
	return allMoves;
}
bool Board::testMove(Move move)
{
	Board copyBoard(*this);
	copyBoard.doMove(&move);
	// make move on board
	if (copyBoard.isValid(&move))
	{
		return true;
	}
	else
		return false;
}