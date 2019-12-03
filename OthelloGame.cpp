#include "OthelloGame.h"
#include "CommandLineInterface.h"
#include "BitboardHelper.h"
#include "Player.h"


Player* OthelloGame::opponent(Player* p) {
	return p == player1 ? player2 : player1;
}

OthelloGame::OthelloGame(Player* player1, Player* player2, OthelloBoard* ob) : player1(player1), player2(player2), ob(ob) {}

void OthelloGame::endGame() {
	cli::comment("Game is over.");
	running = false;
	cli::signalEndGame(ob->getNumOfPieces(BLACK));
}

void OthelloGame::start() {
	running = true;
	Player* currentPlayer = player1->color == BLACK ? player1 : player2;
	cli::comment("Board:" + ob->toString());
	while (running) {
		Move nextMove = currentPlayer->nextMove();

		if (nextMove.bi == PASS_BI_FLAG) {
			////if there were two passes in a row
			//if (currentPlayer->passedLastTurn) {
			//	cli::comment("Player " + ci::colorName[currentPlayer->color] + " passed twice in a row.");
			//	endGame();
			//}
			//else {
			//	cli::comment("Player " + ci::colorName[currentPlayer->color] + " passed.");
			//	currentPlayer->passedLastTurn = true;
			//}
		}
		else {
			currentPlayer->passedLastTurn = false;

			int numOfPieces = ob->makeMove(nextMove, currentPlayer->color);
			cli::comment("Player " + ci::colorName[currentPlayer->color] + " moved to " + bbh::biToColRowString(nextMove.bi));
			//if there's been an illegal move
			if (numOfPieces == 0) {
				cli::comment("That was an illegal move.");
				endGame();
			}
		}
		opponent(currentPlayer)->notify(nextMove);
		currentPlayer = opponent(currentPlayer);
		cli::comment("The score is now W: " + std::to_string(ob->getNumOfPieces(WHITE)) + "; B:" + std::to_string(ob->getNumOfPieces(BLACK)));
		cli::comment("Board:" + ob->toString());

	}
}
