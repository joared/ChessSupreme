#ifndef BITBOARD_H
#define BITBOARD_H

#include <cinttypes>
#include <string>
#include <assert.h>
/*
NOTE TO SELF: If any definitions are made here, they should be constexpr or inline. 
Otherwise there will probably be a compilation error when building the tests indicating 
multiple definitions since many other .cpp files are including this file.
*/

enum Color : int
{
  WHITE, BLACK, COLOR_N, COLOR_INVALID
};

inline std::string colorToStr(Color color)
{
	switch (color)
	{
		case WHITE:
			return "White";
		case BLACK:
			return "Black";
		default:
			return "";
	}
};

// A valid Square is an int in range [0,63]
typedef int Square;
// Forward declarations
class Bitboard;
Bitboard squareBB(Square s);

enum Direction : int 
{
  NORTH = 8,
  EAST = 1,
  SOUTH = -NORTH,
  WEST = -EAST,
  NORTH_WEST = NORTH+WEST,
  NORTH_EAST = NORTH+EAST,
  SOUTH_WEST = SOUTH+WEST,
  SOUTH_EAST = SOUTH+EAST
};

class Bitboard
{
	public:
		constexpr Bitboard(uint64_t b = 0): m_bb(b) {};
		const std::string prettyBitset();
		const std::string prettyBoard();

		// conversion operator to enable standard operations on bitboard
		// "const" is needed for GTest to compile
		constexpr operator uint64_t() const { return m_bb; };

		// Pops least significant bit and returns as square
		// NOTE: GCC, Clang, ICC required (from stockfish)
		inline Square popLsb() 
		{ 
			assert(m_bb);
			Square s = Square(__builtin_ctzll(m_bb)); 
			m_bb &= (~squareBB(s)); 
			return s; 
		};

		inline Bitboard shift(int d)
		{
			return (d > 0) ? (m_bb << d) : (m_bb >> -d);
		}

		// Standard operators to manipulate bitboard
		inline Bitboard& operator+=(uint64_t b) { m_bb += b; return *this;};
		inline Bitboard& operator-=(uint64_t b) { m_bb -= b; return *this;};
		inline Bitboard& operator|=(uint64_t b) { m_bb |= b; return *this;};
		inline Bitboard& operator^=(uint64_t b) { m_bb ^= b; return *this;};
		inline Bitboard& operator&=(uint64_t b) { m_bb &= b; return *this;};

	private:
		uint64_t m_bb;
};

/*
Predefined ranks and files
*/
static Bitboard FILE_A = 0x0101010101010101;
static Bitboard FILE_H = FILE_A << 7;
static Bitboard RANK_1 = 0xFFULL;
static Bitboard RANK_2 = 0xFFULL << 8;
static Bitboard RANK_7 = 0xFFULL << 8*6;
static Bitboard RANK_8 = 0xFFULL << 8*7;

/*
Square and square related functions.
*/

constexpr bool validSquare(Square s)
{
  return (s >= 0) && (s <= 63);
}

inline Bitboard squareBB(Square s)
{
  assert(validSquare(s));
  return Bitboard(1ULL<<s);
}

constexpr int fileOf(Square s)
{
  return s % 8;
}

constexpr int rankOf(Square s)
{
  return s / 8;
}

constexpr Square squareFromFileRank(int file, int rank)
{
	return (rank<<3) + file;
}

inline std::string squareToStr(Square s)
{
	char file = 'a' + fileOf(s);
	char rank = '1' + rankOf(s);

	return std::string(1,file)+rank;
}

inline Square squareFromStr(std::string str)
{
	if (str.length() != 2)
	{
		return Square(-1);
	}

	int file = str[0] - 'a';
	int rank = str[1] - '1';
	
	Square square = ((rank<<3) + file);

	return validSquare(square) ? square : Square(-1);
}

inline int distance(Square from, Square to)
{
    int fDiff = abs(fileOf(to) - fileOf(from));
    int rDiff = abs(rankOf(to) - rankOf(from));
    return fDiff + rDiff;
}

inline Bitboard safeDestination(Square s, int step, int maxDist=2) {
    Square to = Square(s + step);
    return validSquare(to) && distance(s, to) <= maxDist ? squareBB(to) : Bitboard(0);
}
/*
\Square and square related functions.
*/

#endif /* BITBOARD_H */
