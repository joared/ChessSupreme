#include "piece.h"
#include "position.h"
#include <iostream>
#include <stdexcept>

std::string pieceTypeToStr(PieceType pt, Color c)
{
    std::string s;
    switch (pt)
    {
        case PAWN:
            s = "p";
            break;
        case KING:
            s = "k";
            break;
        case KNIGHT:
            s = "n";
            break;
        case BISHOP:
            s = "b";
            break;
        case ROOK:
            s = "r";
            break;
        case QUEEN:
            s = "q";
            break;
        case PIECE_INVALID:
            s = " ";
            break;
        default:
            assert(false);
            break;
    }

    s = (c == WHITE) ? std::string(1, toupper(s[0])) : s;

    return s;
}

bool operator==(const Piece &p1, const Piece &p2)
{
    return (p1.color == p2.color) && (p1.pieceType == p2.pieceType);
}

Piece Piece::fromChar(const char c)
{
    switch (c)
    {
        case 'P': return Piece(PAWN, WHITE); break;
        case 'p': return Piece(PAWN, BLACK); break;
        case 'K': return Piece(KING, WHITE); break;
        case 'k': return Piece(KING, BLACK); break;
        case 'N': return Piece(KNIGHT, WHITE); break;
        case 'n': return Piece(KNIGHT, BLACK); break;
        case 'B': return Piece(BISHOP, WHITE); break;
        case 'b': return Piece(BISHOP, BLACK); break;
        case 'R': return Piece(ROOK, WHITE); break;
        case 'r': return Piece(ROOK, BLACK); break;
        case 'Q': return Piece(QUEEN, WHITE); break;
        case 'q': return Piece(QUEEN, BLACK); break;
        default: throw std::runtime_error("Invalid piece character: " + std::to_string(c));
    }
}

template <>
Bitboard pseduoMovesBB<KING>(Color c, Square s, const Position* p)
{
    Bitboard moves;
    moves |= safeDestination(s, NORTH);
    moves |= safeDestination(s, NORTH + EAST);
    moves |= safeDestination(s, EAST);
    moves |= safeDestination(s, EAST + SOUTH);
    moves |= safeDestination(s, SOUTH);
    moves |= safeDestination(s, SOUTH + WEST);
    moves |= safeDestination(s, WEST);
    moves |= safeDestination(s, WEST + NORTH);

    if (p)
    {
        Bitboard friendly = p->pieces(c);
        moves &= ~friendly;
    }
    
    return moves;
}

template <>
Bitboard pseduoMovesBB<KNIGHT>(Color c, Square s, const Position* p)
{
    Bitboard moves;
    int maxDist = 3;
    moves |= safeDestination(s, NORTH + NORTH + WEST, maxDist);
    moves |= safeDestination(s, NORTH + NORTH + EAST, maxDist);
    moves |= safeDestination(s, EAST + EAST + NORTH, maxDist);
    moves |= safeDestination(s, EAST + EAST + SOUTH, maxDist);
    moves |= safeDestination(s, SOUTH + SOUTH + EAST, maxDist);
    moves |= safeDestination(s, SOUTH + SOUTH + WEST, maxDist);
    moves |= safeDestination(s, WEST + WEST + SOUTH, maxDist);
    moves |= safeDestination(s, WEST + WEST + NORTH, maxDist);

    if (p)
    {
        Bitboard friendly = p->pieces(c);
        moves &= ~friendly;
    }

    return moves;
}

template <>
Bitboard pseduoMovesBB<BISHOP>(Color c, Square s, const Position* p)
{
    Bitboard moves, friendly, target;
    std::vector<Direction> directions = {NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST};

    if (p)
    {
        friendly = p->pieces(c);
        target = p->target(c);
    }

    for (Direction d : directions)
    {
        Square to = s;
        while (Bitboard toBB = safeDestination(to, d))
        {
            if (toBB & friendly)
            {
                break;
            }
            else if (toBB & target)
            {
                moves |= toBB;                
                break;
            }
            moves |= toBB;
            to += d;
        }
    }

    return moves;
}

template <>
Bitboard pseduoMovesBB<ROOK>(Color c, Square s, const Position* p)
{
    // Bitboard movesHorizontal;
    // Bitboard movesVertical;
 
    // int rank = rankOf(s);
    // int file = fileOf(s);

    // movesHorizontal = 0xFFULL << (rank * NORTH);
    // movesVertical = (0x0101010101010101ULL) << (file * EAST);
    // return movesHorizontal | movesVertical;

    Bitboard moves;
    std::vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};

    Bitboard friendly;
    Bitboard target;

    if (p)
    {
        friendly = p->pieces(c);
        target = p->target(c);
    }

    for (Direction d : directions)
    {
        Square to = s;
        while (Bitboard toBB = safeDestination(to, d))
        {
            if (toBB & friendly)
            {
                break;
            }
            else if (toBB & target)
            {
                moves |= toBB;                
                break;
            }
            moves |= toBB;
            to += d;
        }
    }

    return moves;
}

template <>
Bitboard pseduoMovesBB<QUEEN>(Color c, Square s, const Position* p)
{
    Bitboard moves;
 
    moves |= pseduoMovesBB<BISHOP>(c, s, p);
    moves |= pseduoMovesBB<ROOK>(c, s, p);

    return moves;
}

template <>
Bitboard pseduoMovesBB<PAWN>(Color c, Square s, const Position* p)
{
    Bitboard friendly, target, allPieces, moves;
    if (p)
    {
        friendly = p->pieces(c);
        target = p->target(c);
        allPieces = friendly | target;
    }
    Direction d = c == WHITE ? NORTH : SOUTH;
    bool onStartRank = c == WHITE ? rankOf(s) == 1 : rankOf(s) == 6;

    // Single step
    moves |= safeDestination(s, d);
    moves &= ~allPieces;
    // Double step
    if (onStartRank && moves!=0)
    {
        moves |= safeDestination(s, d+d);
    }
    moves &= ~allPieces;

    // Attacks
    Bitboard attacks;
    attacks |= safeDestination(s, d+EAST);
    attacks |= safeDestination(s, d+WEST);
    attacks &= target;

    moves |= attacks;

    return moves;
}
