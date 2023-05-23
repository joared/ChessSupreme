#include "chesshandler.h"
#include <iostream>
ChessHandler::ChessHandler(std::string fen)
{
    if (!fen.empty())
    {
        m_position = Position::fromFEN(fen);
    }
    else 
    {
        m_position = Position::standardPosition();
    }
    m_validMoves.reserve(256);
    m_history.reserve(10000000);
    m_stateHistory.reserve(10000000);
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

const Position::State& ChessHandler::state() const
{
    return m_position.state;
}

std::vector<Move>& ChessHandler::validMoves()
{
    return m_validMoves;
}

Bitboard ChessHandler::validMoves(Square from)
{
    Bitboard moves;
    for (Move& m : m_validMoves)
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
    for (Move& m : m_validMoves )
    {
        if (m.from == from)
        {
            return true;
        }
    }
    return false;
}

bool ChessHandler::isValidMove(const Move& m)
{
    for (Move& validMove : m_validMoves )
    {
        if ((m.from == validMove.from) && (m.to == validMove.to))
        {
            return true;
        }
    }
    return false;
}

void ChessHandler::makeSafeMove(Move m)
{
    for (Move& move : m_validMoves)
    {
        if ((m.from == move.from) && (m.to == move.to))
        {
            makeMove(move);
            return;
        }
    }
    throw std::runtime_error("Move is in valid.");
}

void ChessHandler::makeMove(Move m, bool generateNewMoves)
{
    // TODO: the state stuff should be handled in Position
    m_history.push_back(m);
    auto state = m_position.state;
    m_stateHistory.push_back(state);
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
        // TODO: the state stuff should be handled in Position
        Move prevMove = m_history.back();
        Position::State prevState = m_stateHistory.back();
        m_history.pop_back();
        m_stateHistory.pop_back();
        m_position.undoMove(prevMove);
        m_position.state = prevState;

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
