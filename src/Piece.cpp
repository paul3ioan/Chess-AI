#include "Piece.h"
    std::shared_ptr<Piece> this_ptr;

bool Piece::checkDifferentColor(const Board &board, int line, int col, Color color)
{
    if (board.board[line][col].first == PieceCode::empty)
        return true;
    if (color == Color::white)
    {
        if (board.board[line][col].first == PieceCode::whiteKing ||
            board.board[line][col].first == PieceCode::whiteBishop ||
            board.board[line][col].first == PieceCode::whiteKnight ||
            board.board[line][col].first == PieceCode::whitePawn ||
            board.board[line][col].first == PieceCode::whiteQueen ||
            board.board[line][col].first == PieceCode::whiteRook)
            return false;
    }
    if (color == Color::black)
    {
        if (board.board[line][col].first == PieceCode::blackKing ||
            board.board[line][col].first == PieceCode::blackBishop ||
            board.board[line][col].first == PieceCode::blackKnight ||
            board.board[line][col].first == PieceCode::blackPawn ||
            board.board[line][col].first == PieceCode::blackQueen ||
            board.board[line][col].first == PieceCode::blackRook)
            return false;
    }
    return true;
}