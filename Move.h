#pragma once
#include <cstdint>

struct Move {
	int bi = 0;
	int numOfPieces = 0;
	std::uint64_t toFlip = 0;
	double score = 0;
	Move();
	Move(int bi, int numOfPieces, std::uint64_t toFlip, double score);
	static Move noScoreMoveFromXY(int x, int y, int numOfPieces, uint64_t toFlip = 0);
};

