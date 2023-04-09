#include "bitboard.h"
#include <gtest/gtest.h>

TEST(BitboardTest, Equal) { 
    ASSERT_EQ(2, Bitboard(2));
    ASSERT_EQ(3, Bitboard(3));
    ASSERT_EQ(4, Bitboard(4));
}
 
TEST(BitboardTest, NotEqual) {
    ASSERT_NE(3, Bitboard(2));
    ASSERT_NE(2, Bitboard(3));
}