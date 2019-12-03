#pragma once
#include "Player.h"
#include "OthelloBoard.h"

class HighestFlipScoreAgent : public Player {
private:
	OthelloBoard* ob;
public:
	//TODO abstract ob constructor to Player
	HighestFlipScoreAgent(Color color, OthelloBoard* ob);
	void notify(Move makeMove);
	Move nextMove();
};