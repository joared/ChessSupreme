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
        ChessHandler(std::string fen = "");

        std::string pretty(Bitboard b = 0);
        Color toMove();
        const Position& position() const;
        const Position::State& state() const;
        std::vector<Move>& validMoves();
        Bitboard validMoves(Square from);
        bool isValidFrom(Square from);
        bool isValidMove(const Move& m);
        void makeSafeMove(Move m);
        void makeMove(Move m, bool generateNewMoves=true);
        void undo(bool generateNewMoves=true);

        const std::vector<Move>& generateMoves();

        // Performance testing
        uint64_t perft(int depth);
    private:
        Position m_position;
        std::vector<Move> m_validMoves;
        MoveGenerator m_generator;
        std::vector<Move> m_history;
        std::vector<Position::State> m_stateHistory;
};

typedef std::shared_ptr<ChessHandler> ChessHandlerPtr;

#endif /* CHESSHANDLER_H */
