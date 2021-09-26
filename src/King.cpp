#include "King.h"
#include <iostream>

PieceCode King::getPieceCode(Color color)
{
    if (color == Color::white)
        return PieceCode::whiteKing;
    return PieceCode::blackKing;
}

std::vector<Move> King::getLegalMoves(const Board &board)
{
    std::vector<Move> possibleMoves;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, 0, -1, 1};
    // normal move
    for (int i = 0; i < 8; i++)
    {

        int line = poz.poz.first + dx[i];
        int col = poz.poz.second + dy[i];

        if (line < 0 || col < 0 || line > 7 || col > 7)
            continue;
        if (this->checkDifferentColor(board, line, col, this->color))
        {
            if (this->color == Color::white)
            {
                if (board.attackedWhite[line][col])
                    continue;
            } else
            {
                if (board.attackedBlack[line][col])
                    continue;
            }
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(line, col)), MoveType::king,
                                       this_ptr);
        }
    }
    //castles
    if (this->color == Color::white && board.whiteCastleLeft && board.board[7][0].first == PieceCode::whiteRook)
    {
        if (!(board.attackedWhite[7][4] || board.attackedWhite[7][3] || board.attackedWhite[7][2]))
        {
            bool flag = true;
            for (int i = 1; i <= 3; i++)
                if (board.board[7][i].first != PieceCode::empty)
                    flag = false;
            if (flag)
                possibleMoves.emplace_back(Position(poz), Position(std::make_pair(7, 2)), MoveType::castle,
                                           this_ptr);
        }
    }
    if (this->color == Color::white && board.whiteCastleRight)
    {
        if (!(board.attackedWhite[7][4] || board.attackedWhite[7][5] || board.attackedWhite[7][6]) &&
            board.board[7][7].first == PieceCode::whiteRook)
        {

            bool flag = true;
            for (int i = 5; i <= 6; i++)
                if (board.board[7][i].first != PieceCode::empty)
                    flag = false;
            if (flag)
                possibleMoves.emplace_back(Position(poz), Position(std::make_pair(7, 6)), MoveType::castle,
                                           this_ptr);

        }
    }
    if (this->color == Color::black && board.blackCastleLeft)
    {
        if (!(board.attackedBlack[0][4] || board.attackedBlack[0][3] || board.attackedBlack[0][2]) &&
            board.board[0][0].first == PieceCode::blackRook)
        {
            bool flag = true;
            for (int i = 1; i <= 3; i++)
                if (board.board[0][i].first != PieceCode::empty)
                    flag = false;
            if (flag)
                possibleMoves.emplace_back(Position(poz), Position(std::make_pair(0, 2)), MoveType::castle,
                                           this_ptr);
        }
    }
    if (this->color == Color::black && board.blackCastleRight && board.board[0][7].first == PieceCode::blackRook)
    {
        if (!(board.attackedBlack[0][4] || board.attackedBlack[0][5] || board.attackedBlack[0][6]))
        {
            bool flag = true;
            for (int i = 5; i <= 6; i++)
                if (board.board[0][i].first != PieceCode::empty)
                    flag = false;
            if (flag)
                possibleMoves.emplace_back(Position(poz), Position(std::make_pair(0, 6)), MoveType::castle,
                                           this_ptr);
        }

    }

    return possibleMoves;
}