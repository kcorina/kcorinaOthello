#pragma once
#include <cstdint>
#include <string>
#include "Color.h"
#include <map>
#include <algorithm> 
#include "Move.h"
class OthelloBoard {
private:
	int numOfPieces[2] = { 0,0 };

public:
	int getNumOfPieces(Color player);
	
	std::uint64_t pieces[2] = { 0,0 };
	std::uint64_t empty = 18446744073709551615;

	int makeMove(Move move, Color player);
	int makeMove(int pos, Color player);
	int makeMove(int x, int y, Color player);

	void place(int pos, Color c);
	void place(int x, int y, Color player);
	void flip(std::uint64_t, int flipCount, Color player);

	Move getFlips(int toPlace, Color player);

	void generateLegalMoves(Color player, Move (&moves)[64], int& size);
	std::uint64_t getOpenEdges(Color color);

	OthelloBoard();
	OthelloBoard(std::string richString);
	OthelloBoard(const OthelloBoard& ob);
	OthelloBoard(std::uint64_t black, std::uint64_t white);

	std::string toString(bool A1Origin = false);
	
};