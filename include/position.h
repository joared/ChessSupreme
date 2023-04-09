#ifndef POSITION_H
#define POSITION_H

#include "bitboard.h"

class Board: public IBoard
{
    public:
        virtual Bitboard getPieceTypeBB(PieceType pieceType, Color color);
        virtual bool isAttackedBy(Square square, Color color);
        virtual void makeMove(Move move);
        virtual void placePiece(Piece piece, Square square);

    private:
        Bitboard m_piecesBB[2][6]; // TODO: should not be hardcoded

};

#endif /* POSITION_H */
