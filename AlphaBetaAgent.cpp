#include "AlphaBetaAgent.h"
#include "OthelloBoard.h"
#include "BitboardHelper.h"
#include "CommandLineInterface.h"
#include "OthelloGame.h"

#include <float.h>

AlphaBetaAgent::AlphaBetaAgent(Color color, OthelloBoard* ob) : Player(color), ob(ob) {}



double AlphaBetaAgent::evaluateBoard(OthelloBoard* toEvaluate) {
	return (double(toEvaluate->getNumOfPieces(color)) - double(toEvaluate->getNumOfPieces(ci::opponent[color])))/ (double(toEvaluate->getNumOfPieces(color)) + double(toEvaluate->getNumOfPieces(ci::opponent[color])));
}

Move AlphaBetaAgent::alphaBetaSearch(OthelloBoard currentBoard, Move lastMove, Color player, double alpha, double beta, int depth, bool maximizing)
{
	
	if (depth == 0 || currentBoard.empty == 0 || time(NULL) >= searchLimit) {
		if (time(NULL) >= searchLimit) {
			//cli::comment("hit search limit at " + std::to_string(searchLimit));
		}
		lastMove.score = evaluateBoard(&currentBoard);
		return lastMove;
	}
	else {
		Move moves[64];
		int size;
		currentBoard.generateLegalMoves(player, moves, size);

		
		if (size == 0) {
			moves[0] = Move(OthelloGame::PASS_BI_FLAG, 0, 0, DBL_MIN);
			size = 1;
		}
		int bestMoveIndex = 0;
		if (maximizing) {
			
			for (int i = 0; i < size; i++) {
				OthelloBoard nextBoard = currentBoard;
				nextBoard.makeMove(moves[i], player);
				moves[i].score = alphaBetaSearch(nextBoard, moves[i], ci::opponent[player], alpha, beta, depth - 1, false).score;

				if (moves[bestMoveIndex].score < moves[i].score) {
					bestMoveIndex = i;
				}
				if (moves[bestMoveIndex].score >= beta)
					break;
				alpha = std::max(alpha, moves[bestMoveIndex].score);
			}
		}
		else {
			
			for (int i = 0; i < size; i++) {
				OthelloBoard nextBoard = currentBoard;
				nextBoard.makeMove(moves[i], player);
				moves[i].score = alphaBetaSearch(nextBoard, moves[i], ci::opponent[player], alpha, beta, depth - 1, true).score;
				if (moves[bestMoveIndex].score > moves[i].score) {
					bestMoveIndex = i;
				}
				if (moves[bestMoveIndex].score <= alpha)
					break;
				beta = std::min(beta, moves[bestMoveIndex].score);
			}
		}
		return moves[bestMoveIndex];
	}
}
Move AlphaBetaAgent::alphaBetaSearch() {
	//cli::comment("starting ab search.");
	
	searchLimit = time(NULL) + searchDuration[moveNum];
	
	///cli::comment("start time " + std::to_string(time(NULL)));
	//cli::comment("end time " + std::to_string(searchLimit));
	//cli::comment("search duration " + std::to_string(searchDuration[moveNum]));

	moveNum++;

	OthelloBoard toSearch(*ob);
	return alphaBetaSearch(toSearch, Move(), color, DBL_MIN, DBL_MAX, this->maxDepth, true);
}



//add time-tracking to Agent, not Game class. 
//ideas:
//-maybe use notify() to track the amount of time the opponent takes
//-...or extracty"notify" out of Player and into a "listener" class so only CLP needs to implement it
//-time spent searching should be a function of the number of moves into the game it is
//-frontier strategy - consider potential mobility and stability of disk
//-stoner move - corner stealing
//-ch. 4 alphabeta & min/max functions - check out the java implementation on moodle (slightly modified)
//-lookup tables - generate at a compile time, search early moves
//-use multithreading to batch searches AND search while opponent is "thinking"


void AlphaBetaAgent::notify(Move makeMove)
{
}

Move AlphaBetaAgent::nextMove() {
	return alphaBetaSearch();
}

void AlphaBetaAgent::setDepth(int maxDepth) {
	this->maxDepth = maxDepth;
}

void AlphaBetaAgent::setMoveNum(int move)
{
	this->moveNum = move;
}
