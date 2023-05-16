#include <gtest/gtest.h>
#include "piece.h"

TEST(PieceTest, CopyConstructor)
{
    Piece p(PAWN, WHITE);
    Piece p2 = p;
    ASSERT_EQ(PAWN, p2.pieceType);
    ASSERT_EQ(WHITE, p2.color);
}

TEST(PieceTest, KnightPseudoMoveBB)
{
    Color c = WHITE;
    Square s = 17;
    auto b = pseduoMovesBB<KNIGHT>(c, s);
}

TEST(PieceTest, PawnPseudoMoveBB)
{
    Color c = WHITE;
    Square s = 10;
    auto b = pseduoMovesBB<PAWN>(c, s);

    Bitboard maskValid = squareBB(18) | squareBB(26);
    bool t = b & maskValid;
    bool f = b & ~maskValid;
    ASSERT_TRUE(t);
    ASSERT_FALSE(f);
}