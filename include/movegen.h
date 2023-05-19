#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "position.h"
#include "piece.h"
#include "move.h"

class MoveGenerator
{
    public:
        MoveGenerator();
        std::vector<Move> generateMoves(const Position& p, std::vector<Move>& moves, bool validateMoves=true);
    private:
        template <PieceType pt>
        std::vector<Move>& generateMoves(const Position& p, std::vector<Move>& moves, bool validateMoves=true);
        std::vector<Move>& generatePawnMoves(const Position& p, std::vector<Move>& moves, bool validateMoves=true);
        std::vector<Move> m_tempMoves;
};

#endif /* MOVEGEN_H */
