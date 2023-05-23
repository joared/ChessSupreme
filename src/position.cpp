#include "position.h"
#include "utility.h"
#include "piece.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

Position::Position() : m_toMove(WHITE), m_piecesBB()
{
    for (Square s=0; s < 64; s++)
    {
        m_board[s] = Piece(PIECE_INVALID, COLOR_INVALID);
    }
}

Position Position::standardPosition()
{
    Position position;
    for (int i=0; i < 8; i++)
    {
        position.placePiece(Piece(PAWN, WHITE), Square(8 + i));
        position.placePiece(Piece(PAWN, BLACK), Square(48 + i));
    }
    position.placePiece(Piece(ROOK, WHITE), Square(0));
    position.placePiece(Piece(ROOK, WHITE), Square(7));
    position.placePiece(Piece(ROOK, BLACK), Square(8*7));
    position.placePiece(Piece(ROOK, BLACK), Square(8*7+7));
    
    position.placePiece(Piece(KNIGHT, WHITE), Square(1));
    position.placePiece(Piece(KNIGHT, WHITE), Square(6));
    position.placePiece(Piece(KNIGHT, BLACK), Square(56+1));
    position.placePiece(Piece(KNIGHT, BLACK), Square(56+6));

    position.placePiece(Piece(BISHOP, WHITE), Square(2));
    position.placePiece(Piece(BISHOP, WHITE), Square(5));
    position.placePiece(Piece(BISHOP, BLACK), Square(56+2));
    position.placePiece(Piece(BISHOP, BLACK), Square(56+5));
    
    position.placePiece(Piece(QUEEN, WHITE), Square(3));
    position.placePiece(Piece(KING, WHITE), Square(4));

    position.placePiece(Piece(QUEEN, BLACK), Square(56+3));
    position.placePiece(Piece(KING, BLACK), Square(56+4));

    return position;
}

bool Position::isValidPosition() const
{
    for (Square s=0; s<64; s++)
    {
        Piece p = getPiece(s);
        if (p.pieceType != PIECE_INVALID)
        {
            if (!(m_piecesBB[p.color][p.pieceType] & squareBB(s)))
            {
                std::cout << "PieceBB " << pieceTypeToStr(p.pieceType, p.color) << " :\n" << m_piecesBB[p.color][p.pieceType].prettyBoard() << std::endl;
                std::cout << "SquareBB:\n" << squareBB(s).prettyBoard() << std::endl;
                return false;
            }
        }
        else
        {
            if( pieces() & squareBB(s) )
            {
                std::cout << "PieceBB NO PIECE :\n" << m_piecesBB[p.color][p.pieceType].prettyBoard() << std::endl;
                std::cout << "SquareBB:\n" << squareBB(s).prettyBoard() << std::endl;
                return false;
            }
        }
        
    }
    return true;
}

/*
Creates and returns a position from a fen string.
TODO: currently only piece placement is considered.
*/
Position Position::fromFEN(std::string fen)
{
    Position position;
    auto tokens = Utils::splitString(fen, " ");
    assert(tokens.size() == 6);

    // Setup pieces
    auto piecesByRank = Utils::splitString(tokens[0], "/");
    assert(piecesByRank.size() == 8);
    int rank = 7;
    int file = 0;
    for (auto rankString : piecesByRank)
    {
        for (auto it = rankString.begin(); it != rankString.end(); it++)
        {
            auto s = std::string(1, *it);
            int nEmptySquares = 0;
            try
            {
                nEmptySquares = std::stoi(s);
            }
            catch(const std::invalid_argument& e)
            {}
            
            if (nEmptySquares > 0)
            {
                assert((nEmptySquares + file) <= 8);
                for (int i=0; i<nEmptySquares; i++)
                {
                    position.placePiece(Piece(), Square((rank<<3) + file));
                    file++;
                }
            }
            else
            {
                Piece p = Piece::fromChar(s[0]);
                position.placePiece(p, Square((rank<<3) + file));
                file++;
            }
        }
        file = 0;
        rank--;
    }

    // Turn to move
    auto colorStr = tokens[1];
    if (colorStr != "w" && colorStr != "b") { throw std::runtime_error("Invalid active color in fen string: " + colorStr); }
    Color c = colorStr == "w" ? WHITE : BLACK;
    position.m_toMove = c;

    // TODO: Castling rights
    auto castlingRights = tokens[2];

    // TODO: Enpassant square
    auto enPassantSquare = tokens[3];
    assert(enPassantSquare.length() >= 1 && enPassantSquare.length() <= 2);
    switch (enPassantSquare.length())
    {
        case 1:
            assert(enPassantSquare == "-");
            position.state.enPassantSquare = Square(-1);
            break;
        case 2:
            position.state.enPassantSquare = squareFromStr(enPassantSquare);
            break;
        default:
            throw std::runtime_error("Invalid FEN en passant square: " + enPassantSquare);
    }

    // TODO: Half move clock
    auto nHalfMoves = tokens[4];
    assert(nHalfMoves.length() == 1);

    // TODO: Full move number
    auto nFullMoves = tokens[5];
    assert(nFullMoves.length() == 1);

    return position;
}

std::string Position::toFEN() const
{
    
    std::ostringstream ss;

    // Pieces
    for (int rank=7; rank>=0; rank--)
    {
        int emptyCount = 0;
        for (int file=0; file<8; file++)
        {
            Square s = squareFromFileRank(file, rank);
            Piece p = getPiece(s);
            
            if (p.pieceType == PIECE_INVALID)
            {
                emptyCount += 1;
            }
            else
            {
                if (emptyCount > 0) { ss << std::to_string(emptyCount); }
                ss << pieceTypeToStr(p.pieceType, p.color);
                emptyCount = 0;
            }   
            
        }
        if (emptyCount > 0) { ss << std::to_string(emptyCount); }
        ss << ((rank == 0) ? " " : "/");
    }

    // Turn to move
    ss << ((m_toMove == WHITE) ? "w " : "b ");
    
    // TODO: Castling rights
    ss << "- ";

    if (state.enPassantSquare != -1)
    {
        ss << squareToStr(state.enPassantSquare) + " ";
    }
    else 
    {
        ss << "- ";
    }

    // TODO: Half move clock
    ss << "0 ";

    // TODO: Full move number
    ss << "0";

    return ss.str();
}

Bitboard Position::pieceTypeBB(Color c, PieceType pt) const
{
    return m_piecesBB[c][pt];
}

std::string Position::pretty(Bitboard b)
{
    std::string s = "    a   b   c   d   e   f   g   h\n";
    s += "  +---+---+---+---+---+---+---+---+\n";

    for (int r=7; r >= 0; r--)
    {
        s += std::to_string(r+1) + " |";
        for (int f=0; f <= 7; f++)
        {
            Square square = (r<<3) + f;
            Piece p = getPiece(square);
            auto pStr = pieceTypeToStr(p.pieceType, p.color);
            if (b & squareBB(square))
            {
                // Square is set by b
                pStr = p.pieceType == PIECE_INVALID ? "X" : "*";
            }
            s += " " + pStr + " |";

        }
        s += " " + std::to_string(r+1) + "\n";
        s += "  +---+---+---+---+---+---+---+---+\n";
    }
    s += "    a   b   c   d   e   f   g   h\n";

    return s;
}

Color Position::toMove() const
{
    return m_toMove;
}

void Position::placePiece(Piece p, Square s)
{
    Piece allreadyThere = m_board[s];
    if (allreadyThere.pieceType != PIECE_INVALID)
    {
        removePiece(s);
    }
    m_board[s] = p;
    m_piecesBB[p.color][p.pieceType] |= squareBB(s);
}

void Position::removePiece(Square s)
{
    Piece p = m_board[s];
    m_piecesBB[p.color][p.pieceType] &= ~squareBB(s);
    m_board[s] = Piece();
    // TODO: does this work?
    // m_piecesBB[p.color][p.pieceType] |= -squareBB(s);
}

void Position::makeMove(Move& m)
{
    // m_toMove = Color(m_toMove+1);
    // if (m_toMove == COLOR_N)
    // {
    //     m_toMove = Color(0);
    // }
    m.execute(this);
    m_toMove = (m_toMove == WHITE) ? BLACK : WHITE;
}

void Position::undoMove(Move& m)
{
    // m_toMove = Color(m_toMove+1);
    // if (m_toMove == COLOR_N)
    // {
    //     m_toMove = Color(0);
    // }
    
    m.undo(this);
    m_toMove = (m_toMove == WHITE) ? BLACK : WHITE;
}

Piece Position::getPiece(Square s) const
{
    return m_board[s];
}

Bitboard Position::pieces() const
{
    return pieces(WHITE) | pieces(BLACK);
}

Bitboard Position::pieces(Color c) const
{
    Bitboard pieces(0);
    for (int i=0; i < PIECE_TYPE_N; i++)
    {
        pieces |= m_piecesBB[c][i];
    }

    return pieces;
}

Bitboard Position::target(Color c) const
{
    Bitboard target;
    
    for (int tColor=0; tColor<COLOR_N; tColor++)
    {
        if (tColor != c)
        {
            for (int i=0; i < PIECE_TYPE_N; i++)
            {
                target |= m_piecesBB[tColor][i];
            }
        }
    }

    return target;
}

bool operator==(const Position &p1, const Position &p2)
{
    for (int i=0; i < 64; i++)
    {
        if (!(p1.m_board[i] == p2.m_board[i])) { return false; }
    }

    if (p1.m_toMove != p2.m_toMove) { return false; }

    // TODO: castling rights and so on... (see from fen)

    return true;
}

std::string Position::State::toString() const
{
    std::stringstream ss;
    ss << "Rule50: " << rule50count << std::endl;
    ss << "En passant square : " << enPassantSquare << std::endl;
    ss << "Captured piece: " << pieceTypeToStr(capturedPiece.pieceType, capturedPiece.color) << std::endl;
    ss << "Captured square: " << capturedSquare << std::endl;
    return ss.str();
}
