#ifndef POSITION_H
#define POSITION_H

#include "bitboard.h"
#include "piece.h"

class Position
{
    // A position has a state represented by this struct.
    // The state holds "time-dependent" information about the 
    // position. 
    // NOTE: We can se the State info for dynamic allocation
    // of information that can increase efficiency of calculating
    // moves.
    struct State
    {
        int rule50count;
        Square enPassantSquare;
    };

    public:
        Position();
        static Position standardPosition();
        bool isValidPosition(); // for debugging
        std::string pretty(Bitboard b=0);

        Color toMove() const;

        // returns a position from fen string
        static Position fromFEN(std::string fen);
        std::string toFEN() const;

        Bitboard pieceTypeBB(Color c, PieceType pt) const;

        // TODO
        //bool isInCheck(Color c);

        // Methods that modifies the internal board representation
        // NOTE: Doesn't work with inline, could be the compiler
        void placePiece(Piece p, Square s);
        void removePiece(Square s);
        bool makeMove(Move m);

        // Methods for retrieving piece placement information
        Piece getPiece(Square s) const;
        Bitboard pieces() const;
        Bitboard pieces(Color c) const;
        Bitboard target(Color c) const;
        
        // Some operators for conveniece
        friend bool operator==(const Position &p1, const Position &p2);

    private:
        Piece m_board[64];
        Bitboard m_piecesBB[COLOR_N][PIECE_TYPE_N];
        Color m_toMove;
        State state;
};

bool operator==(const Position &p1, const Position &p2);

#endif /* POSITION_H */
