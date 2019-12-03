#define OPEN_EDGES(p) empty & (p << 8 | p >> 8 | (bbh::NOT_RIGHT_EDGE& (p << 1 | p >> 7 | p << 9)) | (bbh::NOT_LEFT_EDGE & (p >> 1 | p << 7 | p >> 9)));

#include "Color.h"
#include "OthelloBoard.h"
#include "BitboardHelper.h"
#include <iostream>
#include "CommandLineInterface.h"

#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>

OthelloBoard::OthelloBoard() {
	place(4, 3, BLACK);
	place(3, 4, BLACK);
	place(3, 3, WHITE);
	place(4, 4, WHITE);
}

OthelloBoard::OthelloBoard(std::string richString)
{
	std::replace(richString.begin(), richString.end(), '.', '0');
	std::string blackString = richString;
	std::replace(blackString.begin(), blackString.end(), 'B', '1');
	std::replace(blackString.begin(), blackString.end(), 'W', '0');
	std::string whiteString = richString;
	std::replace(whiteString.begin(), whiteString.end(), 'W', '1');
	std::replace(whiteString.begin(), whiteString.end(), 'B', '0');

	
	pieces[BLACK] = bbh::bbFromBinaryString(blackString);
	pieces[WHITE] = bbh::bbFromBinaryString(whiteString);
	//numOfPieces[BLACK] = __builtin_popcountl(pieces[BLACK] >> 32) + __builtin_popcountl(pieces[BLACK]);
	//numOfPieces[WHITE] = __builtin_popcountl(pieces[WHITE] >> 32) + __builtin_popcountl(pieces[WHITE]);
	empty = ~pieces[BLACK] & ~pieces[WHITE];

	
}

OthelloBoard::OthelloBoard(const OthelloBoard& ob) {

	std::copy(std::begin(ob.numOfPieces), std::end(ob.numOfPieces), std::begin(numOfPieces));
	std::copy(std::begin(ob.pieces), std::end(ob.pieces), std::begin(pieces));
	empty = ob.empty;

}

OthelloBoard::OthelloBoard(std::uint64_t black, std::uint64_t white) {
	pieces[BLACK] = black;
	pieces[WHITE] = white;
	empty = ~black & ~white;
}

std::string OthelloBoard::toString(bool A1Origin)
{
	char s[3] = { 'B','W','.' };
	std::uint64_t b[3] = { pieces[BLACK], pieces[WHITE], empty };
	return bbh::bitBoardToString(b, 3, true, "BW.");
}

//modify OB to accepts moves instead of x,y
//(currently Agent and OB both perform the same, slow cast for the same result on a move)

int OthelloBoard::getNumOfPieces(Color player)
{
	return numOfPieces[player];
}

int OthelloBoard::makeMove(Move move, Color player) {
	
	

	if (move.numOfPieces != 0) {
		flip(move.toFlip, move.numOfPieces, player);
		place(move.bi, player);
	}




	

	return move.numOfPieces;
}

int OthelloBoard::makeMove(int bi, Color player)
{
	Move move = getFlips(bi, player);
	if (move.numOfPieces != 0) {
		flip(move.toFlip, move.numOfPieces, player);
		place(move.bi, player);
	}

	return move.numOfPieces;
}

int OthelloBoard::makeMove(int x, int y, Color c)
{
	return makeMove(bbh::XY_TO_BI[x][y], c);
}

void OthelloBoard::place(int pos, Color c)
{
	pieces[c] |= bbh::ONE << pos;
	empty &= ~(bbh::ONE << pos);
	numOfPieces[c] += 1;

}

void OthelloBoard::place(int x, int y, Color c)
{
	place(bbh::XY_TO_BI[x][y], c);
}

void OthelloBoard::flip(std::uint64_t toFlip, int flipCount, Color player)
{
	pieces[player] |= toFlip;
	pieces[ci::opponent[player]] &= ~toFlip;

	numOfPieces[player] += flipCount;
	numOfPieces[ci::opponent[player]] -= flipCount;

}

//TODO: 
//10/8  - get it working
//10/10 - OPTIMIZE

//possible routes: lookup tables, bit-twiddling
Move OthelloBoard::getFlips(int bi, Color color) {
	Move result(bi,0,0,0);
	int x = bbh::BI_TO_XY[bi][0];
	int y = bbh::BI_TO_XY[bi][1];

	//cli::comment("checking (" + std::to_string(x) + "," + std::to_string(y) + ")");
	//cli::comment("on OB:\n " + toString());
	//cli::comment("for color " + ci::colorName[color]);


	for (int dir = 0; dir < 8; dir++) {
		
		//cli::comment("DIR: " + std::to_string(dir));

		int xMod = bbh::DIRECTION_XY_MOD[dir][0];
		int yMod = bbh::DIRECTION_XY_MOD[dir][1];
		
		//lookup table candidate?
		//int maxCast = ?;
		
		std::uint64_t cast = 0;
		std::uint64_t lastCast = 0;
		//converts to x y to check if within bounds
		//slow
		//deal with later
		for (int j = 1; 
			(x + j * xMod) <  8 && 
			(x + j * xMod) >= 0 && 
			(y + j * yMod) <  8 && 
			(y + j * yMod) >= 0
			; j++) {
			
			cast |= bbh::ONE << (bi + j * bbh::DIRECTION_BI_MOD[dir]);
			//cli::comment("cast:");
			//cli::comment(bbh::bitBoardToString(&cast));

			if (cast & empty) {
				//cli::comment("hit empty! breaking");

				break;
			}
			
			if (cast & pieces[color]) {
				result.numOfPieces += j - 1;
				result.toFlip |= lastCast;
				//cli::comment("hit same color! score: " + std::to_string(j-1));
				break;
			}

			lastCast = cast;
		}
		//cli::comment("max cast reached");

	}
	return result;
}

void OthelloBoard::generateLegalMoves(Color player, Move(&moves)[64], int &size) {
	Color opponent = ci::opponent[player];

	std::uint64_t opponentEdges = getOpenEdges(opponent);



	/*
	size = 0;
	int i = 0;
	int nextOn = 0;
	int pos = 64;

	while ((nextOn = __builtin_clzll(opponentEdges) + 1) ^ 64) {
		pos -= nextOn;
		Move result = getFlips(pos, player);
		if (result.numOfPieces != 0) {
			moves[size] = result;
			size += 1;
		}
		opponentEdges <<= nextOn;
		i++;
	}*/

	size = 0;
	
	int nextOn;
	int pos = 64;
		
	for (int i = 63; i >= 0; i--) {
		if ((bbh::ONE << i) & opponentEdges) {
			Move result = getFlips(i, player);
			if (result.numOfPieces != 0) {
				moves[size] = result;
				size += 1;
			}
		}
	}

}

//TODO: MACRO?
std::uint64_t OthelloBoard::getOpenEdges(Color color) {
	std::uint64_t p = pieces[color];
	/*return empty & (p << 8 | p >> 8 |
		(bbh::NOT_RIGHT_EDGE & (p << 1 | p >> 7 | p << 9)) |
		(bbh::NOT_LEFT_EDGE & (p >> 1 | p << 7 | p >> 9))
		);*/
	return OPEN_EDGES(p);
}
