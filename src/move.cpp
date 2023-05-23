#include "move.h"
#include "position.h"

#include <stdexcept>
#include <iostream>

std::string Move::toString()
{
     return squareToStr(from) + " -> " + squareToStr(to);
}

Move Move::fromString(std::string moveStr)
{
     if (moveStr.length() != 4)
     {
          return Move();
     }
     Square from = squareFromStr(moveStr.substr(0, 2));
     Square to = squareFromStr(moveStr.substr(2, 2));
     if (from == -1 || to == -1)
     {
          return Move();
     }
     return Move(from, to);
}

bool Move::isValid()
{
     return from != -1 && to != -1;
}

// Execute and undo
void Move::execute(Position* p)
{
     switch (moveType)
     {
          case NORMAL:
               execute<NORMAL>(p);
               p->state.enPassantSquare = Square(-1);
               break;
          case DOUBLE_PUSH:
               execute<DOUBLE_PUSH>(p);
               break;
          case EN_PASSANT:
               execute<EN_PASSANT>(p);
               p->state.enPassantSquare = Square(-1);
               break;
          default:
               throw std::runtime_error("Invalid move type!");
     }
}

void Move::undo(Position* p)
{
     // TODO: Set the enPassant square to invalid- This has to be done for any other move than DOUBLE_PUSH
     
     switch (moveType)
     {
          case NORMAL:
               undo<NORMAL>(p);
               break;
          case DOUBLE_PUSH:
               undo<DOUBLE_PUSH>(p);
               break;
          case EN_PASSANT:
               undo<EN_PASSANT>(p);
               break;
          default:
               throw std::runtime_error("Invalid move type!");
     }
}

template<>
void Move::execute<NORMAL>(Position* p)
{
     auto piece = p->getPiece(from);
     p->state.capturedPiece = p->getPiece(to);
     p->state.capturedSquare = to;
     assert(piece.pieceType != PIECE_INVALID);
     p->removePiece(from);
     p->placePiece(piece, to);
}

template<>
void Move::undo<NORMAL>(Position* p)
{
     auto piece = p->getPiece(to);
     p->removePiece(to);
     p->placePiece(p->state.capturedPiece, p->state.capturedSquare);
     p->placePiece(piece, from);
}

template <>
void Move::execute<DOUBLE_PUSH>(Position *p)
{
     p->state.enPassantSquare = (p->toMove() == WHITE) ? (from+NORTH) : (from+SOUTH);
     execute<NORMAL>(p);
}

template <>
void Move::undo<DOUBLE_PUSH>(Position *p)
{
     undo<NORMAL>(p);
}

template <>
void Move::execute<EN_PASSANT>(Position *p)
{
     Square enPSquare = p->state.enPassantSquare;
     auto piece = p->getPiece(enPSquare);
     // std::cout << "WALLA" <<  pieceTypeToStr(piece.pieceType, piece.color) << std::endl;
     // std::cout << p->pretty() << std::endl;
     // std::cout << toString() << std::endl;
     
     assert(validSquare(enPSquare));
     p->removePiece(enPSquare);
     p->removePiece(from);
     p->placePiece(Piece(PAWN, p->toMove()), to);
     // Store the enPassantSquare for potential undo()
     auto enPassantSquare = p->state.enPassantSquare;
     p->state.capturedSquare = (p->toMove() == WHITE) ? to+SOUTH : to+NORTH;
     p->state.capturedPiece = p->getPiece(p->state.capturedSquare);
     
}

template <>
void Move::undo<EN_PASSANT>(Position *p)
{
     undo<NORMAL>(p);
}
