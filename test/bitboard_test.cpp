#include "bitboard.h"
#include <gtest/gtest.h>

TEST(BitboardTest, Equal) 
{ 
    ASSERT_EQ(2, Bitboard(2));
    ASSERT_EQ(3, Bitboard(3));
    ASSERT_EQ(4, Bitboard(4));
}
 
TEST(BitboardTest, NotEqual) 
{
    ASSERT_NE(3, Bitboard(2));
    ASSERT_NE(2, Bitboard(3));
}

TEST(BitboardTest, Plus)
{
    Bitboard b(1);
    ASSERT_EQ(2, b + 1);
    ASSERT_EQ(2, 1 + b);
    ASSERT_EQ(2, b + b);
    ASSERT_EQ(b, b + b - b);
}

TEST(BitboardTest, PlusEqual)
{
    Bitboard b(1);
    b += 1;
    ASSERT_EQ(2, b);
    b += 1;
    ASSERT_EQ(3, b);
    b += 1;
    ASSERT_EQ(4, b);
}

TEST(BitboardTest, MinusEqual)
{
    Bitboard b(3);
    b -= 1;
    ASSERT_EQ(2, b);
    b -= 1;
    ASSERT_EQ(1, b);
    b -= 1;
    ASSERT_EQ(0, b);
}

TEST(BitboardTest, BitwiseOperators)
{
    // AND
    ASSERT_TRUE(Bitboard(1) & Bitboard(1));
    ASSERT_TRUE(Bitboard(1) & Bitboard(3));
    ASSERT_FALSE(Bitboard(1) & Bitboard(2));
}

TEST(BitboardTest, PrettyStrings)
{
    Bitboard b(1);
    //std::cout << b.prettyBitset() << std::endl;
    //std::cout << b.prettyBoard() << std::endl;
}