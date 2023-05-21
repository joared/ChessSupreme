#ifndef MOVE_H
#define MOVE_H

#include "bitboard.h"
#include "piece.h"

struct Move
{
    Move(Square from=-1, Square to=-1) : from(from), to(to) {};
    std::string toString();
    static Move fromString(std::string moveStr);
    bool isValid();

    Square from;
    Square to;
    Piece capturedPiece;
    Piece promotionPiece;
};

#endif /* MOVE_H */
