#include "utility.h"
#include "move.h"
#include "piece.h"

#include "bitboard.h"

#include <iostream>
#include <bitset>
#include <math.h>

PieceType choosePieceType()
{
  std::string pieceStr;
  std::cout << "Choose piece: ";
  std::cin >> pieceStr;
  PieceType pt;
  switch (std::stoi(pieceStr))
  {
    case KING:
      	pt = KING;
      	break;
    case KNIGHT:
      	pt = KNIGHT;
      	break;
    case BISHOP:
      	pt = BISHOP;
      	break;
    case ROOK:
      	pt = ROOK;
      	break;
    case QUEEN:
      	pt = QUEEN;
      	break;
    case PAWN:
		pt = PAWN;
		break;
    default:
      pt = KING;
  }

  return pt;
}

int main() {
  std::cout << "Welcome to the ChessSupreme!" << std::endl;

  PieceType pt = choosePieceType();
  while (true)
  {
    Color color = WHITE;

    std::string squareStr;
    Square square;
    std::cout << "Square: ";
    std::cin >> squareStr;
    if (squareStr == "q")
    {
      break;
    }
    else if (squareStr == "p")
    {
      pt = choosePieceType();
    }
    else
    {
      try
      {
        square = std::stoi(squareStr.c_str(), nullptr, 10);
      }
      catch (std::exception)
      {
        std::cout << "Something went wrong..." << std::endl;  
      }
    }

    Bitboard moves;
    switch(pt)
    {
    case KING:
      moves = pseduoMovesBB<KING>(color, square);
      break;
    case KNIGHT:
      moves = pseduoMovesBB<KNIGHT>(color, square);
      break;    
    case BISHOP:
      moves = pseduoMovesBB<BISHOP>(color, square);
      break;
    case ROOK:
      moves = pseduoMovesBB<ROOK>(color, square);
      break;
    case QUEEN:
      moves = pseduoMovesBB<QUEEN>(color, square);
      break;
	case PAWN:
      moves = pseduoMovesBB<PAWN>(color, square);
      break;
    default:
      std::cout << "Invalid piece...";
    }

    std::cout << "Pseudo moves for piece " + pieceTypeToStr(pt, WHITE) + ":\n";
    std::cout << moves.prettyBoard() << std::endl;
  }
  return 0;
}