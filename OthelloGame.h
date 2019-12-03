#pragma once
#include "Player.h"
#include "OthelloBoard.h"

class OthelloGame {
private:
	Player* player1;
	Player* player2;
	OthelloBoard* ob;
	bool running;
public:
	static const int PASS_BI_FLAG = -1;
	Player* opponent(Player* p);
	OthelloGame(Player* player1, Player* player2, OthelloBoard* ob);
	void start();
	void endGame();

};