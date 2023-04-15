#include "utility.h"
#include "move.h"
#include "piece.h"

#include "bitboard.h"

#include <iostream>
#include <bitset>
#include <math.h>

int main() {
  std::cout << "Welcome to the ChessSupreme!" << std::endl;

  while (true)
  {
    std::string shiftStr;
    uint64_t shift = 0;
    std::cin >> shiftStr;
    if (shiftStr == "q")
    {
      break;
    }
    try
    {
      shift = std::stoul(shiftStr.c_str(), nullptr, 10);
    }
    catch (std::exception)
    {
      std::cout << "Something went wrong..." << std::endl;  
    }
    // <takethis> <</>> <shift it this way, this much>
    std::cout << Bitboard(shift<<1).prettyBitset() << std::endl;
    std::cout << Bitboard(shift>>1).prettyBitset() << std::endl;
    std::cout << Bitboard(1<<shift).prettyBitset() << std::endl;
    std::cout << Bitboard(1>>shift).prettyBitset() << std::endl;
    std::cout << Bitboard(shift).prettyBoard() << std::endl;
  }
  return 0;
}