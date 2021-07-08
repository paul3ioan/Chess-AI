#pragma once
#include "../Chess AI/GeneralServices.h"
#include "Board.h"
class BasicTest : public ::testing::Test
{
protected:
	int allMoves;
	Board board;
	virtual void SetUp()
	{	
	}
	void Init();
	virtual void TearDown() {
	}

};

