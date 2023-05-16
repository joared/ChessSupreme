#include "move.h"

std::string Move::toString()
{
     return squareToStr(from) + " -> " + squareToStr(to);
}

Move Move::fromString(std::string moveStr)
{
     if (moveStr.length() != 4)
     {
          return Move();
     }
     Square from = squareFromStr(moveStr.substr(0, 2));
     Square to = squareFromStr(moveStr.substr(2, 2));
     if (from == -1 || to == -1)
     {
          return Move();
     }
     return Move(from, to);
}

bool Move::isValid()
{
     return from != -1 && to != -1;
}
