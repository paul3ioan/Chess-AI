#include "Pawn.h"
#include <iostream>

PieceCode Pawn::getPieceCode(Color color)
{
    if (color == Color::white)
        return PieceCode::whitePawn;
    return PieceCode::blackPawn;
}

class Board;

std::vector<Move> Pawn::getLegalMoves(const Board &board)
{
    //std::cout << "PAWN\n";
    std::vector<Move> possibleMoves;
    std::pair<int, int> poz = this->poz.poz;

    std::pair<int, int> ans = {poz.first, poz.second};

    //check for white color
    if (this->color == Color::black)
    {
        // check one square up move
        if (board.board[ans.first + 1][ans.second].first == PieceCode::empty)
        {
            if (ans.first + 1 != 7)
                possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 1, poz.second)),
                                           MoveType::basic, this_ptr);
            else
                possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 1, poz.second)),
                                           MoveType::promote, this_ptr);
        }
        // check two square up move
        if (board.board[ans.first + 1][ans.second].first == PieceCode::empty && poz.first == 1
            && board.board[ans.first + 2][ans.second].first == PieceCode::empty)
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 2, poz.second)),
                                       MoveType::doubleUp, this_ptr);
        //check capture right

        if (ans.second + 1 < 8 && checkDifferentColor(board, ans.first + 1, ans.second + 1, Color::black) &&
            board.board[ans.first + 1][ans.second + 1].first != PieceCode::empty)
        {
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 1, poz.second + 1)),
                                       ans.first + 1 == 7 ? MoveType::promote : MoveType::basic,
                                       this_ptr);
        }
        //check capture left
        if (ans.second - 1 >= 0 && checkDifferentColor(board, ans.first + 1, ans.second - 1, Color::black) &&
            board.board[ans.first + 1][ans.second - 1].first != PieceCode::empty)
        {
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 1, poz.second - 1)),
                                       ans.first + 1 == 7 ? MoveType::promote : MoveType::basic,
                                       this_ptr);
        }
        // check enpasant
        if (board.moveList.size() > 1)
        {
            Move lastMove = board.moveList[board.moveList.size() - 1];
            Position from = lastMove.from;
            if (ans.first == 4 && lastMove.moveType == MoveType::doubleUp)
            {
                if (from.poz.second == ans.second - 1)
                    possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first - 1, poz.second - 1)),
                                               MoveType::enpasant, this_ptr);
                if (from.poz.second == ans.second + 1)
                    possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first - 1, poz.second + 1)),
                                               MoveType::enpasant, this_ptr);

            }
        }

    }

    if (this->color == Color::white)
    {
        // check one square up move

        //std::
        if (board.board[ans.first - 1][ans.second].first == PieceCode::empty)
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first - 1, poz.second)),
                                       ans.first - 1 == 0 ? MoveType::promote : MoveType::basic,
                                       this_ptr);

        // check two square up move

        if (board.board[ans.first - 1][ans.second].first == PieceCode::empty && poz.first == 6
            && board.board[ans.first - 2][ans.second].first == PieceCode::empty)
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first - 2, poz.second)),
                                       MoveType::doubleUp, this_ptr);
        //check capture right
        if (ans.second + 1 < 8 && checkDifferentColor(board, ans.first - 1, ans.second + 1, Color::white) &&
            board.board[ans.first - 1][ans.second + 1].first != PieceCode::empty)
        {
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first - 1, poz.second + 1)),
                                       ans.first - 1 == 0 ? MoveType::promote : MoveType::basic,
                                       this_ptr);
        }
        //check capture left
        if (ans.second - 1 >= 0 && checkDifferentColor(board, ans.first - 1, ans.second - 1, Color::white) &&
            board.board[ans.first - 1][ans.second - 1].first != PieceCode::empty)
        {
            possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first - 1, poz.second - 1)),
                                       ans.first - 1 == 0 ? MoveType::promote : MoveType::basic,
                                       this_ptr);
        }
        // check enpasant
        if (board.moveList.size() > 1)
        {
            Move lastMove = board.moveList[board.moveList.size() - 1];

            Position from = lastMove.from;

            if (ans.first == 3 && lastMove.moveType == MoveType::doubleUp)
            {

                if (from.poz.second == ans.second - 1)

                    possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 1, poz.second - 1)),
                                               MoveType::enpasant, this_ptr);

                if (from.poz.second == ans.second + 1)

                    possibleMoves.emplace_back(Position(poz), Position(std::make_pair(poz.first + 1, poz.second + 1)),
                                               MoveType::enpasant, this_ptr);


            }
        }
    }
    return possibleMoves;
}