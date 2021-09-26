#include "Position.h"

std::string Position::chessNote()
{
    char col = poz.second + 'a';
    return col + std::to_string(poz.first);
}
