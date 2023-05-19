#ifndef CHESSHANDLER_H
#define CHESSHANDLER_H

#include "position.h"
#include "movegen.h"
#include "bitboard.h"
#include "move.h"

#include <vector>
#include <memory>

class ChessHandler
{
    public:
        ChessHandler();
        ChessHandler(std::string fen);

        std::string pretty(Bitboard b = 0);
        Color toMove();
        const Position& position() const;
        std::vector<Move>& validMoves();
        Bitboard validMoves(Square from);
        bool isValidFrom(Square from);
        bool isValidMove(Move m);
        bool makeMove(Move m, bool generateNewMoves=true);
        void undo(bool generateNewMoves=true);

        const std::vector<Move>& generateMoves();

        // Performance testing
        uint64_t perft(int depth);
    private:
        Position m_position;
        std::vector<Move> m_validMoves;
        MoveGenerator m_generator;
        std::vector<Position> m_history;
};

typedef std::shared_ptr<ChessHandler> ChessHandlerPtr;

#endif /* CHESSHANDLER_H */
