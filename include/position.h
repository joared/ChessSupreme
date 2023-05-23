#ifndef POSITION_H
#define POSITION_H

#include "bitboard.h"
#include "piece.h"
#include "move.h"

class Position
{
    // A position has a state represented by this struct.
    // The state holds "time-dependent" information about the 
    // position. 
    // NOTE: We can se the State info for dynamic allocation
    // of information that can increase efficiency of calculating
    // moves.
    public:
        struct State
        {
            //State(int rule50Count, Square enPSquare, Piece capturedPiece, Square capturedSquare)
            int rule50count = 0;
            Square enPassantSquare = -1;
            Piece capturedPiece = Piece();
            Square capturedSquare = -1;
            std::string toString() const;
        };

    public:
        Position();
        static Position standardPosition();
        bool isValidPosition() const; // for debugging
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
        void makeMove(Move& m);
        void undoMove(Move& m);

        // Methods for retrieving piece placement information
        Piece getPiece(Square s) const;
        Bitboard pieces() const;
        Bitboard pieces(Color c) const;
        Bitboard target(Color c) const;
        
        // Some operators for conveniece
        friend bool operator==(const Position &p1, const Position &p2);

        State state;
    private:
        Piece m_board[64];
        Bitboard m_piecesBB[COLOR_N][PIECE_TYPE_N];
        Color m_toMove;
};

bool operator==(const Position &p1, const Position &p2);

#endif /* POSITION_H */
