#include "Gametypes.h"


#include "TestDriver.h"
#include "OthelloBoard.h"
#include "CommandLineInterface.h"
#include "AlphaBetaAgent.h"
#include "HighestFlipScoreAgent.h"
#include "Player.h"
#include "OthelloGame.h"
#include "CommandLinePlayer.h"
#include "Gametypes.h"

void startAlphaBetaAgentAgentVersusCommandLineOpponentGame() {

	OthelloBoard* ob = new OthelloBoard();
	Color agentColor = cli::getInitalizerColor();
	Player* agent = new AlphaBetaAgent(agentColor, ob);
	Player* commandLinePlayer = new CommandLinePlayer(ci::opponent[agentColor], ob);

	OthelloGame og = OthelloGame(agent, commandLinePlayer, ob);
	cli::signalReady(agentColor);

	og.start();

	delete(agent);
	delete(commandLinePlayer);
	delete(ob);

}

void startAlphaBetaAgentVersusAlphaBetaAgentGame() {
	OthelloBoard* ob = new OthelloBoard();
	AlphaBetaAgent* agent1 = new AlphaBetaAgent(BLACK, ob);
	AlphaBetaAgent* agent2 = new AlphaBetaAgent(WHITE, ob);
	agent1->setDepth(100);
	agent2->setDepth(100);
	OthelloGame og = OthelloGame(agent1, agent2, ob);

	og.start();

	delete(agent1);
	delete(agent2);
	delete(ob);
}

void startAlphaBetaAgentVersusHighestFlipScoreAgentGame() {
	OthelloBoard* ob = new OthelloBoard();
	Player* agent1 = new AlphaBetaAgent(BLACK, ob);
	Player* agent2 = new HighestFlipScoreAgent(WHITE, ob);

	OthelloGame og = OthelloGame(agent1, agent2, ob);

	og.start();

	delete(agent1);
	delete(agent2);
	delete(ob);
}
