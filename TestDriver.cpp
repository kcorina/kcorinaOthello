#include "BitboardHelper.h"
#include <cassert>
#include <string>
#include <iostream>
#include "OthelloBoardTests.h"
#include "TestDriver.h"
#include <iostream>
#include <fstream>

void test() {

	std::ofstream myfile;
	myfile.open("out.txt");
	myfile << "new test" << "\n";
	myfile.close();

	testOthelloBoard();
}
