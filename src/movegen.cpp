#include "movegen.h"
#include "piece.h"
#include <iostream> // for debugging

std::vector<Move> MoveGenerator::generateMoves(const Position& p, std::vector<Move>& moves, bool validateMoves)
{
    moves = generateMoves<KING>(p, moves, validateMoves);
    moves = generateMoves<QUEEN>(p, moves, validateMoves);
    moves = generateMoves<KNIGHT>(p, moves, validateMoves);
    moves = generateMoves<ROOK>(p, moves, validateMoves);
    moves = generateMoves<BISHOP>(p, moves, validateMoves);
    moves = generateMoves<PAWN>(p, moves, validateMoves);
    //moves = generatePawnMoves(p, moves, validateMoves); // TODO

    return moves;
}

MoveGenerator::MoveGenerator()
{
    m_tempMoves.reserve(256);
}

template <PieceType pt>
std::vector<Move> &MoveGenerator::generateMoves(const Position &p, std::vector<Move> &moves, bool validateMoves)
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
            
            // Check if the move is valid (does not put own king in check)
            if (validateMoves)
            {
                Position tempPos = p;
                
                tempPos.makeMove(candidateMove);
                m_tempMoves.clear();
                auto tempMoves = generateMoves(tempPos, m_tempMoves, false);
                
                // "isInCheck" ?
                Bitboard kingSquareBB = tempPos.pieceTypeBB(p.toMove(), KING);
                Square kingSquare = kingSquareBB.popLsb();
                assert(kingSquareBB == 0); // There should only be one king
                bool isInCheck = false;
                for ( Move m : tempMoves )
                {
                    if (m.to == kingSquare)
                    {
                        // King is in check
                        isInCheck = true;
                        break;
                    }
                }
                if (!isInCheck)
                {
                    moves.push_back(candidateMove);
                }
            }
            else
            {
                moves.push_back(candidateMove);
            }
            
        }
    }

    return moves;
}

std::vector<Move> &MoveGenerator::generatePawnMoves(const Position &p, std::vector<Move> &moves, bool validateMoves)
{
    Bitboard friendly, target, allPieces, movesBB;
    Color c = p.toMove();
    friendly = p.pieces(c);
    target = p.target(c);
    allPieces = friendly | target;

    Bitboard pawnsBB = p.pieceTypeBB(c, PAWN);
    Direction d = c == WHITE ? NORTH : SOUTH;
    Direction atkd1 = c == WHITE ? NORTH_EAST : SOUTH_EAST;
    Direction atkd2 = c == WHITE ? NORTH_WEST : SOUTH_WEST;
    Bitboard startRank = WHITE ? (0xFFULL << 1) : (0xFFULL << 6);
    Bitboard firstRank = WHITE ? 0xFFULL : (0xFFULL << 7);
    
    // Single step
    Bitboard singlePushBB;
    //singlePushBB = (~firstRank & (pawnsBB << d));
    //singlePushBB = (pawnsBB << d);
    singlePushBB = pawnsBB;
    std::cout << pawnsBB.prettyBoard() << std::endl;
    //singlePushBB &= ~allPieces;

    // Double step
    Bitboard doublePushBB;
    doublePushBB = (~firstRank & (movesBB << d));
    doublePushBB &= ~allPieces;

    // Attacks
    Bitboard attacksBB1;
    Bitboard fileA = 0x0101010101010101;
    attacksBB1 |= ((pawnsBB << atkd1) & fileA);
    attacksBB1 &= target;

    Bitboard attacksBB2;
    Bitboard fileH = fileA << 7;
    attacksBB2 |= ((pawnsBB << atkd2) & fileH);
    attacksBB2 &= target;

    std::vector<Move> candidateMoves;

    while (singlePushBB)
    {
        Square to = singlePushBB.popLsb();
        candidateMoves.push_back(Move(to >> d, to));
    }

    // while (doublePushBB)
    // {
    //     Square to = doublePushBB.popLsb();
    //     candidateMoves.push_back(Move((to >> d) >> d, to));
    // }

    // while (attacksBB1)
    // {
    //     Square to = attacksBB1.popLsb();
    //     candidateMoves.push_back(Move(to >> atkd1, to));
    // }

    // while (attacksBB2)
    // {
    //     Square to = attacksBB2.popLsb();
    //     candidateMoves.push_back(Move(to >> atkd2, to));
    // }

    for (Move candidateMove : candidateMoves)
    {
        // Check if the move is valid (does not put own king in check)
        if (validateMoves)
        {
            Position tempPos = p;
            
            tempPos.makeMove(candidateMove);
            std::vector<Move> nextMoves;
            generateMoves(tempPos, nextMoves, false);
            
            // "isInCheck" ?
            Bitboard kingSquareBB = tempPos.pieceTypeBB(p.toMove(), KING);
            Square kingSquare = kingSquareBB.popLsb();
            assert(kingSquareBB == 0); // There should only be one king
            bool isInCheck = false;
            for ( Move m : nextMoves )
            {
                if (m.to == kingSquare)
                {
                    // King is in check
                    isInCheck = true;
                    break;
                }
            }
            if (!isInCheck)
            {
                moves.push_back(candidateMove);
            }
        }
        else
        {
            moves.push_back(candidateMove);
        }
        
    }

    return moves;
}
