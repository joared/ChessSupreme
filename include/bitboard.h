#ifndef BITBOARD_H
#define BITBOARD_H

#include <cinttypes>
#include <string>

typedef uint64_t Bitboard;

namespace Bitboards 
{
  const std::string asBitset(Bitboard b);
}


#endif /* BITBOARD_H */
