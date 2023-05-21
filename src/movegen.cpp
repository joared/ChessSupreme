#include "movegen.h"
#include "piece.h"
#include <iostream> // for debugging

MoveGenerator::MoveGenerator()
{
    m_tempMoves.reserve(256);
}

std::vector<Move>& MoveGenerator::generateMoves(Position& p, std::vector<Move>& moves, bool validateMoves)
{
    moves = generateMoves<KING>(p, moves, validateMoves);
    moves = generateMoves<QUEEN>(p, moves, validateMoves);
    moves = generateMoves<KNIGHT>(p, moves, validateMoves);
    moves = generateMoves<ROOK>(p, moves, validateMoves);
    moves = generateMoves<BISHOP>(p, moves, validateMoves);
    //moves = generateMoves<PAWN>(p, moves, validateMoves);
    moves = generatePawnMoves(p, moves, validateMoves);

    // Check if the move is valid (does not put own king in check)
    if (validateMoves)
    {
        for (auto it = moves.begin(); it != moves.end();)
        {
            Move& candidateMove = *it;
            
            Color toMove = p.toMove();
            p.makeMove(candidateMove);
            Bitboard pseudoMoves = generatePseudoMovesBB(p);
            Bitboard kingSquareBB = p.pieceTypeBB(toMove, KING);
            bool isInCheck = (kingSquareBB & pseudoMoves);
            p.undoMove(candidateMove);

            if (isInCheck)
            {
                moves.erase(it);
            }
            else
            {
                it++;
            }
            
        }
    }

    return moves;
}

template <PieceType pt>
std::vector<Move>& MoveGenerator::generateMoves(const Position &p, std::vector<Move>& moves, bool validateMoves)
{
    Bitboard piecesBB = p.pieceTypeBB(p.toMove(), pt);

    while (piecesBB)
    {
        Square from = piecesBB.popLsb();
        Piece piece = p.getPiece(from);
        Bitboard movesBB = pseduoMovesBB<pt>(piece.color, from, &p);

        while (movesBB)
        {
            Square to = movesBB.popLsb();
            Move candidateMove(from, to);
            candidateMove.capturedPiece = p.getPiece(to);
            moves.push_back(candidateMove);
        }
    }

    return moves;
}

std::vector<Move>& MoveGenerator::generatePawnMoves(const Position &p, std::vector<Move> &moves, bool validateMoves)
{
    Bitboard friendly, target, allPieces, movesBB;
    Color c = p.toMove();
    friendly = p.pieces(c);
    target = p.target(c);
    allPieces = friendly | target;

    Bitboard pawnsBB = p.pieceTypeBB(c, PAWN);
    Direction d =           (c == WHITE) ? NORTH : SOUTH;
    Direction atkd1 =       (c == WHITE) ? NORTH_EAST : SOUTH_EAST;
    Direction atkd2 =       (c == WHITE) ? NORTH_WEST : SOUTH_WEST;
    Bitboard startRank =    (c == WHITE) ? RANK_2 : RANK_7;
    Bitboard firstRank =    (c == WHITE) ? RANK_1 : RANK_8;
    
    // Single push
    Bitboard singlePushBB;
    singlePushBB = (~firstRank & (pawnsBB.shift(d)));
    singlePushBB = (pawnsBB.shift(d));
    singlePushBB &= ~allPieces;

    // Double push
    Bitboard doublePushBB;
    doublePushBB = (~firstRank & (singlePushBB.shift(d)));
    doublePushBB &= ~allPieces;
    Bitboard temp = startRank & pawnsBB;
    doublePushBB &= temp.shift(d+d);

    // Attacks
    Bitboard attacksBB1;
    Bitboard fileA = 0x0101010101010101;
    attacksBB1 |= ((pawnsBB.shift(atkd1)) & ~fileA);
    attacksBB1 &= target;

    Bitboard attacksBB2;
    Bitboard fileH = fileA << 7;
    attacksBB2 |= ((pawnsBB.shift(atkd2)) & ~fileH);
    attacksBB2 &= target;

    while (singlePushBB)
    {
        Square to = singlePushBB.popLsb();
        moves.push_back(Move(to - d, to));
    }

    while (doublePushBB)
    {
        Square to = doublePushBB.popLsb();
        Move move((to - d) - d, to);
        moves.push_back(move);
    }

    while (attacksBB1)
    {
        Square to = attacksBB1.popLsb();
        Move move(to - atkd1, to);
        move.capturedPiece = p.getPiece(move.to);
        moves.push_back(move);
    }

    while (attacksBB2)
    {
        Square to = attacksBB2.popLsb();
        Move move(to - atkd2, to);
        move.capturedPiece = p.getPiece(move.to);
        moves.push_back(move);
    }

    return moves;
}

Bitboard MoveGenerator::generatePseudoMovesBB(const Position &p)
{
    Bitboard moves;
    moves |= generatePseudoMovesBB<KING>(p);
    moves |= generatePseudoMovesBB<QUEEN>(p);
    moves |= generatePseudoMovesBB<KNIGHT>(p);
    moves |= generatePseudoMovesBB<ROOK>(p);
    moves |= generatePseudoMovesBB<BISHOP>(p);
    moves |= generatePseudoMovesBB<PAWN>(p);
    //moves = generatePawnMoves(p, moves, validateMoves);
    return moves;
}

template <PieceType pt>
Bitboard MoveGenerator::generatePseudoMovesBB(const Position &p)
{
    Bitboard piecesBB = p.pieceTypeBB(p.toMove(), pt);
    Bitboard movesBB;
    while (piecesBB)
    {
        Square from = piecesBB.popLsb();
        Piece piece = p.getPiece(from);
        movesBB |= pseduoMovesBB<pt>(piece.color, from, &p);
    }
    return movesBB;
}
