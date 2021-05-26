#include "GeneralServices.h"
#include <fstream>
void GeneralServices::loadPosition(Board*& board)
{
	std ::ifstream cin("position.txt");
	std::string position, moveList;
	cin >> position >> moveList;
	cin.close();
	//parcurgere de string	
	//board->pieceList.push_back(//create piece)
	
}
void GeneralServices::savePosition(/*positionCreation*/)
{
	std::ofstream cout("position.txt");
	cout.open("position.txt", std::ios::out | std::ios::trunc);
	//cout << PiecePosition<< '\n';
	//cout <<moveList;
	cout.close();
}
std::string createPosition(const Board* board)
{
	std::string position;
	//for (auto piece : board->pieceList)
//	{
		//if(piece == )
	//}
	return position;
}