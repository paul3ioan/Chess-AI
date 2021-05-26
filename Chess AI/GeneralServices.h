#pragma once
#include "Board.h"

class GeneralServices
{
public:
	void loadPosition(Board*& board);
	void savePosition();
	std::string createPosition(const Board* board);
};

