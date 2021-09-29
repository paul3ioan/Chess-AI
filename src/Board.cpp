#include "Board.h"
#include "Piece.h"
#include "GeneralServices.h"

Board::Board()
{
    for (int i = 0; i <= 7; i++)
        for (int j = 0; j <= 7; j++)
        {
            this->attackedBlack[i][j] = 0;
            this->attackedWhite[i][j] = 0;
            this->board[i][j].first = PieceCode::empty;
            this->board[i][j].second = nullptr;
        }
}

Board::Board(const Board &board)
{
    this->whiteCastleLeft = board.whiteCastleLeft;
    this->undoWhiteCastleLeft = board.undoWhiteCastleLeft;
    this->whiteCastleRight = board.whiteCastleRight;
    this->undoWhiteCastleRight = board.undoWhiteCastleRight;
    this->blackCastleLeft = board.blackCastleLeft;
    this->undoBlackCastleLeft = board.undoBlackCastleLeft;
    this->blackCastleRight = board.blackCastleRight;
    this->undoBlackCastleRight = board.undoBlackCastleRight;
    this->capturedPieces = board.capturedPieces;
    this->numberOfMovesBlack = board.numberOfMovesBlack;
    this->numberOfMovesWhite = board.numberOfMovesWhite;
    this->whoMove = board.whoMove;
    for (int i = 0; i <= 7; i++)
        for (int j = 0; j <= 7; j++)
        {
            this->attackedBlack[i][j] = board.attackedBlack[i][j];
            this->attackedWhite[i][j] = board.attackedWhite[i][j];
            this->board[i][j].first = board.board[i][j].first;
            if (this->board[i][j].first == PieceCode::empty)
            {
                this->board[i][j].second = nullptr;
                continue;
            }
            this->board[i][j].second = board.board[i][j].second;
            if (this->board[i][j].second != nullptr)
                this->pieceList.push_back(this->board[i][j].second);
        }
    for(auto move: board.moveList)
    {
        this->moveList.push_back(move);
    }
}

Board::~Board()
{
    //for (auto* piece : this->pieceList)
    //delete piece;
    /* while(!this->capturedPieces.empty())
     {
         delete capturedPieces.top();
         capturedPieces.pop();
     }*/
}

bool Board::makeMove(const Move &move)
{
    this->undoWhiteCastleLeft = this->whiteCastleLeft;
    this->undoWhiteCastleRight = this->whiteCastleRight;
    this->undoBlackCastleLeft = this->blackCastleLeft;
    this->undoBlackCastleRight = this->blackCastleRight;

    this->doMove(move);
    // make move on board
    if (this->isValid(move));
    else
    {
        this->undoMove(move);
        this->makeAttackBoard();
        return false;
    }
    auto from = move.from.poz;
    auto to = move.to.poz;
    // make move in moveList

    //make the notation of the move
    std::string moveCode;
    char fromLine = '8' - from.first, fromCol = from.second + 'a';
    char toLine = '8' - to.first, toCol = to.second + 'a';
    moveCode += fromCol;
    moveCode += fromLine;
    moveCode += toCol;
    moveCode += toLine;
    moveCode += ' ';
    moveNotationList += moveCode;
    return true;

    //put move in moveList
    //moveList.emplace_back(Position({ '1','2' }), Position({ '2','3' }), MoveType::basic); crapa
}

void Board::makeAttackBoard()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            this->attackedBlack[i][j] = 0;
    //reset attacked board for white
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            this->attackedWhite[i][j] = 0;

    for (const auto &piece: pieceList)
    {
        auto moves = piece->getLegalMoves(*this);

        for (const auto &move: moves)
        {
            //check for pawn : a pawn doesn't attack straight forward
            if (piece->getPieceCode(piece->color) == PieceCode::whitePawn
                || piece->getPieceCode(piece->color) == PieceCode::blackPawn)
            {
                if (abs(move.to.poz.second - move.from.poz.second) == 0)
                    continue;
            }
            if (piece->color == Color::black)
                this->attackedWhite[move.to.poz.first][move.to.poz.second] = 1;
            else
            {
                this->attackedBlack[move.to.poz.first][move.to.poz.second] = 1;
            }
        }
    }
}

void Board::doMove(const Move &move)
{
    //this->capturedPiece = nullptr;
    int tox = move.to.poz.first;
    int toy = move.to.poz.second;

    int fromx = move.from.poz.first;
    int fromy = move.from.poz.second;

    auto piece = move.piece;
    if (move.moveType == MoveType::basic || move.moveType == MoveType::doubleUp)
        basicMove(move);
    if (move.moveType == MoveType::king)
    {
        if (move.piece->color == Color::white)
        {
            this->whiteCastleLeft = this->whiteCastleRight = false;
            basicMove(move);
        } else
        {
            this->blackCastleLeft = this->blackCastleRight = false;
            basicMove(move);
        }
    }
    if (move.moveType == MoveType::castle)
    {

        if (move.piece->color == Color::white)
            this->whiteCastleLeft = this->whiteCastleRight = false;
        else
            this->blackCastleLeft = this->blackCastleRight = false;
        //move the king first
        basicMove(move);
        //move the rook
        int whichLine = move.piece->color == Color::white ? 7 : 0;
        if (toy == 6)
        {
            auto movedRook = this->board[whichLine][7].second;
            this->board[whichLine][5] = {movedRook->getPieceCode(move.piece->color), movedRook};
            this->board[whichLine][7] = {PieceCode::empty, nullptr};
            movedRook->poz.poz = {whichLine, 5};
        }
        if (toy == 2)
        {

            auto movedRook = this->board[whichLine][0].second;
            this->board[whichLine][3] = {movedRook->getPieceCode(move.piece->color), movedRook};
            this->board[whichLine][0] = {PieceCode::empty, nullptr};
            movedRook->poz.poz = {whichLine, 3};
        }
    }
    if (move.moveType == MoveType::rook)
    {
//        int whichLine = move.piece->color == Color::white ? 7 : 0;
        if(fromy == 0 and fromx == 0)
            this->blackCastleLeft = false;
        if(fromy == 0 and fromx == 7)
            this->whiteCastleLeft = false;
        if(fromy == 7 and fromx == 0)
            this->blackCastleRight = false;
        if(fromy == 7 and fromx == 7)
            this->whiteCastleRight = false;
        basicMove(move);
    }
    if (move.moveType == MoveType::promoteQueen or move.moveType == MoveType::promoteBishop
        or move.moveType == MoveType::promoteKnight or move.moveType == MoveType::promoteRook)
    {
        if(this->board[tox][toy].first !=PieceCode::empty)
        {
            this->capturedPieces.push(this->board[tox][toy].second);
            auto newEnd = std::remove(this->pieceList.begin(), this->pieceList.end(), this->capturedPieces.top());
            this->pieceList.erase(newEnd, this->pieceList.end());
            this->board[tox][toy] = {PieceCode::empty, nullptr};
        }
        this->capturedPieces.push(this->board[fromx][fromy].second);
        auto newEnd = std::remove(this->pieceList.begin(), this->pieceList.end(), this->capturedPieces.top());
        this->pieceList.erase(newEnd, this->pieceList.end());
        this->board[fromx][fromy] = {PieceCode::empty, nullptr};
        //now test if i captured a piece

         std::shared_ptr<Piece> newPiece;
        switch(move.moveType)
        {
            case MoveType::promoteKnight:
                newPiece = std::make_shared<Knight>(this->capturedPieces.top()->color, move.to);
                break;
            case MoveType::promoteQueen:
                newPiece = std::make_shared<Queen>(this->capturedPieces.top()->color, move.to);
                break;
            case MoveType::promoteRook:
                newPiece = std::make_shared<Rook>(this->capturedPieces.top()->color, move.to);
                break;
            case MoveType::promoteBishop:
                newPiece = std::make_shared<Bishop>(this->capturedPieces.top()->color, move.to);
                break;
        }
        newPiece->this_ptr = newPiece;
        this->pieceList.push_back(newPiece);
        this->board[tox][toy] = {newPiece->getPieceCode(move.piece->color), newPiece};
    }
    if (move.moveType == MoveType::enpasant)
    {
        this->capturedPieces.push(this->board[fromx][toy].second);
        auto newEnd = std::remove(this->pieceList.begin(), this->pieceList.end(), this->capturedPieces.top());
        this->pieceList.erase(newEnd, this->pieceList.end());
        this->board[fromx][toy] = {PieceCode::empty, nullptr};
        basicMove(move);
    }
}

void Board::basicMove(const Move &move)
{
    int tox = move.to.poz.first;
    int toy = move.to.poz.second;
    int fromx = move.from.poz.first;
    int fromy = move.from.poz.second;
    auto piece = move.piece;
    // basic move implementation
    if (this->board[tox][toy].first == PieceCode::empty)
    {
        this->capturedPieces.push(nullptr);
        this->board[tox][toy] = {piece->getPieceCode(move.piece->color), piece};
        this->board[fromx][fromy] = {PieceCode::empty, nullptr};
        move.piece->poz = move.to;
    } else
    {
        this->capturedPieces.push(this->board[tox][toy].second);
        auto newEnd = std::remove(this->pieceList.begin(), this->pieceList.end(), this->capturedPieces.top());
        this->pieceList.erase(newEnd, this->pieceList.end());
        this->board[tox][toy] = {piece->getPieceCode(move.piece->color), piece};
        this->board[fromx][fromy] = {PieceCode::empty, nullptr};
        move.piece->poz = move.to;
    }
}

bool Board::isValid(const Move &move)
{
    Color color = move.piece->color;
    this->makeAttackBoard();
    if (color == Color::white)
    {
        for (const auto &piece: this->pieceList)
        {
            if (piece->getPieceCode(piece->color) == PieceCode::whiteKing)
            {
                if (this->attackedWhite[piece->poz.poz.first][piece->poz.poz.second])
                    return false;
                return true;
            }
        }
    } else
    {
        for (const auto &piece: this->pieceList)
        {
            if (piece->getPieceCode(piece->color) == PieceCode::blackKing)
            {
                if (this->attackedBlack[piece->poz.poz.first][piece->poz.poz.second])
                    return false;
                return true;
            }
        }
    }
    return false;
}

std::vector<Move> Board::getAllMoves(Color color)
{
    std::vector<Move> allMoves;
    for (const auto &piece: this->pieceList)
    {
        if (piece->color != color)
            continue;
        auto moves = piece->getLegalMoves(*this);
        for (const auto &move: moves)
            allMoves.push_back(move);
    }
    return allMoves;
}

bool Board::testMove(const Move &move)
{
    Board copyBoard(*this);
    copyBoard.doMove(move);
    // make move on board
    if (copyBoard.isValid(move))
    {
        return true;
    } else
        return false;
}

void Board::undoMove(const Move &move)
{
    this->whiteCastleLeft = this->undoWhiteCastleLeft;
    this->whiteCastleRight = this->undoWhiteCastleRight;
    this->blackCastleLeft = this->undoBlackCastleLeft;
    this->blackCastleRight = this->undoBlackCastleRight;
    if (move.moveType == MoveType::basic || move.moveType == MoveType::doubleUp
        || move.moveType == MoveType::king || move.moveType == MoveType::rook)
        basicUndoMove(move);
    if (move.moveType == MoveType::castle)
    {
        this->board[move.from.poz.first][move.from.poz.second] = {move.piece->getPieceCode(move.piece->color),
                                                                  move.piece};
        this->board[move.to.poz.first][move.to.poz.second] = {PieceCode::empty, nullptr};
        move.piece->poz = move.from;
        if (move.to.poz.second == 6)
        {
            auto movedRook = this->board[move.from.poz.first][5].second;
            this->board[move.from.poz.first][7] = {movedRook->getPieceCode(movedRook->color), movedRook};
            this->board[move.from.poz.first][5] = {PieceCode::empty, nullptr};
            movedRook->poz.poz = {move.from.poz.first, 7};
        }
        if (move.to.poz.second == 2)
        {
            auto movedRook = this->board[move.from.poz.first][3].second;
            this->board[move.from.poz.first][0] = {movedRook->getPieceCode(movedRook->color), movedRook};
            this->board[move.from.poz.first][3] = {PieceCode::empty, nullptr};
            movedRook->poz.poz = {move.from.poz.first, 0};
        }
    }
    if (move.moveType == MoveType::enpasant)
    {

        basicUndoMove(move);
    }
    if (move.moveType == MoveType::promoteQueen or move.moveType == MoveType::promoteBishop
        or move.moveType == MoveType::promoteKnight or move.moveType == MoveType::promoteRook)
    {
        auto promotedPiece = this->board[move.to.poz.first][move.to.poz.second].second;
        promotedPiece->this_ptr = nullptr;
        this->board[move.to.poz.first][move.to.poz.second]={PieceCode::empty, nullptr};
        auto newEnd = std::remove(pieceList.begin(), pieceList.end(), promotedPiece);
        this->pieceList.erase(newEnd, this->pieceList.end());
        //delete promotedPiece;

        auto oldPawn = this->capturedPieces.top();
        this->capturedPieces.pop();
        this->board[move.from.poz.first][move.from.poz.second] = {oldPawn->getPieceCode(oldPawn->color),oldPawn};
        this->pieceList.push_back(oldPawn);
        if(!this->capturedPieces.empty() and this->capturedPieces.top() !=nullptr){
            auto oldPiece = this->capturedPieces.top();
            this->capturedPieces.pop();
//		this->capturedPiece = nullptr;
            this->board[move.to.poz.first][move.to.poz.second] = {oldPiece->getPieceCode(oldPiece->color), oldPiece};
            this->pieceList.push_back(oldPiece);
        }
    }

}

void Board::basicUndoMove(const Move &move)
{
    int tox = move.to.poz.first;
    int toy = move.to.poz.second;
    int fromx = move.from.poz.first;
    int fromy = move.from.poz.second;

    this->board[fromx][fromy] = {move.piece->getPieceCode(move.piece->color), move.piece};
    this->board[tox][toy] = {PieceCode::empty, nullptr};
        auto rip = this->capturedPieces.top();
        this->capturedPieces.pop();
    if (rip!=nullptr)
    {
        int capturedX = rip->poz.poz.first;
        int capturedY = rip->poz.poz.second;
        auto newPiece = rip;
        this->board[capturedX][capturedY] = {newPiece->getPieceCode(rip->color), newPiece};

        this->pieceList.push_back(newPiece);
//		this->capturedPiece = nullptr;
    }
    move.piece->poz = move.from;

}