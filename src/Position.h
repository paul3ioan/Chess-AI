#pragma once

#include <string>

class Position
{
public:
    Position(std::pair<int, int> poz) : poz(poz)
    {

    }

    std::pair<int, int> poz;

    std::string chessNote();
};