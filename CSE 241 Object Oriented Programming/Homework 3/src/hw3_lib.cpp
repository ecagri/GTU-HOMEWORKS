#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "hw3_lib.h"
using namespace std;

/* CONSTRUCTORS ----------------------------------------------------------------------------------------------------------- */

PegSolitaire::PegSolitaire(const int board_type){ /* Construct the object of PegSolitaire if it calls with type of the board. */
	set_board_types(type_of_board); /* Sets the board according to type. */
	type_of_board = board_type; /* Saves the type number of board. */
}

PegSolitaire::PegSolitaire(char size){ /* Construct the object of PegSolitaire if it calls with size of the board. */
	set_board(size-'0'); /* Sets the board according to size. */
	type_of_board = 0; /* Saves type number of board as 0. */
}

PegSolitaire::PegSolitaire(){ /* Construct the object of PegSolitaire if it calls without any parameter. */ 
	set_board(1); /* Sets the board to 1 size. */
	type_of_board = 0; /* Saves type number of board as 0. */
}

PegSolitaire::Cell::Cell(int x, char y, state type){ /* Construct the object of Cell if it calls with 3 parameter. */
	x_axis = x;
	y_axis = y;
	cell_type = type;
}

/* ------------------------------------------------------------------------------------------------------------------------ */

/* SETTERS ---------------------------------------------------------------------------------------------------------------- */

void PegSolitaire::set_board(int size){ /* Sets the board according to the size. */

	vector <Cell> v1; /* Creates a vector of object of Cell. */

	int empty_cell_coord = size/2; /* Sets the empty cell coordinates in the middle as possible. */

	if(size > 4){ /* If size is bigger than four, creates a board. */
		board.clear(); 

		for(int row = 0; row < size; row++){ 
			v1.clear();
			for(int col = 0; col < size; col++){
				Cell c1(row, col, state::PEG); /* Creates a cell of type PEG. */
				v1.push_back(c1); /* Push this cell to cell vector. */
				how_many_pegs +=1; /* Increases number of pegs on all board. */
			}
			board.push_back(v1); /* Push this vector to board. */
		}

		board[empty_cell_coord][empty_cell_coord].change_cell_type(state::EMPTY); /* Makes one of the cell empty. */
		how_many_pegs -=1; /* Decreases number of pegs on all board. */
	}
	else{ /* If size is not bigger than four, ends */
		cout << "Size of the board must be bigger than 4..." << endl;
	}
}

void PegSolitaire::set_name_of_board(){ /* Gets a name from the user and sets it as name of the board. */
	string name;
	cout << "Enter the name of the board:";
	cin >> name;
	name_of_board = name;
	set_statistics(); /* Sets also statistic of board. */
}

void PegSolitaire::set_name_of_board(string name){ /* Gets a string as a parameter and sets it as name of the board. */
	name_of_board = name;
	set_statistics(); /* Sets also statistic of board. */
}


void PegSolitaire::set_board_types(const int board_type){ /* Gets a integer parameter, and sets it as type of the board. */
	switch(board_type){
		case 1:
			board_type_1();
			break;
		case 2:
			board_type_2();
			break;
		case 3:
			board_type_3();
			break;
		case 4:
			board_type_4();
			break;
		case 5:
			board_type_5();
			break;
		case 6:
			board_type_6();
			break;
	}
	resize_board(); /* Resizes the board if it is not square. */
}

void PegSolitaire::set_statistics(){ /* Calculates number of peg and empty cells and assign it to statistics variable of the board. */
	int number_of_pegs = peg_cells_number(); 

	int number_of_empty = empty_cells_number();

	statistics.push_back(number_of_pegs);

	statistics.push_back(number_of_empty);
}

void PegSolitaire::resize_board(){ /* Resizes the board if it is not square. */
	int number_of_col = 0, number_of_row = board.size(), add_row = 0, add_col = 0;

	Cell c1(0, 0, state::EMPTY); /* Creates a empty cell. */

	for(auto col : board[0]){ /* Calculates number of coloumn. */
		number_of_col++;
	}

	add_row = number_of_col - number_of_row; /* Calculates how many row must be added. */

	add_col = number_of_row - number_of_col; /* Calculates how many coloumn must be added. */

	for(int i = 0; i < number_of_row; i++){ /* Makes operation to every row. */
		for(int k = 0; k < add_col; k++){ 
			if(board[i][number_of_col-1].type_of_cell() == state::PEG){ /* If the last coloumn is peg cell, convert type of c1 into peg cell. */
				c1.change_cell_type(state::PEG);
				how_many_pegs++;
			}
			else if(board[i][number_of_col-1].type_of_cell() == state::WALL) /* If the last coloumn is wall cell, convert type of c1 into wall cell. */
				c1.change_cell_type(state::WALL);
			board[i].push_back(c1); /* Adds the c1 to i. row of board. */
		}
	}

	for(int k = 0; k < add_row; k++){ 
		board.push_back(board[number_of_row-1]); /* Adds one row which is the same as last row to board. */

		for(auto col : board[number_of_row-1]){
			if(col.type_of_cell() == state::PEG)
				how_many_pegs++; /* Increases the how_many_pegs variable for new row. */
		}
	}
}

void PegSolitaire::Cell::change_cell_type(state type){ /* Changes the type of the cell. */
	cell_type = type;
}

/* ------------------------------------------------------------------------------------------------------------------------ */

/* FILE OPERATIONS -------------------------------------------------------------------------------------------------------- */

bool PegSolitaire::read(string filename){ /* Read a txt file and convert it into a board. */
	string line;
	vector <Cell> v1; /* Creates a Cell vector. */
	filename += ".txt";
	ifstream load(filename); /* Opens the file. */
	int row;
	char col;
	bool is_read = false;

	if(!load){ 
		cerr << "The file couldn't opened.";
	}
	else{
		board.clear(); /* Clears the board. */
		row = 0;
		while(getline (load, line) ){  /* Gets every line of the txt file one by one. */
			v1.clear();
			for(char a: line){ /* Gets every character of the line. */
				col = 'A';
				if(a == 'W'){ /* If the character is 'W', creates a wall cell, and push it into the cell vector. */
					Cell c1(row, col, state::WALL); 
					v1.push_back(c1);
				}
				else if(a == 'P'){ /* If the character is 'P', creates a peg cell, and push it into the cell vector. */
					Cell c1(row, col, state::PEG);
					v1.push_back(c1);
					how_many_pegs +=1; /* Increases how_many_pegs variable. */
				}
				else if(a == '.'){ /* If the character is '.', creates a empty cell, and push it into the cell vector. */
					Cell c1(row, col, state::EMPTY); 
					v1.push_back(c1);
				}
				else if(a > '0'){ /* If the character is a number, assign it into type_of_board variable. */
					type_of_board = a - '0';
				}
				col++;
			}
			row++;
			board.push_back(v1); /* Push the cell vector into board. */
		}
		is_read = true;
	}
	resize_board(); /* If the board is not square, resize it. */

	return is_read;
}
 
void PegSolitaire::write(string filename){ /* Prints the board to a txt file. */
	ofstream write_file(filename+".txt"); /* Creates a file. */

	for(int row = 0; row < board.size(); row++){ /* Searches every row of the board. */
		for(int col = 0; col < board.size(); col++){ /* Searches every coloumn of the board. */
			if(board[row][col].type_of_cell() == state::EMPTY) /* If the cell is empty cell, prints ' .' to the file. */
				write_file << " .";

			else if(board[row][col].type_of_cell() == state::PEG) /* If the cell is peg cell, prints ' P' to the file. */
				write_file << " P";

			else if(board[row][col].type_of_cell() == state::WALL) /* If the cell is wall cell, prints ' W' to the file. */
				write_file << " W";
		}		
		write_file << endl;
	}
}

/* ------------------------------------------------------------------------------------------------------------------------ */

/* PLAY FUNCTIONS --------------------------------------------------------------------------------------------------------- */

bool PegSolitaire::play(){ /* Makes one moves automatically. */
	bool completed = false;

	int rank, random_x_coordinate, random_y_coordinate;

	vector<vector<int>> empty_cell_vec; /* Creates a 2 dimensional integer vector to keep empty cell coordinates. */

	empty_cell_vec = empty_cells(); /* Fills the vector. */

	for(int i = 0; i < empty_cells_number() && completed == false; i++){ /* Try every empty cells until it moves. */
		do{ /* Continues until gets one logic coordinate. */
			rank = rand()%empty_cells_number();
			random_x_coordinate = empty_cell_vec[rank][0]; /* Assign x coordinate of one of the empty cells to random_x_coordinate variable. */
			random_y_coordinate = empty_cell_vec[rank][1]; /* Assign y coordinate of one of the empty cells to random_y_coordinate variable. */
		}while(random_x_coordinate == -1 && random_y_coordinate == -1);

		empty_cell_vec[rank][0] = -1; /* Assign -1 to x coordinate of empty cell to get rid of repetition. */
		empty_cell_vec[rank][1] = -1; /* Assign -1 to y coordinate of empty cell to get rid of repetition. */

		completed = all_direction(random_x_coordinate, random_y_coordinate); /* Calls all_direction function to try every direction to move. */
	}
	if(completed == true){ /* If the empty cells moves, decreases how_many_pegs variable. */
		how_many_pegs -=1;
		show_board();
	}

	return completed;
}

bool PegSolitaire::play(int row, int col){ /* Makes one moves by getting the coordinates from the user. */
	char direction;

	bool completed = false;

	cout << "Which direction do you want to move(r: for right, l: for left, u: for up, d: for down: ";

	cin >> direction; /* Gets direction input from the user. */

	switch(direction){
			case 'r':
				if(row >= 0 && row < board.size() && col >= 0 && col+2 < board.size()){ /* If coordinates is logical, continue. */
					completed = move_left(row, col+2); /* Calls move left function. */
					if(completed == true){ /* If the pegs can move, make the movement. */
						board[row][col+2].change_cell_type(state::PEG);
						board[row][col+1].change_cell_type(state::EMPTY);
						board[row][col].change_cell_type(state::EMPTY);
					}
				}
				break;
			case 'l':
				if(row >= 0 && row < board.size() && col-2 >= 0 && col < board.size()){ /* If coordinates is logical, continue. */
					completed = move_right(row, col-2); /* Calls move right function. */
					if(completed == true){ /* If the pegs can move, make the movement. */
						board[row][col-2].change_cell_type(state::PEG);
						board[row][col-1].change_cell_type(state::EMPTY);
						board[row][col].change_cell_type(state::EMPTY);
					}
				}
				break;
			case 'd':
				if(row >= 0 && row+2 < board.size() && col >= 0 && col < board.size()){ /* If coordinates is logical, continue. */
					completed = move_up(row+2, col); /* Calls move up function. */
					if(completed == true){ /* If the pegs can move, make the movement. */
						board[row+2][col].change_cell_type(state::PEG);
						board[row+1][col].change_cell_type(state::EMPTY);
						board[row][col].change_cell_type(state::EMPTY);
					}
				}
				break;
			case 'u':
				if(row >= 2 && row < board.size() && col >= 0 && col < board.size()){ /* If coordinates is logical, continue. */
					completed = move_down(row-2, col); /* Calls move down function. */
					if(completed == true){ /* If the pegs can move, make the movement. */
						board[row-2][col].change_cell_type(state::PEG);
						board[row-1][col].change_cell_type(state::EMPTY);
						board[row][col].change_cell_type(state::EMPTY);
					}
				}
				break;
		}
	if(completed == true){ /* If the pegs moves, decreases how_many_pegs variable. */
		show_board();
		how_many_pegs-=1;
	}
	if(is_game_end() == true){ /* If there is no moves left, show statistic. */
		cout << "There is no option to move, the game is over.";
		show_statistics();
	}
	return completed;
}

void PegSolitaire::playGame(){ /* Calls play function until the game is over. */
	bool completed = false;
	do{ 
		completed = play();
	}while(completed == true);
}

bool PegSolitaire::all_direction(int row, int col){

	bool completed = false;

	int all_direction[4] = {0,1,2,3}; /* Creates a all_direction array. */

	int random_rank, random_direction;

	for(int i = 0; i < 4 && completed == false; i++){ /* Try all direction until it moves. */

		do{ /* Continues until gets a logical direction. */
			random_rank = rand()%4;
			random_direction = all_direction[random_rank];
		}while(random_direction == -1);

		all_direction[random_rank] = -1; /* Assign -1 to current direction to get rid of repetition. */

		switch(random_direction){
			case 0:
				completed = move_right(row, col); /* Calls move_right function .*/
				if(completed == true){ /* If the empty cell can move, makes the movement. */
					board[row][col].change_cell_type(state::PEG);
					board[row][col+1].change_cell_type(state::EMPTY);
					board[row][col+2].change_cell_type(state::EMPTY);
				}
				break;
			case 1:
				completed = move_left(row, col); /* Calls move_left function .*/
				if(completed == true){ /* If the empty cell can move, makes the movement. */
					board[row][col].change_cell_type(state::PEG);
					board[row][col-1].change_cell_type(state::EMPTY);
					board[row][col-2].change_cell_type(state::EMPTY);
				}
				break;
			case 2:
				completed = move_down(row, col); /* Calls move_down function .*/
				if(completed == true){ /* If the empty cell can move, makes the movement. */
					board[row][col].change_cell_type(state::PEG);
					board[row+1][col].change_cell_type(state::EMPTY);
					board[row+2][col].change_cell_type(state::EMPTY);
				}
				break;
			case 3:
				completed = move_up(row, col); /* Calls move_up function .*/
				if(completed == true){ /* If the empty cell can move, makes the movement. */
					board[row][col].change_cell_type(state::PEG);
					board[row-1][col].change_cell_type(state::EMPTY);
					board[row-2][col].change_cell_type(state::EMPTY);
				}
				break;
		}
	}

	return completed;
}

/* ------------------------------------------------------------------------------------------------------------------------ */

/* OUTPUT FUNCTIONS ------------------------------------------------------------------------------------------------------- */


void PegSolitaire::Cell::show_cell(){ /* Shows the cell according to its type. */
	switch(cell_type){
		case state::EMPTY:
		cout << " .";
		break;
	case state::PEG:
		cout << " P";
		break;
	case state::WALL:
		cout << "  ";
		break;
	}
}

void PegSolitaire::show_board(){ /* Shows every cell of the board. */
	int j = 1;

	cout << ' ';
	for(int i = 0; i < board.size(); i++){ /* Sets coloumn letters. */
		cout << ' ' << char('A' + i);
	}
	cout << endl;

	for(auto &row : board){
		cout << j++; /* Sets row numbers. */
		for(auto col : row){
			col.show_cell(); /* Calls show_cell function. */
		}
		cout << endl;
	}	
	cout << endl;
}

void PegSolitaire::show_statistics(){ /* Shows some information about board. */
	cout << "There were " << statistics[0] << " pegs on the board." << endl;

	cout << "There are " << peg_cells_number() << " pegs left on the board." << endl;

	cout << statistics[0] - peg_cells_number() << " pegs is taken. " << endl;
}

/* ------------------------------------------------------------------------------------------------------------------------ */

/* HELPER FUNCTION -------------------------------------------------------------------------------------------------------- */


int PegSolitaire::empty_cells_number(){ /* Calculates number of empty cells on the board. */
	int number_of_empty = 0;
	for(auto &row : board){
		for(auto col : row){
			if(col.type_of_cell() == state::EMPTY){
				number_of_empty +=1;
			}
		}
	}	
	return number_of_empty;
}

vector <vector<int>> PegSolitaire::empty_cells(){ /* Saves empty cells coordinates to 2 dimensional integer vector. */
	vector <int> v1;

	vector <vector<int>> empty_cell_vec; /* Creates 2 dimensional integer vector. */

	empty_cell_vec.clear();

	for(int row = 0; row < board.size(); row++){
		for(int col = 0; col < board.size(); col++){
			v1.clear();
			if(board[row][col].type_of_cell() == state::EMPTY){ /* If the cell is empty, saves coordinates it to v1 vector. */
				v1.push_back(row);
				v1.push_back(col);

				empty_cell_vec.push_back(v1); /* Push the v1 vector to 2 dimensional integer vector. */
			}
		}
	}	
	return empty_cell_vec;
}
int PegSolitaire::peg_cells_number(){ /* Calculates number of peg cells on the board. */
	int number_of_pegs = 0;
	for(auto &row : board){
		for(auto col : row){
			if(col.type_of_cell() == state::PEG){
				number_of_pegs += 1;
			}
		}
	}	
	return number_of_pegs;
}

bool PegSolitaire::modification(PegSolitaire p1){ /* Controls the object is changed or not. */
	bool modificated = false;

	if(peg_cells_number() > p1.peg_cells_number()){
		modificated = true;
	}
	return modificated;
}

bool PegSolitaire::is_game_end(){ /* Controls the game whether is it end or not. */
	bool completed = false;
	for(int row = 0; row < board.size() && completed == false; row++){
		for(int col = 0; col < board.size() && completed == false; col++){
			if(board[row][col].type_of_cell() == state::EMPTY){ /* If the cell is empty, try every direction until it moves. */
				for(int all_direction = 0; all_direction < 4 && completed == false; all_direction++){
					switch(all_direction){
						case 0:
							completed = move_right(row, col);
							break;
						case 1:
							completed = move_left(row, col);
							break;
						case 2:
							completed = move_down(row, col);
							break;
						case 3:
							completed = move_up(row, col);
							break;
					}
				}
			}
		}
	}
	return !completed;
}

bool PegSolitaire::correct_board(string board_name){ /* Compares the name with the name of the board. */
	bool correct = false;
	if(board_name == name_of_board){
		correct = true;
	}
	return correct;
}

/* MOVE FUNCTIONS --------------------------------------------------------------------------------------------------------- */

bool PegSolitaire::move_right(const int row, const int col){ /* Returns true if it meets the conditions. */
	bool completed = false;

	if(col+2 < board.size() && board[row][col].type_of_cell() == state::EMPTY){
		if(board[row][col+1].type_of_cell() == state::PEG){
			if(board[row][col+2].type_of_cell() == state::PEG){
				completed = true;
			}
		}
	}
	return completed;
}

bool PegSolitaire::move_left(const int row, const int col){ /* Returns true if it meets the conditions. */
	bool completed = false;

	if(col-2 >= 0 && board[row][col].type_of_cell() == state::EMPTY){
		if(board[row][col-1].type_of_cell() == state::PEG){
			if(board[row][col-2].type_of_cell() == state::PEG){
				completed = true;
			}
		}
	}
	return completed;
}

bool PegSolitaire::move_down(const int row, const int col){ /* Returns true if it meets the conditions. */
	bool completed = false;

	if(row+2 < board.size() && board[row][col].type_of_cell() == state::EMPTY){
		if(board[row+1][col].type_of_cell() == state::PEG){
			if(board[row+2][col].type_of_cell() == state::PEG){
				completed = true;
			}
		}
	}
	return completed;
}

bool PegSolitaire::move_up(const int row, const int col){ /* Returns true if it meets the conditions. */
	bool completed = false;

	if(row-2 >= 0  && board[row][col].type_of_cell() == state::EMPTY){
		if(board[row-1][col].type_of_cell() == state::PEG){
			if(board[row-2][col].type_of_cell() == state::PEG){
				completed = true;
			}
		}
	}
	return completed;
}

/* ------------------------------------------------------------------------------------------------------------------------ */

/* BOARD TYPES ------------------------------------------------------------------------------------------------------------ */


void PegSolitaire::board_type_1(){ /* Sets board type_1. */
	Cell emptycell(0, 0, state::EMPTY); /* Creates a empty cell. */
	Cell pegcell(0, 0, state::PEG); /* Creates a peg cell .*/
	Cell wallcell(0, 0, state::WALL); /* Creates a wall cell. */

	board = {
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell},
		{wallcell, pegcell, pegcell, pegcell, pegcell, pegcell, wallcell},
		{pegcell, pegcell, pegcell, emptycell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{wallcell, pegcell, pegcell, pegcell, pegcell, pegcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell}
	};
	how_many_pegs +=36; /* Increases how_many_pegs variable by 36. */
}

void PegSolitaire::board_type_2(){ /* Sets board type_2. */
	Cell emptycell(0, 0, state::EMPTY); /* Creates a empty cell. */
	Cell pegcell(0, 0, state::PEG); /* Creates a peg cell .*/
	Cell wallcell(0, 0, state::WALL); /* Creates a wall cell. */

	board = {
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, pegcell, emptycell, pegcell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell}
	};
	how_many_pegs +=44; /* Increases how_many_pegs variable by 44. */
}

void PegSolitaire::board_type_3(){ /* Sets board type_3. */
	Cell emptycell(0, 0, state::EMPTY); /* Creates a empty cell. */
	Cell pegcell(0, 0, state::PEG); /* Creates a peg cell .*/
	Cell wallcell(0, 0, state::WALL); /* Creates a wall cell. */

	board = {
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, emptycell, pegcell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell}
	};
	how_many_pegs +=38; /* Increases how_many_pegs variable by 38. */
}

void PegSolitaire::board_type_4(){ /* Sets board type_4. */
	Cell emptycell(0, 0, state::EMPTY); /* Creates a empty cell. */
	Cell pegcell(0, 0, state::PEG); /* Creates a peg cell .*/
	Cell wallcell(0, 0, state::WALL); /* Creates a wall cell. */

	board = {
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, emptycell, pegcell, pegcell, pegcell},
		{pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell}
	};
	how_many_pegs +=32; /* Increases how_many_pegs variable by 32. */
}

void PegSolitaire::board_type_5(){ /* Sets board type_5. */
	Cell emptycell(0, 0, state::EMPTY); /* Creates a empty cell. */
	Cell pegcell(0, 0, state::PEG); /* Creates a peg cell .*/
	Cell wallcell(0, 0, state::WALL); /* Creates a wall cell. */

	board = {
		{wallcell, wallcell, wallcell, wallcell, pegcell, wallcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, pegcell, pegcell, wallcell, wallcell},
		{wallcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, wallcell},
		{pegcell, pegcell, pegcell, pegcell, emptycell, pegcell, pegcell, pegcell, pegcell},
		{wallcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, pegcell, wallcell},
		{wallcell, wallcell, pegcell, pegcell, pegcell, pegcell, pegcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, pegcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, wallcell, pegcell, wallcell, wallcell, wallcell, wallcell}
	};
	how_many_pegs +=40; /* Increases how_many_pegs variable by 40. */
}

void PegSolitaire::board_type_6(){ /* Sets board type_6. */
	Cell emptycell(0, 0, state::EMPTY); /* Creates a empty cell. */
	Cell pegcell(0, 0, state::PEG); /* Creates a peg cell .*/
	Cell wallcell(0, 0, state::WALL); /* Creates a wall cell. */

	board = {
		{wallcell, wallcell, wallcell, wallcell, emptycell, wallcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, wallcell, pegcell, wallcell, pegcell, wallcell, wallcell, wallcell},
		{wallcell, wallcell, pegcell, wallcell, pegcell, wallcell, pegcell, wallcell, wallcell},
		{wallcell, pegcell, wallcell, pegcell, wallcell, pegcell, wallcell, pegcell, wallcell},
		{pegcell, wallcell, pegcell, wallcell, pegcell, wallcell, pegcell, wallcell, pegcell}
	};
	how_many_pegs +=14; /* Increases how_many_pegs variable by 14. */
}

/* ------------------------------------------------------------------------------------------------------------------------ */









