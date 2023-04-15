#ifndef BITBOARD_H
#define BITBOARD_H

#include <cinttypes>
#include <string>

class Bitboard
{
  public:
    constexpr Bitboard(uint64_t b): m_bb(b) {};
    const std::string prettyBitset();
    const std::string prettyBoard();

    // conversion operator to enable standard operations on bitboard
    // "const" is needed for GTest to compile
    constexpr operator uint64_t() const { return m_bb; };

    // Standard operators to manipulate bitboard
    constexpr Bitboard& operator+=(uint64_t b) { m_bb += 1; return *this;};
    constexpr Bitboard& operator-=(uint64_t b) { m_bb -= 1; return *this;};

  private:
    uint64_t m_bb;
};

#endif /* BITBOARD_H */
