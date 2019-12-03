#include "HighestFlipScoreAgent.h"
#include "OthelloGame.h"
#include <float.h>
HighestFlipScoreAgent::HighestFlipScoreAgent(Color color, OthelloBoard* ob) : Player(color), ob(ob) {}

void HighestFlipScoreAgent::notify(Move makeMove)
{
}

Move HighestFlipScoreAgent::nextMove()
{
	Move moves[64];
	int size;

	ob->generateLegalMoves(color, moves, size);

	if (size == 0) {
		moves[0] = Move(OthelloGame::PASS_BI_FLAG, 0, 0, DBL_MIN);
		size = 1;
	}

	Move bestMove = moves[0];

	for (int i = 0; i < size; i++) {
		if (moves[i].numOfPieces > bestMove.numOfPieces) {
			bestMove = moves[i];
		}
	}
	return bestMove;
}
