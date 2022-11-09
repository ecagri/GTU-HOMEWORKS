#ifndef DERIVEDPUZZLE
#define DERIVEDPUZZLE

#include <iostream>
#include <string>
#include <vector>
#include "BoardGame2D.h"
using namespace std;
using namespace Base;
namespace derived_puzzle{
	class EightPuzzle: public BoardGame2D{
	public:
		EightPuzzle();
		int boardScore();
		void print();
		void initialize();
		bool playAuto(mode);
		bool playUser(string);
	private:
		vector <vector<int>> puzzleBoard;
		void find_target(int, int&, int&);
		void simulate(mode);
		bool shift(int, int, mode);
		bool is_solveable();
	};
}

#endif // DERIVEDPUZZLE
