#include <iostream>
#include <string>
#include <vector>
#ifndef KLOTSKIPUZ
#define KLOTSKIPUZ

#include "BoardGame2D.h"
using namespace std;
using namespace Base;

namespace derived_klotski{
	class Klotski: public BoardGame2D{
	public:
		Klotski();
		int boardScore();
		void print();
		void initialize();
		bool playAuto(mode);
		bool playUser(string);
	private:
		vector <vector<char>> klotskiBoard;
		bool shift(char, int, int, mode);
		int sizeBrick(char target);

	};
}

#endif // KLOTSKIPUZ
