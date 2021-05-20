#pragma once
#include <string>
class Position {
public:
	Position(std::pair<uint8_t, uint8_t> poz) : poz(poz) {

	}
	std::pair< uint8_t, uint8_t> poz;
	std::string chessNote();
};