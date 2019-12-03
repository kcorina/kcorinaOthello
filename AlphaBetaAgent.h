#pragma once
#include "Player.h"
#include "OthelloBoard.h"
#include <time.h>
class AlphaBetaAgent : public Player {
private:
	OthelloBoard* ob;
	int maxDepth = 100;
	time_t searchLimit;
	int moveNum = 0;
	double searchDuration[36] = { 5,5,5,5,15,15,15,15,15,15,15,30,30,30,30,30,25,25,25,25,25,25,25,25,25,7,7,7,7,7,7,7,7,2,2,2 };

public:
	//TODO abstract ob constructor to Player
	AlphaBetaAgent(Color color, OthelloBoard* ob);
	void notify(Move makeMove);
	Move nextMove();
	void setDepth(int maxDepth);
	void setMoveNum(int move);
	double evaluateBoard(OthelloBoard* toEvaluate);
	Move alphaBetaSearch(OthelloBoard currentBoard, Move lastMove, Color player, double alpha, double beta, int depth, bool maximizing);
	Move alphaBetaSearch();

};