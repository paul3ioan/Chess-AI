#include <iostream>
#include<vector>
#include "Piece.h"
#include<set>
#include<stdlib.h>
#include "Board.h"
#include <sstream>
#include "GeneralServices.h"

using namespace std;

[[noreturn]] void loop();
//const string position = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
//const string position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const string position = "rnbqkbnr/1ppppppp/8/8/8/p7/1PPPPPPP/1NBQKBNR b KQ kq - 0 1";
std::shared_ptr<Piece> getPiece(Board &board, string arg);

pair<string, string> decodeCommand(const string &command);
void updateStatus(Board &board);
Move getMove(Board &board, string);

int main()
{
    loop();

}
vector<Move> moves;
[[noreturn]] void loop()
{
	Board board;
//	GeneralServices::restartPosition(board,"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//    GeneralServices::restartPosition(board,);
	while (1)
	{
		int x = 5;
		string input;
		getline(cin, input);
		auto [command, arguments] = decodeCommand(input);
        if(command == "status")
            ;
		if (command == "loadPosition")
        {
            GeneralServices::restartPosition(board, position);
            cout << position << '\n';
        }

		else
			if (command == "savePosition")
				GeneralServices::savePosition(board);
			else
				if (command == "getMovesPiece")
				{
                    moves.clear();

					auto piece = getPiece(board,arguments);
                    moves = piece->getLegalMoves(board);
					vector<pair<int,char>> output;
                    unordered_map<int,bool> promotingPiece;
                    for(const Move move : moves)
                    {
                        if(board.makeMove(move)) {
                            board.undoMove(move);
                            int line = move.to.poz.first;
                            int col = move.to.poz.second;
                            if (move.moveType == MoveType::enpasant)
                                output.push_back({(line * 8) + col, 'e'});
                            else if ((move.moveType == MoveType::promoteBishop or move.moveType == MoveType::promoteQueen
                                     or move.moveType == MoveType::promoteKnight or
                                     move.moveType == MoveType::promoteRook) ) {
                                if(promotingPiece[line*8 + col])
                                    continue;
                                output.push_back({(line * 8) + col, 'p'});
                                promotingPiece[line*8 + col] = true;

                            }
                                    else
                                output.push_back({(line * 8) + col, '/'});
                        }
                    }

					cout << output.size() << '\n';
					for (auto i : output)
                    {
                        cout << i.first ;
                        cout<< i.second << '\n';
                    }
					cout.flush();
					// check for pin 
					// make notation functie si pusa aici
				}
				else
					if (command == "playerMove")
					{
						auto move = getMove(board, arguments);
                        board.makeMove(move);
                        board.moveList.push_back(move);
                        updateStatus(board);
                        //status pentru interfata functie separata
						}
					else if (command == "playerUndo")
						auto move = getMove(board, arguments);
					else
						if (command == "AI move")
							;

	}
}

pair<string, string> decodeCommand(const string &command)
{
    int pozSpace = command.find(' ');
    return
            {
                    command.substr(0, pozSpace), command.substr(pozSpace + 1)
            };
}

std::shared_ptr<Piece> getPiece(Board &board, string arg)
{
    int line = arg[1] - '1';
    int col = arg[0] - 'a';
    return board.board[line][col].second;
}

Move getMove(Board &board, string arguments)
{

 /*   stringstream geek(arguments);
    int pos = 0;
    geek>>pos;
    int line = pos / 8;
    int col = pos % 8;
*/
    char promotedPiece = NULL;
    int pos = 0;
    for(char c : arguments)
    {
        if(c >= '0' and c <= '9')
            pos = pos * 10 + (c - '0');
        else if(c != '/')
        {
            promotedPiece = c;
        }

    }
    int line = pos / 8;
    int col = pos % 8;
    for(auto move:moves)
    {
        if(move.to.poz.first == line and move.to.poz.second == col )
        {
            if(promotedPiece == NULL)
            return move;
            else{
                if(move.moveType==MoveType::promoteKnight and promotedPiece == 'n')
                    return move;
                if(move.moveType==MoveType::promoteBishop and promotedPiece == 'b')
                    return move;
                if(move.moveType==MoveType::promoteRook and promotedPiece == 'r')
                    return move;
                if(move.moveType==MoveType::promoteQueen and promotedPiece == 'q')
                    return move;
            }
        }
    }

}
void updateStatus(Board& board) {

    bool canMove = false;
    //change the player who move
    if (board.whoMove == Color::black)
        board.whoMove = Color::white;
    else
        board.whoMove = Color::black;
    Board board2 = board;
    //test possible moves
    for (auto piece: board2.pieceList) {
        if (piece->color == board2.whoMove) {
            auto moves = piece->getLegalMoves(board2);
            for (auto move: moves) {
                if (board2.makeMove(move)) {
                    board2.undoMove(move);
                    canMove = true;
                    break;
                }
            }
            if (canMove)
                break;
        }
    }
    board2.whoMove == Color::white ? cout << 'w' : cout << 'b';
    if (canMove)
    {
        cout <<"0\n";
        return;
    }

    shared_ptr<Piece> king;
    for (auto piece: board2.pieceList) {
        if (piece->color == board2.whoMove) {
            if (piece->getPieceCode(piece->color) == (
                    piece->color == Color::white ? PieceCode::whiteKing : PieceCode::blackKing)) {
                king = piece;
                break;
            }
        }
    }
    if(board2.whoMove==Color::black and board2.attackedBlack[king->poz.poz.first][king->poz.poz.second])
    {

        cout <<"m\n";
        return;
    }
    if(board2.whoMove==Color::white and board2.attackedWhite[king->poz.poz.first][king->poz.poz.second])
    {

        cout <<"m\n";
        return;
    }

    cout <<"d\n";
}