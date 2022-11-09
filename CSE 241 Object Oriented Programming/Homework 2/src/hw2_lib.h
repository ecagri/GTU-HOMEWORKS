#include <vector>
#include <string>
using namespace std;

enum class state{ WALL, PEG, EMPTY};

bool border_violation(vector <vector<state>> board, const int &vertical, const int &horizontal);

void show_board(vector <vector<state>> board); 

void show_results(vector <vector<state>> board);

int count_pegs(vector <vector<state>> board);

int is_change(vector <vector<state>> oldboard, vector <vector<state>> newboard);

/* These are helper functions for solve_puzzle function. */

vector <vector<int>> find_empty_cells(vector <vector<state>> board);

vector <vector<int>> random_empty_cell(vector <vector<int>> empty_cells, vector <vector<state>> board, int &xcoordinate, int &ycoordinate);

int empty_cells_number(vector <vector<state>> board, int number_of_empty); 

/* ----------------------------------------------------- */

/* Puzzle solver functions, manuel or automatically. */

void solve_puzzle(vector <vector<state>> board, int board_type);

void get_user_move(vector <vector<state>> board, int board_type);

/* ------------------------------------------------- */

/* File handling functions. */

vector <vector<state>> file_operation(vector <vector<state>> board, bool *opr_completed, int * board_type);

vector <vector<state>> LOAD(vector <vector<state>> board, string filename, bool *opr_completed, int * board_type);

vector <vector<state>> SAVE(vector <vector<state>> board, string filename, int * board_type);

/* ------------------------ */

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




