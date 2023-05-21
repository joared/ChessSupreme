#include "chesshandler.h"

ChessHandler::ChessHandler()
{
    m_validMoves.reserve(256);
    m_position = Position::standardPosition();
    generateMoves();
}

ChessHandler::ChessHandler(std::string fen)
{
    m_validMoves.reserve(256);
    m_position = Position::fromFEN(fen);
    generateMoves();
}

std::string ChessHandler::pretty(Bitboard b)
{
    return m_position.pretty(b);
}

Color ChessHandler::toMove()
{
    return m_position.toMove();
}

const Position& ChessHandler::position() const
{
    return m_position;
}

std::vector<Move>& ChessHandler::validMoves()
{
    return m_validMoves;
}

Bitboard ChessHandler::validMoves(Square from)
{
    Bitboard moves;
    for (Move m : m_validMoves)
    {
        if (from == m.from)
        {
            moves |= squareBB(m.to);
        }
    }
    return moves;
}

bool ChessHandler::isValidFrom(Square from)
{
    for (Move m : m_validMoves )
    {
        if (m.from == from)
        {
            return true;
        }
    }
    return false;
}

bool ChessHandler::isValidMove(Move m)
{
    for (Move validMove : m_validMoves )
    {
        if ((m.from == validMove.from) && (m.to == validMove.to))
        {
            return true;
        }
    }
    return false;
}

void ChessHandler::makeMove(Move m, bool generateNewMoves)
{
    m_history.push_back(m);
    m_position.makeMove(m);
    
    if (generateNewMoves)
    {
        generateMoves();
    }
}

void ChessHandler::undo(bool generateNewMoves)
{
    if (m_history.size() > 0)
    {
        Move& prevMove = m_history.back();
        m_history.pop_back();
        m_position.undoMove(prevMove);

        if (generateNewMoves)
        {
            generateMoves();
        }
    }
}

const std::vector<Move>& ChessHandler::generateMoves()
{
    m_validMoves.clear();
    m_validMoves = m_generator.generateMoves(m_position, m_validMoves);
    return m_validMoves;
}

uint64_t ChessHandler::perft(int depth)
{
    // https://www.chessprogramming.org/Perft
    if (depth == 0)
    {
        return 1ULL;
    }
    int nodes = 0;
    auto moves = generateMoves();

    for (Move& m : moves)
    {
        makeMove(m, false);
        nodes += perft(depth-1);
        undo(false);
    }
    return nodes;
}
