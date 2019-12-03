#include "Move.h"
#include "BitboardHelper.h"

Move::Move()
{
}

Move::Move(int bi, int numOfPieces, std::uint64_t toFlip, double score) : bi(bi), numOfPieces(numOfPieces), toFlip(toFlip), score(score) {
}

Move Move::noScoreMoveFromXY(int x, int y, int numOfPieces, uint64_t toFlip)
{
	return Move(bbh::XY_TO_BI[x][y], numOfPieces, toFlip, 0);
}
