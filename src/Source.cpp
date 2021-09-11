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

Piece* getPiece(Board& board, string arg);
pair<string, string> decodeCommand(string command);
Move getMove(Board& board, string);
int main()
{
	loop();

}
vector<Move> moves;
[[noreturn]] void loop()
{
	Board board;
	GeneralServices::loadPosition(board);

	while (1)
	{
		int x = 5;
		string input;
		getline(cin, input);
		auto [command, arguments] = decodeCommand(input);
		if (command == "loadPosition")
			//GeneralServices::loadPosition(board, arguments)
			;
		else
			if (command == "savePosition")
				GeneralServices::savePosition(board);
			else
				if (command == "getMovesPiece")
				{
					//string s = "ceva";
					//char c = s[101];
					//throw "";
                    moves.clear();
					Piece* piece = getPiece(board,arguments);
                    moves = piece->getLegalMoves(board);
					vector<int> output;
					for (auto move : moves)
					{
						int line = move.to.poz.first;
						int col = move.to.poz.second;
						output.push_back( (line * 8) + col);
						
					}
					cout << output.size() << '\n';
					for (int i : output)
						cout << i << '\n';
					cout.flush();
					// check for pin 
					// make notation functie si pusa aici
				}
				else
					if (command == "playerMove")
					{
						auto move = getMove(board, arguments);
                        board.makeMove(move);

						}
					else if (command == "playerUndo")
						auto move = getMove(board, arguments);
					else
						if (command == "AI move")
							;

	}
}
pair<string, string> decodeCommand(string command)
{
	int pozSpace = command.find(' ');
	return 
	{
		command.substr(0, pozSpace), command.substr(pozSpace + 1)
	};
}
Piece* getPiece(Board& board, string arg)
{
	int line = arg[1] - '1';
	int col = arg[0] - 'a';
	return board.board[line][col].second;
}
Move getMove(Board& board,string arguments)
{
    stringstream geek(arguments);
    int pos = 0;
    geek>>pos;
    int line = pos / 8;
    int col = pos % 8;
	int fromCol = arguments[0]-'a', fromLine = arguments[1]-'1';
	int toCol = arguments[2]-'a', toLine = arguments[3]-'1';
    for(auto move:moves)
    {
        if(move.to.poz.first == line and move.to.poz.second == col)
            return move;
    }
//	Piece* piece = board.board[fromLine][fromCol].second;
//	MoveType moveType;
//	switch (arguments[5])
//	{
//	case'b':
//		moveType = MoveType::basic;
//		break;
//
//	case'c':
//		moveType = MoveType::castle;
//		break;
//
//	case'p':
//		moveType = MoveType::promote;
//		break;
//
//	case'e':
//		moveType = MoveType::enpasant;
//		break;
//
//	case'd':
//		moveType = MoveType::doubleUp;
//		break;
//
//	case'r':
//		moveType = MoveType::rook;
//		break;
//	case'k':
//		moveType = MoveType::king;
//		break;
//	default:
//		break;
//	}
//	return Move(Position({ fromLine, fromCol }), Position({ toLine, toCol }), moveType, piece);
}