#include "OthelloBoard.h"
#include "OthelloBoardTests.h"
#include <cassert>
#include "BitboardHelper.h"
#include <iostream>
#include "CommandLineInterface.h"
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <iterator>

void compareMoveResults(Move actualMoves[], int actualSize, Move expectedMoves[], int expectedSize) {



	/*cli::comment("expected size\t" + std::to_string(expectedSize));
	cli::comment("actual size\t" + std::to_string(actualSize));*/

	assert(actualSize == expectedSize);

	for (int i = 0; i < expectedSize; i++) {
		Move a = actualMoves[i];
		Move e = expectedMoves[i];

		/*cli::comment("expected move\t" + std::to_string(bbh::BI_TO_XY[e.bi][0]) + ",\t" + std::to_string(bbh::BI_TO_XY[e.bi][1]) + "\ts:\t score:" + std::to_string(e.numOfPieces));
		cli::comment("actual move\t" + std::to_string(bbh::BI_TO_XY[a.bi][0]) + ",\t" + std::to_string(bbh::BI_TO_XY[a.bi][1]) + "\ts:\t score:" + std::to_string(a.numOfPieces));
		*/
		/*cli::comment("expected move\t" + bbh::biToColRowString(e.bi) + "\ts:\t score:" + std::to_string(e.numOfPieces));
		cli::comment("actual move\t" + bbh::biToColRowString(e.bi) + + "\ts:\t score:" + std::to_string(a.numOfPieces));*/

		assert(a.bi == e.bi);
		assert(a.numOfPieces == e.numOfPieces);
		//i++;
	}
}

void testOthelloBoardConstructors() {
	cli::comment("Testing OthelloBoard constructors...");
	OthelloBoard ob = OthelloBoard();

	assert(ob.pieces[WHITE] == bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00000000"
	));
	assert(ob.pieces[BLACK] == bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00001000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000000"
	));

	assert(ob.empty == bbh::bbFromBinaryString(
		"11111111"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111111"
	));
	
	OthelloBoard* obPoint = new OthelloBoard(
		"B...BBB."\
		".BBBBB.W"\
		"WWBBWWW."\
		".WBBBW.W"\
		".BWBWWB."\
		"...W.W.B"\
		".....W.."\
		".....W..");

	ob = OthelloBoard(*obPoint);

	assert(ob.pieces[BLACK] == obPoint->pieces[BLACK]);
	assert(ob.pieces[WHITE] == obPoint->pieces[WHITE]);
	assert(ob.empty == obPoint->empty);
	assert(ob.getNumOfPieces(WHITE) == obPoint->getNumOfPieces(WHITE));
	assert(ob.getNumOfPieces(BLACK) == obPoint->getNumOfPieces(BLACK));
	assert(ob.getNumOfPieces(BLACK) == obPoint->getNumOfPieces(BLACK));

	ob.makeMove(6, 1, BLACK);
	assert(ob.pieces[BLACK] != obPoint->pieces[BLACK]);


	cli::comment("OthellBoard constructor tests passed.");
}
void testPlace() {

	cli::comment("Testing OthelloBoard::place(...) function...");
	OthelloBoard ob = OthelloBoard();
	ob.place(0, 0, BLACK);
	assert(ob.empty == bbh::bbFromBinaryString(
		"01111111"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111111"
	));


	assert(ob.pieces[BLACK] == bbh::bbFromBinaryString(
		"10000000"\
		"00000000"\
		"00000000"\
		"00001000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000000"
	));

	ob.place(7, 7, BLACK);
	assert(ob.empty == bbh::bbFromBinaryString(
		"01111111"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111110"
	));
	assert(ob.pieces[BLACK] == bbh::bbFromBinaryString(
		"10000000"\
		"00000000"\
		"00000000"\
		"00001000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000001"
	));

	ob.place(7, 0, WHITE);
	assert(ob.empty == bbh::bbFromBinaryString(
		"01111110"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111110"
	));
	assert(ob.pieces[WHITE] == bbh::bbFromBinaryString(
		"00000001"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00000000"
	));

	ob.place(0, 7, WHITE);
	assert(ob.empty == bbh::bbFromBinaryString(
		"01111110"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"01111110"
	));
	assert(ob.pieces[WHITE] == bbh::bbFromBinaryString(
		"00000001"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"10000000"
	));

	ob.place(6, 6, WHITE);
	assert(ob.empty == bbh::bbFromBinaryString(
		"01111110"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111101"\
		"01111110"
	));
	assert(ob.pieces[WHITE] == bbh::bbFromBinaryString(
		"00000001"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000010"\
		"10000000"
	));

	cli::comment("OthelloBoard::place(...) function tests passed.");


}
void testFlip() {
	cli::comment("Testing OthelloBoard::flip(...) function...");
	OthelloBoard ob = OthelloBoard(
		bbh::bbFromBinaryString(
			"00000000"\
			"00001000"\
			"00001000"\
			"00001100"\
			"00001000"\
			"00100100"\
			"00110010"\
			"00000000"
		),
		bbh::bbFromBinaryString(
			"00000000"\
			"00000000"\
			"00000000"\
			"00000010"\
			"00000000"\
			"00000000"\
			"00000000"\
			"00000001"
		)
	);

	ob.flip(bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00001100"\
		"00001000"\
		"00000100"\
		"00000010"\
		"00000000")
		, 7, WHITE);

	assert(ob.pieces[WHITE] == bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00001110"\
		"00001000"\
		"00000100"\
		"00000010"\
		"00000001")
	);
	assert(ob.pieces[BLACK] == bbh::bbFromBinaryString(
		"00000000"\
		"00001000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00100000"\
		"00110000"\
		"00000000"
	));

	cli::comment("OthelloBoard::flip(...) function tests passed.") ;
}
void testMove() {
	cli::comment("Testing OthelloBoard::move(...) function...");
	OthelloBoard ob = OthelloBoard(
		bbh::bbFromBinaryString(
			"00000000"\
			"00001000"\
			"00001000"\
			"00001100"\
			"00001000"\
			"00100100"\
			"00110010"\
			"00000000"
		),
		bbh::bbFromBinaryString(
			"00000000"\
			"00000000"\
			"00000000"\
			"00000010"\
			"00000000"\
			"00000000"\
			"00000000"\
			"00000001"
		)
	);

	assert(ob.makeMove(3, 3, WHITE) == 5);

	assert(ob.empty == bbh::bbFromBinaryString(
		"11111111"\
		"11110111"\
		"11110111"\
		"11100001"\
		"11110111"\
		"11011011"\
		"11001101"\
		"11111110"
	));

	assert(ob.pieces[WHITE] == bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00011110"\
		"00001000"\
		"00000100"\
		"00000010"\
		"00000001")
	);
	assert(ob.pieces[BLACK] == bbh::bbFromBinaryString(
		"00000000"\
		"00001000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00100000"\
		"00110000"\
		"00000000"
	));

	

	cli::comment("OthelloBoard::move(...) function tests passed.");

}
void testEdgeGen() {
	cli::comment("Testing OthelloBoard::getOpenEdges(...) function...");

	OthelloBoard ob = OthelloBoard(bbh::bbFromBinaryString(
		"00000000"\
		"00100000"\
		"00010000"\
		"00000000"\
		"00110000"\
		"01000000"\
		"00000000"\
		"00000000"
	), bbh::bbFromBinaryString(
		"00000000"\
		"00010000"\
		"00000000"\
		"00011100"\
		"00001100"\
		"00000100"\
		"00000000"\
		"00000000"
	));
	assert(ob.getOpenEdges(WHITE) == bbh::bbFromBinaryString(
		"00111000"\
		"00001000"\
		"00101110"\
		"00100010"\
		"00000010"\
		"00011010"\
		"00001110"\
		"00000000"));
	

	ob = OthelloBoard(bbh::bbFromBinaryString(
		"10000001"\
		"00011000"\
		"00100000"\
		"10000000"\
		"10010000"\
		"00100000"\
		"01000000"\
		"10000001"
	), bbh::bbFromBinaryString(
		"01000000"\
		"00100000"\
		"00000000"\
		"00011100"\
		"00000000"\
		"00000000"\
		"10000010"\
		"00000000"
	));
	std::uint64_t edgesActual = ob.getOpenEdges(BLACK);
	std::uint64_t edgesExpected = bbh::bbFromBinaryString(
		"00111110"\
		"11000111"\
		"11011100"\
		"01100000"\
		"01101000"\
		"11011000"\
		"00110001"\
		"01100010");

	assert(ob.getOpenEdges(BLACK) == bbh::bbFromBinaryString(
		"00111110"\
		"11000111"\
		"11011100"\
		"01100000"\
		"01101000"\
		"11011000"\
		"00110001"\
		"01100010"));
	cli::comment("OthelloBoard::getOpenEdges(...) tests passed.");
	
}



void testBBtoIndices() {
	cli::comment("Testing BitBoardToIndices algorithm...");

	std::uint64_t bb = bbh::bbFromBinaryString(
		"00000000"\
		"00001000"\
		"00001000"\
		"00001100"\
		"00001000"\
		"00100100"\
		"00110010"\
		"00000000"
	);

	
	int expected[10][2] = { {6,6},{3,6},{2,6},{5,5},{2,5},{4,4},{5,3},{4,3},{4,2},{4,1} };
	
	int i = 0;
	int nextOn = 0;
	int pos = 64;


	while ((nextOn = __builtin_clzll(bb) + 1) ^ 64) {
		pos -= nextOn;

		
		
		//cli::comment("expected\t" + std::to_string(expected[i][0]) + ",\t" + std::to_string(expected[i][1]));
		//cli::comment("actual\t" + std::to_string(bbh::BI_TO_XY[pos][0]) + ",\t" + std::to_string(bbh::BI_TO_XY[pos][1]));

		
		assert(bbh::BI_TO_XY[pos][0] == expected[i][0]);
		assert(bbh::BI_TO_XY[pos][1] == expected[i][1]);

		bb <<= nextOn;
		i++;
	}	


	bb = bbh::bbFromBinaryString(
		"11111111"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"11111111"
	);


	int expected1[16][2] = { {7,7},{6,7},{5,7},{4,7},{3,7},{2,7},{1,7},{0,7},{7,0},{6,0},{5,0},{4,0},{3,0},{2,0},{1,0},{0,0} };

	i = 0;
	nextOn = 0;
	pos = 64;

	//cli::comment("T2!");

	while ((nextOn = __builtin_clzll(bb) + 1) && bb) {
		pos -= nextOn;

		//cli::comment("expected\t" + std::to_string(expected1[i][0]) + ",\t" + std::to_string(expected1[i][1]));
		//cli::comment("actual\t" + std::to_string(bbh::BI_TO_XY[pos][0]) + ",\t" + std::to_string(bbh::BI_TO_XY[pos][1]));
		assert(bbh::BI_TO_XY[pos][0] == expected1[i][0]);
		assert(bbh::BI_TO_XY[pos][1] == expected1[i][1]);

		bb <<= nextOn;
		i++;
	}



	bb = bbh::bbFromBinaryString(
		"00010100"\
		"11101000"\
		"00010110"\
		"00000010"\
		"00000001"\
		"10010000"\
		"00010100"\
		"11110000"
	);


	int expected2[19][2] = { {3,7},{2,7},{1,7},{0,7},{5,6},{3,6},{3,5},{0,5},{7,4},{6,3},{6,2},{5,2},{3,2},{4,1},{2,1},{1,1},{0,1}, {5,0}, {3,0}};

	i = 0;
	nextOn = 0;
	pos = 64;

	//cli::comment("T2!");

	while ((nextOn = __builtin_clzll(bb) + 1) && bb) {
		pos -= nextOn;

		cli::comment("expected move\t" + bbh::biToColRowString(bbh::XY_TO_BI[expected2[i][0]][expected2[i][1]]));
		cli::comment("actual move\t" + bbh::biToColRowString(pos));
		
		assert(bbh::BI_TO_XY[pos][0] == expected2[i][0]);
		assert(bbh::BI_TO_XY[pos][1] == expected2[i][1]);

		bb <<= nextOn;
		i++;
	}


	bb = bbh::bbFromBinaryString(
		"10000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
	);


	int expected3[1][2] = { {0,0} };

	i = 0;
	nextOn = 0;
	pos = 64;

	//cli::comment("T2!");

	while ((nextOn = __builtin_clzll(bb) + 1) ^ 64) {
		pos -= nextOn;
		cli::comment("pos:\t" + bbh::biToColRowString(pos));

		cli::comment("expected move\t" + bbh::biToColRowString(bbh::XY_TO_BI[expected3[i][0]][expected3[i][1]]));
		cli::comment("actual move\t" + bbh::biToColRowString(pos));

		assert(bbh::BI_TO_XY[pos][0] == expected3[i][0]);
		assert(bbh::BI_TO_XY[pos][1] == expected3[i][1]);
		cli::comment("bb before shift:\t" + bbh::bitBoardToString(&bb));
		cli::comment("next on = :\t" + std::to_string(nextOn));

		bb <<= nextOn;
		cli::comment("bb after shift:\t" + bbh::bitBoardToString(&bb));

		i++;
	}


	cli::comment("BitBoardToIndices algorithm tests passed.");

}

void testMoveGen() {
	cli::comment("Testing OthelloBoard::generateLegalMoves(...) function...");

	OthelloBoard ob = OthelloBoard();
	//cli::comment(ob.toString());


	Move moves[64];
	int size;
	
	ob.generateLegalMoves(BLACK, moves, size);
	

	Move expected1[] = {
		Move::noScoreMoveFromXY(4,5,1),
		Move::noScoreMoveFromXY(5,4,1),
		Move::noScoreMoveFromXY(2,3,1),
		Move::noScoreMoveFromXY(3,2,1),
	};

	compareMoveResults(moves, size, expected1,4);

	ob = OthelloBoard(
		"........"\
		"..BW...."\
		"...B...."\
		"...WWW.."\
		"..BBWW.."\
		".B...W.."\
		"........"\
		"........");
	
	Move expected2[6] = {
		Move::noScoreMoveFromXY(6,5,2),
		Move::noScoreMoveFromXY(6,4,2),
		Move::noScoreMoveFromXY(5,2,1),
		Move::noScoreMoveFromXY(4,2,1),
		Move::noScoreMoveFromXY(4,1,1),
		Move::noScoreMoveFromXY(3,0,1),
		
	};


	ob.generateLegalMoves(BLACK, moves, size);
	
	compareMoveResults(moves, size, expected2, 6);
	ob = OthelloBoard(
		"........"\
		"...B...."\
		"..B.B..."\
		".BBBWB.."\
		".BBBBW.."\
		".....BWB"\
		"......WW"\
		"......WB");

	Move expected3[10] = {
		Move::noScoreMoveFromXY(5,6,1),
		Move::noScoreMoveFromXY(4,5,2),
		Move::noScoreMoveFromXY(2,5,1),
		Move::noScoreMoveFromXY(7,4,1),
		Move::noScoreMoveFromXY(0,4,4),
		Move::noScoreMoveFromXY(6,3,1),
		Move::noScoreMoveFromXY(0,3,3),
		Move::noScoreMoveFromXY(5,2,1),
		Move::noScoreMoveFromXY(4,1,1),
		Move::noScoreMoveFromXY(1,1,4),
	};

	ob.generateLegalMoves(WHITE, moves, size);
	
	
	compareMoveResults(moves, size, expected3, 10);
	ob = OthelloBoard(
		"..B.W..."\
		"...W.B.."\
		"WBW.B..."\
		"WWBBBW.B"\
		"WWWBBWB."\
		".WW.BBBW"\
		"BWW.B.WB"\
		"....BWWW");
	
	/*cli::comment("board is\t" + ob.toString());
	cli::comment("finding moves for black");*/

	Move expected4[13] = {
		Move::noScoreMoveFromXY(2,7,3),
		Move::noScoreMoveFromXY(1,7,4),
		Move::noScoreMoveFromXY(0,7,2),
		Move::noScoreMoveFromXY(5,6,1),
		Move::noScoreMoveFromXY(3,6,2),
		Move::noScoreMoveFromXY(0,5,1),
		Move::noScoreMoveFromXY(7,4,1),
		Move::noScoreMoveFromXY(6,3,2),
		Move::noScoreMoveFromXY(6,2,1),
		Move::noScoreMoveFromXY(5,2,2),
		Move::noScoreMoveFromXY(3,2,1),
		Move::noScoreMoveFromXY(2,1,1),
		Move::noScoreMoveFromXY(1,1,1),


	};


	ob.generateLegalMoves(BLACK, moves, size);
	compareMoveResults(moves, size, expected4, 13);


	/*auto ob = OthelloBoard(
		"B...BBB."\
		".BBBBB.W"\
		"WWBBWWW."\
		".WBBBW.W"\
		".BWBWWB."\
		"...W.W.B"\
		".....W.."\
		".....W..");

	ob.generateLegalMoves(BLACK, moves, size);

	for (int i = 0; i < size; i++) {
		Move a = moves[i];
		

	}*/


	cli::comment("OthelloBoard::generateLegalMoves(...) function tests passed.");

}
void testFlipGen() {
	cli::comment("Testing OthelloBoard::getFlips(...) function...");
	OthelloBoard ob = OthelloBoard();
	auto m = ob.getFlips(bbh::XY_TO_BI[2][3], BLACK);
	assert(m.numOfPieces == 1);
	assert(m.toFlip == bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"));
	
	

	ob = OthelloBoard(bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"01100000"\
		"00111001"\
		"00000000"\
		"00010000"\
		"00000000"\
		"00000000"
	), bbh::bbFromBinaryString(
		"01000000"\
		"00010000"\
		"00000000"\
		"00000100"\
		"01000100"\
		"00000000"\
		"00000000"\
		"00000000"
	));
	m = ob.getFlips(bbh::XY_TO_BI[1][3], WHITE);
	assert(m.numOfPieces == 4);
	assert(m.toFlip == bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00100000"\
		"00111000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"));
	



	cli::comment("OthelloBoard::getFlips(...) function tests passed.");

}

#include "Player.h"
#include "OthelloGame.h"
#include "AlphaBetaAgent.h"

#include "CommandLinePlayer.h"
void testAlphaBetaAgent() {

	OthelloBoard* ob = new OthelloBoard(
		"B...BBB."\
		".BBBBB.W"\
		"WWBBWWW."\
		".WBBBW.W"\
		".BWBWWB."\
		"...W.W.B"\
		".....W.."\
		".....W..");
	Color agentColor = cli::getInitalizerColor();
	AlphaBetaAgent* agent = new AlphaBetaAgent(agentColor, ob);
	Player* commandLinePlayer = new CommandLinePlayer(ci::opponent[agentColor], ob);
	agent->setMoveNum(14);

	OthelloGame og = OthelloGame(agent, commandLinePlayer, ob);
	cli::signalReady(agentColor);

	og.start();

	delete(agent);
	delete(commandLinePlayer);
	delete(ob);

}

bool testOthelloBoard() {
	cli::comment("Othello version 2.3");
	//testBBtoIndices();
	//testAlphaBetaAgent();
	testOthelloBoardConstructors();
	testPlace();
	testFlip();
	testEdgeGen();
	testFlipGen();
	testMoveGen();
	testMove();
	
	return true;
}