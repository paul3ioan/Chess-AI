#include "Knight.h"

PieceCode Knight::getPieceCode(Color color)
{
    if (color == Color::white)
        return PieceCode::whiteKnight;
    return PieceCode::blackKnight;
}

std::vector<Move> Knight::getLegalMoves(const Board &board)
{
    std::vector<Move> possibleMoves;
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int i = 0; i <= 7; i++)
    {
        int line = poz.poz.first + dx[i];
        int col = poz.poz.second + dy[i];
        if (line < 0 || col < 0 || col > 7 || line > 7)
            continue;
        if (checkDifferentColor(board, line, col, this->color))
        {
            //std::cout << line << " " << col << '\n';
            possibleMoves.emplace_back(Position(poz), Position({line, col}), MoveType::basic,
                                       this_ptr);
        }
    }

    return possibleMoves;
}