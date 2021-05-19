#pragma once
#include <string>
class Position {
public:
	std::pair< uint8_t, uint8_t> poz;
	std::string chessNote();
};