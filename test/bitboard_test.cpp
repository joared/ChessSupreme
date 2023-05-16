#include <gtest/gtest.h>
#include "bitboard.h"

TEST(BitboardTest, Equal) 
{ 
    ASSERT_EQ(2, Bitboard(2));
    ASSERT_EQ(3, Bitboard(3));
    ASSERT_EQ(4, Bitboard(4));
};
 
TEST(BitboardTest, NotEqual) 
{
    ASSERT_NE(3, Bitboard(2));
    ASSERT_NE(2, Bitboard(3));
};

TEST(BitboardTest, Plus)
{
    Bitboard b(1);
    ASSERT_EQ(3, b + 2);
    ASSERT_EQ(6, 5 + b);
    ASSERT_EQ(2, b + b);
    ASSERT_EQ(b, b + b - b);
};

TEST(BitboardTest, PlusEqual)
{
    Bitboard b(1);
    b += 1;
    ASSERT_EQ(2, b);
    b += 2;
    ASSERT_EQ(4, b);
    b += 3;
    ASSERT_EQ(7, b);
};

TEST(BitboardTest, MinusEqual)
{
    Bitboard b(6);
    b -= 1;
    ASSERT_EQ(5, b);
    b -= 2;
    ASSERT_EQ(3, b);
    b -= 3;
    ASSERT_EQ(0, b);
};

TEST(BitboardTest, BitwiseOperators)
{
    // AND
    ASSERT_TRUE(Bitboard(1) & Bitboard(1));
    ASSERT_TRUE(Bitboard(1) & Bitboard(3));
    ASSERT_FALSE(Bitboard(1) & Bitboard(2));
};

TEST(BitboardTest, BitwiseNot)
{
    ASSERT_EQ(-Bitboard(12342), Bitboard(-12342));
    std::cout << -Bitboard(12342) << std::endl;
};

TEST(BitboardTest, PrettyStrings)
{
    Bitboard b(1);
    //std::cout << b.prettyBitset() << std::endl;
    //std::cout << b.prettyBoard() << std::endl;
};

TEST(BitboardTest, FileRankOf)
{
    Square s = 0;
    for (int r=0; r<8; r++)
    {
        for (int f=0; f<8; f++)
        {
            Square s = f + (r<<3);
            ASSERT_EQ(f, fileOf(s));
            ASSERT_EQ(r, rankOf(s));
        }
    }
};

TEST(BitboardTest, PopLSB)
{
    Bitboard b(0);
    for (Square s=63; s>=0; s--)
    {
        b |= squareBB(s);
        Bitboard bTemp = b;
        Square lsb = bTemp.popLsb();
        ASSERT_EQ(lsb, s);
        Bitboard correct = b - squareBB(s);
        ASSERT_EQ(correct, bTemp);
    }
};