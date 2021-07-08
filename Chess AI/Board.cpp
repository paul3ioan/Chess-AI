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
	this->whiteCastleLeft =this->undoWhiteCastleLeft = board.whiteCastleLeft;
	this->whiteCastleRight =this->undoWhiteCastleRight = board.whiteCastleRight;
	this->blackCastleLeft =this->undoBlackCastleLeft=  board.blackCastleLeft;
	this->blackCastleRight =this ->undoBlackCastleRight = board.blackCastleRight;
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
	this->undoWhiteCastleLeft = this->whiteCastleLeft;
	this->undoWhiteCastleRight =this->whiteCastleRight;
	this->undoBlackCastleLeft = this->blackCastleLeft;
	this->undoBlackCastleRight =this->blackCastleRight;
	
	this->doMove(&move);
	// make move on board
	if (this->isValid(&move))
		;
	else
	{
		this->undoMove(&move);
		this->makeAttackBoard();
		return false;
	}
	auto from = move.from.poz;
	auto to = move.to.poz;
	// make move in moveList
	
	//make the notation of the move
	std::string moveCode;
	char fromLine = '8' - from.first , fromCol = from.second + 'a';
	char toLine = '8' - to.first, toCol = to.second + 'a';
	moveCode += fromCol;
	moveCode += fromLine;
	moveCode += toCol;
	moveCode += toLine;
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

	for (auto piece : pieceList)
	{
		auto moves = piece->getLegalMoves(*this);
		
		for (auto move : moves)
		{
			if (piece->color == Color::black)
				attackedWhite[move.to.poz.first ][move.to.poz.second] = 1;
			else
			{
				attackedBlack[move.to.poz.first][move.to.poz.second] = 1;
				
			}
			
		}
	}
}
void Board::doMove(Move* move)
{
	this->capturedPiece = nullptr;
	int tox = move->to.poz.first ;
	int toy = move->to.poz.second ;
	
	int fromx = move->from.poz.first;
	int fromy = move->from.poz.second;

	Piece* piece = move->piece;
	if (move->moveType == MoveType::basic or move->moveType == MoveType::doubleUp)
		basicMove( move);
	if (move->moveType == MoveType::king)
	{
		if ( move->piece->color == Color::white)
		{
			this->whiteCastleLeft = this->whiteCastleRight = 0;
			basicMove( move);
		}
		else
		{
			this->blackCastleLeft = this->blackCastleRight = 0;
			basicMove(move);
		}
	}
	if (move->moveType == MoveType::castle)
	{

		if ( move->piece->color == Color::white)
			this->whiteCastleLeft = this->whiteCastleRight = 0;
		else
			this->blackCastleLeft = this->blackCastleRight = 0;
		//move the king first
		basicMove( move);
		//move the rook
		int whichLine =  move->piece->color == Color::white ? 7 : 0;
		if (toy == 6)
		{
			Piece* movedRook = this->board[whichLine][7].second;
			this->board[whichLine][5] = { movedRook->getPieceCode( move->piece->color),movedRook };
			this->board[whichLine][7] = { PieceCode::empty, nullptr };
			movedRook->poz.poz = {whichLine, 5};
		}
		if (toy == 2)
		{

			Piece* movedRook = this->board[whichLine][0].second;
			this->board[whichLine][3] = { movedRook->getPieceCode( move->piece->color),movedRook };
			this->board[whichLine][0] = { PieceCode::empty, nullptr };
			movedRook->poz.poz = { whichLine, 3 };
		}
	}
	if (move->moveType == MoveType::rook)
	{
		int whichLine =  move->piece->color == Color::white ? 7 : 0;
		if (fromx == fromy and fromy == whichLine)
		{
			if (whichLine == 0)
			{
				fromy == 0 ? this->whiteCastleLeft = 0 : this->whiteCastleRight = 0;
			}
			else
				fromy == 0 ? this->blackCastleLeft = 0 : this->blackCastleRight = 0;
		}
		basicMove( move);
	}
	if (move->moveType == MoveType::promote)
	{
		this->capturedPiece = this->board[fromx][fromy].second;
		auto newEnd = remove(this->pieceList.begin(), this->pieceList.end(), this->capturedPiece);
		this->pieceList.erase(newEnd, this->pieceList.end());
		this->board[fromx][fromy] = { PieceCode::empty, nullptr };
		//for now the new piece is a queen
		Piece* newPiece = new Queen(this->capturedPiece->color, move->to);
		this->pieceList.push_back(newPiece);
		this->board[tox][toy] = {newPiece->getPieceCode( move->piece->color), newPiece};
	}
	if (move->moveType == MoveType::enpasant)
	{
		this->capturedPiece = this->board[fromx][toy].second;
		auto newEnd = remove(this->pieceList.begin(), this->pieceList.end(), this->capturedPiece);
		this->pieceList.erase(newEnd, this->pieceList.end());
		this->board[fromx][toy] = { PieceCode::empty, nullptr };
		basicMove(move);
	}
}
void Board::basicMove( Move* move)
{
	int tox = move->to.poz.first;
	int toy = move->to.poz.second ;
	int fromx = move->from.poz.first ;
	int fromy = move->from.poz.second ;
	Piece* piece = move->piece;
	// basic move implementation
	if (this->board[tox][toy].first == PieceCode::empty)
	{
		this->board[tox][toy] = { piece->getPieceCode( move->piece->color),piece };
		this->board[fromx][fromy] = { PieceCode::empty, nullptr };
		move->piece->poz =  move->to ;
	}
	else
	{
		this->capturedPiece = this->board[tox][toy].second;
		auto newEnd = remove(this->pieceList.begin(), this->pieceList.end(), capturedPiece);
		this->pieceList.erase(newEnd, this->pieceList.end());
		this->board[tox][toy] = { piece->getPieceCode(move->piece->color),piece };
		this->board[fromx][fromy] = { PieceCode::empty, nullptr };
		move->piece->poz = move->to;
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
				if (this->attackedWhite[piece->poz.poz.first][piece->poz.poz.second])
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
				if (this->attackedBlack[piece->poz.poz.first][piece->poz.poz.second])
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
void Board::undoMove(Move* move)
{
	this->whiteCastleLeft = this->undoWhiteCastleLeft;
	this->whiteCastleRight = this->undoWhiteCastleRight;
	this->blackCastleLeft = this->undoBlackCastleLeft;
	this->blackCastleRight = this->undoBlackCastleRight;
	if (move->moveType == MoveType::basic or move->moveType == MoveType::doubleUp
		or move->moveType == MoveType::king or move->moveType== MoveType:: rook)
		basicUndoMove(move);
	if (move->moveType == MoveType::castle)
	{
		this->board[move->from.poz.first][move->from.poz.second] = { move->piece->getPieceCode(move->piece->color), move->piece };
		this->board[move->to.poz.first][move->to.poz.second] = { PieceCode::empty, nullptr };
		if (move->to.poz.second == 6)
		{
			Piece* movedRook =  this->board[move->from.poz.first][5].second;
			this->board[move->from.poz.first][7] = { movedRook->getPieceCode(movedRook->color), movedRook };
			this->board[move->from.poz.first][5] = { PieceCode::empty, nullptr };
			movedRook->poz.poz = { move->from.poz.first, 7 };
		}
		if (move->to.poz.second == 2)
		{
			Piece* movedRook = this->board[move->from.poz.first][3].second;
			this->board[move->from.poz.first][0] = { movedRook->getPieceCode(movedRook->color), movedRook };
			this->board[move->from.poz.first][3] = { PieceCode::empty, nullptr };
			movedRook->poz.poz = { move->from.poz.first, 0 };
		}
	}
	if (move->moveType == MoveType::enpasant)
	{
	
		basicUndoMove(move);
	}
	if (move->moveType == MoveType::promote)
	{
		Piece* promotedPiece = this->board[move->to.poz.first][move->to.poz.second].second;
		auto newEnd = remove(pieceList.begin(), pieceList.end(), promotedPiece);
		this->pieceList.erase(newEnd, this->pieceList.end());
		delete promotedPiece;
		Piece* newPiece = this->capturedPiece;
		this->capturedPiece = nullptr;
		this->board[move->from.poz.first][move->from.poz.second] = { newPiece->getPieceCode(newPiece->color), newPiece };
		this->pieceList.push_back(newPiece);
	}

}
void Board::basicUndoMove(Move* move)
{
	int tox = move->to.poz.first;
	int toy = move->to.poz.second;
	int fromx = move->from.poz.first;
	int fromy = move->from.poz.second;

		this->board[fromx][fromy] = { move->piece->getPieceCode(move->piece->color),move->piece };
	this->board[tox][toy] = { PieceCode::empty, nullptr };
	if (this->capturedPiece != nullptr)
	{
		int capturedX = this->capturedPiece->poz.poz.first;
		int capturedY = this->capturedPiece->poz.poz.second;
		this->board[capturedX][capturedY] = { this->capturedPiece->getPieceCode(this->capturedPiece->color), this->capturedPiece };
		this->pieceList.push_back(capturedPiece);
		this->capturedPiece = nullptr;
	}
	move->piece->poz = move->from;
}