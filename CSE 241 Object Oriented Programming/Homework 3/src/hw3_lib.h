#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum class state{EMPTY, WALL, PEG};

class PegSolitaire{
	
public:
	/* ----- CONSTRUCTORS ----- */

	PegSolitaire(const int board_type);

	PegSolitaire(char size_of_board);

	PegSolitaire();

	/* ------ SETTERS -----*/

	void set_board(int size);

	void set_board_types(const int board_type);

	void set_statistics();

	void set_name_of_board();

	void set_name_of_board(string name);

	void resize_board();

	/* ----- FILE OPERATIONS ----- */

	bool read(string filename);

	void write(string filename);

	/* ----- PLAY FUNCTIONS ----- */

	bool play();

	bool play(int row, int col);

	void playGame();

	bool all_direction(int row, int col);

  	/* ----- OUTPUT FUNCTIONS ----- */

	void show_statistics();

	void show_board();

	/* ----- HELPER FUCTIONS ----- */

	bool modification(PegSolitaire p1);

	bool correct_board(string board_name);

	int empty_cells_number();

	int peg_cells_number();

	int current_type() { return type_of_board; }

	vector <vector<int>> empty_cells();

	/* ----- STATIC COUNTERS ----- */

	static int count_pegs(){ return how_many_pegs; }

	static int how_many_pegs;

	class Cell{
		public:
			/* ----- CONSTRUCTOR ----- */

			Cell(int x, char y, state type);

			/* ----- SETTER ----- */

			void change_cell_type(state type);

			/* ----- OUTPUT FUNCTION ----- */

			void show_cell();

			/* ----- HELPER FUCTION ----- */
			
			inline state type_of_cell(){ return cell_type; }
		private:
			state cell_type;

			int x_axis;

			char y_axis;
	};

private:
	vector<vector<Cell>> board;

	string name_of_board;

	int type_of_board;

	vector <int> statistics;

	/* ----- BOARD TYPES ----- */

	void board_type_1();

	void board_type_2();

	void board_type_3();

	void board_type_4();

	void board_type_5();

	void board_type_6();

	/* ----- MOVE FUNCTIONS ----- */

	bool move_right(const int row, const int col);

	bool move_left(const int row, const int col);

	bool move_down(const int row, const int col);

	bool move_up(const int row, const int col);

	/* ----- HELPER FUCTION ----- */

	bool is_game_end();

};

