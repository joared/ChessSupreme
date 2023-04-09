#include <bitset>
#include "bitboard.h"


const std::string Bitboards::asBitset(Bitboard b)
{
  return std::bitset<64>(b).to_string();
}