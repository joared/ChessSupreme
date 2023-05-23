#ifndef PIECE_H
#define PIECE_H

#include "bitboard.h"

//#include "position.h"
class Position; // Forward declaration

#include <vector>

enum PieceType : int 
{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_TYPE_N, PIECE_INVALID = -1

};

std::string pieceTypeToStr(PieceType pt, Color c);

struct Piece
{
    Piece(PieceType pt=PIECE_INVALID, Color c=COLOR_INVALID) : pieceType(pt), color(c) {};
    static Piece fromChar(const char c);

    friend bool operator==(const Piece& p1, const Piece &p2);

    PieceType pieceType;
    Color color;
};

bool operator==(const Piece& p1, const Piece &p2);

template <PieceType>
Bitboard pseduoMovesBB(Color c, Square s, const Position* p=nullptr);

template <>
Bitboard pseduoMovesBB<KING>(Color c, Square s, const Position* p);

template <>
Bitboard pseduoMovesBB<KNIGHT>(Color c, Square s, const Position* p);

template <>
Bitboard pseduoMovesBB<ROOK>(Color c, Square s, const Position* p);

template <>
Bitboard pseduoMovesBB<BISHOP>(Color c, Square s, const Position* p);

template <>
Bitboard pseduoMovesBB<QUEEN>(Color c, Square s, const Position* p);

template <>
Bitboard pseduoMovesBB<PAWN>(Color c, Square s, const Position* p);

#endif /* PIECE_H */
