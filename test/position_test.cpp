#include <gtest/gtest.h>
#include "position.h"

TEST(PositionTest, FromFen)
{
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Position p = Position::fromFEN(fen);
    Position pTrue = Position::standardPosition();
    bool eq = pTrue == p;
    ASSERT_TRUE(eq);
};

TEST(PositionTest, PlacePiece)
{
    Position p;
    Square s = 13;
    Bitboard sBB = squareBB(s);
    
    // First place a King at the square
    p.placePiece(Piece(KING, WHITE), s);
    Bitboard pieces = p.pieces();
    ASSERT_EQ(sBB, pieces);
    Bitboard kingBB = p.pieceTypeBB(WHITE, KING);
    ASSERT_EQ(sBB, kingBB);

    // Then place a Pawn at the same square
    p.placePiece(Piece(PAWN, WHITE), s);
    pieces = p.pieces();
    ASSERT_EQ(sBB, pieces);
    Bitboard pawnBB = p.pieceTypeBB(WHITE, PAWN);
    ASSERT_EQ(sBB, pawnBB);
};

TEST(PositionTest, RemovePiece)
{

};

TEST(PositionTest, MakeMove)
{
    Position p;
    Square s1 = 14;
    Square s2 = 56;
    
    p.placePiece(Piece(PAWN, WHITE), s1);
    p.placePiece(Piece(PAWN, WHITE), s2);

    Move m(s1, s2);
    p.makeMove(m);

    // Verify that the board centric representation is updated correctly
    Bitboard expected = squareBB(s2);
    Bitboard piecesActual = p.pieces();
    ASSERT_EQ(expected, piecesActual);
    Bitboard pawnActual = p.pieceTypeBB(WHITE, PAWN);
    ASSERT_EQ(expected, pawnActual);

    // Verify that the piece centric representation is updated correctly
    Piece piece = p.getPiece(s2);
    ASSERT_EQ(PAWN, piece.pieceType);
    ASSERT_EQ(WHITE, piece.color);
};