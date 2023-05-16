#include "chesshandler.h"
#include "utility.h"
#include <iostream>

int main()
{
	ChessHandler chessHandler;

	Utils::print("Welcome to ChessSupreme!");
	
	while (true)
	{
		auto validMoves = chessHandler.validMoves();
		//Utils::print(chessHandler.position().pieces().prettyBoard());
		Utils::print(chessHandler.pretty());
		
		Utils::print(colorToStr(chessHandler.toMove()) + " to move");

		std::string fromStr;
		Square from = -1;
		Move move;

		while (true) 
		{
			Utils::promptInput("From: ", fromStr);
			if (fromStr == "u")
			{
				chessHandler.undo();
				break;
			}
			else if (fromStr == "n")
			{
				if (chessHandler.validMoves().size() > 0)
				{
					chessHandler.makeMove(chessHandler.validMoves()[0]);
				}
				break;
			}
			else if (fromStr == "m")
			{
				for (Move m : chessHandler.validMoves())
				{
					std::cout << m.toString() << std::endl;
				}
				break;
			}
			else if (fromStr == "fen")
			{
				std::cout << chessHandler.position().toFEN() << std::endl;
			}
			move = Move::fromString(fromStr);
			if (move.isValid())
			{
				if (chessHandler.isValidMove(move))
				{
					break;
				}
				else
				{
					Utils::print("Invalid move!");
					continue;
				}
			}
			from = squareFromStr(fromStr);
			if (from == -1) { Utils::print("Invalid square..."); }
			else if ( !chessHandler.isValidFrom(from) ) { Utils::print("Can't move from that square!"); }
			else { break; }
		}

		if (!move.isValid() && from != -1)
		{
			Bitboard movesTo = chessHandler.validMoves(from);
			Utils::print(chessHandler.pretty(movesTo));

			std::string toStr;
			Square to;
			while (true)
			{
				Utils::promptInput("To: ", toStr);
				to = squareFromStr(toStr);
				if (to == -1) { Utils::print("Invalid square..."); break; }
				move = Move(from, to);
				if ( !chessHandler.isValidMove(move) ) { Utils::print("Can't move to that square!"); break;}
				else { break; }
			}
		}

		chessHandler.makeMove(move);
	}
}