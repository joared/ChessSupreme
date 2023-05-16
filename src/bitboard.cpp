#include <bitset>
#include <string>
#include "bitboard.h"


const std::string Bitboard::prettyBitset()
{
  return std::bitset<64>(m_bb).to_string();
}

const std::string Bitboard::prettyBoard()
{
  /*
  Example:
      a   b   c   d   e   f   g   h
    +---+---+---+---+---+---+---+---+
  8 |   |   |   |   |   |   |   |   | 8
    +---+---+---+---+---+---+---+---+
  7 |   |   |   |   |   |   |   |   | 7
    +---+---+---+---+---+---+---+---+
  6 |   |   |   |   |   |   |   |   | 6
    +---+---+---+---+---+---+---+---+
  5 |   |   |   |   |   |   |   |   | 5
    +---+---+---+---+---+---+---+---+
  4 |   |   |   | X |   |   |   |   | 4
    +---+---+---+---+---+---+---+---+
  3 |   |   |   |   |   |   |   |   | 3
    +---+---+---+---+---+---+---+---+
  2 |   |   |   |   |   |   |   |   | 2
    +---+---+---+---+---+---+---+---+
  1 |   |   |   |   |   |   |   |   | 1
    +---+---+---+---+---+---+---+---+
      a   b   c   d   e   f   g   h
  */
  std::string s = "    a   b   c   d   e   f   g   h\n";
  s += "  +---+---+---+---+---+---+---+---+\n";

  for (int r=7; r >= 0; r--)
  {
    s += std::to_string(r+1) + " |";
    for (int f=0; f <= 7; f++)
    {
      int square = (r<<3) + f;
      Bitboard squareBB(1ULL<<square);
      s += m_bb & squareBB ? " X |" : "   |";
    }
    s += " " + std::to_string(r+1) + "\n";
    s += "  +---+---+---+---+---+---+---+---+\n";
  }
  s += "    a   b   c   d   e   f   g   h\n";

  return s;
}
