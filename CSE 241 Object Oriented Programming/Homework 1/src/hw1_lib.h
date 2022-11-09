#include <vector>
using namespace std;

enum class state{ WALL, PEG, EMPTY};

void show_board(vector <vector<state>> board, int boardsize); /* Shows the board for first 5 board types. */

void show_board_2(vector <vector<state>> board, int boardsize); /* Shows the board for 6th board type. */

int control_board(vector <vector<state>> board, int boardsize); /* Controls board whether it is finished or not. */

void show_results(vector <vector<state>> board, int boardsize); /* Shows the how many pegs are left on the board. */

void get_user_move(vector <vector<state>> board); /* Gets user moves until the user wants to quit or there is only one peg on the board. It works for first 5 board types.*/

void get_user_move_2(vector <vector<state>> board); /* Gets user moves until the user wants to quit or there is only one peg on the board. It works for 6th board type.*/

int is_change(vector <vector<state>> oldboard, vector <vector<state>> newboard, int boardsize); /* Controls the board whether it is changed or not. */

int empty_cells(vector <vector<state>> board, int boardsize); /* Calculates the number of the empty cells. */

void solve_puzzle(vector <vector<state>> board, int boardsize); /* Solve puzzle randomly for first 5 board types. */

void solve_puzzle_2(vector <vector<state>> board, int boardsize); /* Solve puzzle randomly for 6th board types. */

/* Bottom functions set the vectors. */

vector <vector<state>> board_type_1();

vector <vector<state>> board_type_2();

vector <vector<state>> board_type_3();

vector <vector<state>> board_type_4();

vector <vector<state>> board_type_5();

vector <vector<state>> board_type_6();

/*---------------------------------- */

/* These functions move the pegs for first 5 board types. */

vector <vector<state>> move_right(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_left(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_down(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_up(vector <vector<state>> board, int x, int y);

/* ------------------------------------------------------ */

/* These functions move the pegs for 6th board type. */

vector <vector<state>> move_right_2(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_left_2(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_down_right(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_down_left(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_up_right(vector <vector<state>> board, int x, int y);

vector <vector<state>> move_up_left(vector <vector<state>> board, int x, int y);

/* ------------------------------------------------- */




