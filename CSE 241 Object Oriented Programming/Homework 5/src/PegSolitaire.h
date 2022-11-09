#include <iostream>
#include <string>
#include <vector>
#ifndef PEGSOLITAIRE
#define PEGSOLITAIRE

#include "BoardGame2D.h"
using namespace std;
using namespace Base;
namespace derived_peg{
	enum class state{PEG, EMPTY, WALL};

	class PegSolitaire: public BoardGame2D{
	public:
		PegSolitaire();
		int boardScore();
		void print();
		void initialize();
		bool playAuto(mode);
		bool playUser(string);
	private:
		vector <vector<state>> pegBoard;
		vector <vector<int>> empty_cell_coor() const;
		void empty_coor(int&, int&, vector<vector<int>>&);
		void find_direction(int& , vector<int>&);
		bool move(int, int, mode, int, int);
	};
}
#endif // PEGSOLITAIRE
