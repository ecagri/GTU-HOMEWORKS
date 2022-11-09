#include "hw2_lib.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

/* ----------------------------------------------------------------------------------- */

void show_board(vector <vector<state>> board){ /* Shows the board in a pretty format. */
	char letters;
	int i = 0, j = 0;
	cout << endl << ' ';
	for(state col: board[0]){ /* Prints letters to clarify horizontal axis. */
		letters = 65 + j++;
		cout << ' ' << letters;
	}
	cout << endl;
	for(auto &row : board){
		cout << ++i; /* Prints numbers to clarify vertical axis. */
		for(state col : row){
			if(col == state::WALL){ /* If the cell is wall prints ' '. */
				cout << "  ";
			}
			else if(col == state::PEG){ /* If the cell is peg prints 'P'. */
				cout << " P";
			}
			else if(col == state::EMPTY){ /* If the cell is empty prints '.'. */
				cout << " .";
			}
		}
		cout << endl;
	}
}

/* ----------------------------------------------------------------------------------- */

int count_pegs(vector <vector<state>> board){ /* Counts the pegs on the board and return it. */
	int numberofpegs = 0;
	for(auto &row : board){
		for(state col : row){
			if(col == state::PEG)
				numberofpegs+=1;
		}
	}
	return numberofpegs;
}	

/* ----------------------------------------------------------------------------------- */

bool border_violation(vector <vector<state>> board, const int &vertical, const int &horizontal){ /* Controls the border violation of moves. */
	int i = 0, j = 0;
	bool control_borders;
	for(state col: board[0]){ /* Finds numbers of coloumns of board. */
		j++;
	}

	i = board.size(); /* Finds numbers of rows of board. */

	if(vertical >= 0 && horizontal >= 0 && vertical < i && horizontal < j) /* If there is no border violation returns false. */
		control_borders = false;
	else /* If there is a border violation returns true. */
		control_borders = true;

	return control_borders;
}

/* ----------------------------------------------------------------------------------- */

void show_results(vector <vector<state>> board){ /* Shows the result of the game. */
	int numberofpegs = count_pegs(board); /* Calculates how many pegs is left on the board. */
	if(numberofpegs < 1) /* If number of pegs is less than 1, there must be a mistake. */
		cerr << "ERROR!!!";
	else
		cout << numberofpegs << " pegs has been left on the board." << endl; /* Prints the number of pegs on the board. */
}

/* ----------------------------------------------------------------------------------- */

int is_change(vector <vector<state>> oldboard, vector <vector<state>> newboard){ /* Takes two board as parameters and controls whether they are same or not. */
	int is_changed = 0;

	if(count_pegs(newboard) != count_pegs(oldboard)) /* If number of pegs are on boards are different, the boards are different. */
		is_changed = 1;

	return is_changed;
}

/* ----------------------------------------------------------------------------------- */

int empty_cells_number(vector <vector<state>> board, int number_of_empty){ /* Counts the number of empty cell on the board and return it. */
	for(auto &row : board){
		for(state col : row){
			if(col == state::EMPTY)
				number_of_empty+=1;
		}
	}

	return number_of_empty;
}

/* ----------------------------------------------------------------------------------- */

vector <vector<int>> find_empty_cells(vector <vector<state>> board){ /* Finds empty cells on the board and insert their coordinate into the empty_cells vector and returns it. */
	vector <vector<int>> empty_cells; /* Creates two dimensional integer vector. */
	vector <int> temp; /* Creates one dimensional integer vector. */

	int xcoordinate = 0, ycoordinate;

	for(auto &row : board){ /* Searches every row. */
		ycoordinate = 0;
		for(state col : row){ /* Searches every coloumn. */
			temp.clear(); /* Clear the temp vector. */
			if(col == state::EMPTY){ /* If one of the cells is empty, insert coordinates of it into the temp vector. */
				temp.push_back(xcoordinate);
				temp.push_back(ycoordinate);
				empty_cells.push_back(temp); /* Insert the temp vector into the empty_cells vector. */
			}
			ycoordinate+=1;

		}
		xcoordinate+=1;
	}
	return empty_cells;
}

/* ----------------------------------------------------------------------------------- */

vector <vector<int>> random_empty_cell(vector <vector<int>> empty_cells, vector <vector<state>> board, int &xcoordinate, int &ycoordinate){
	int rank; 

	int number_of_empty = empty_cells_number(board, 0); /* Calculates empty cells on the board. */

	do{
		rank = rand()%number_of_empty; /* Creates a random number in the range of 0 to number of empty cells. */
	}while(empty_cells[rank][0] == -1 && empty_cells[rank][1] == -1); /* Continues until gets valid coordinates. */

	xcoordinate = empty_cells[rank][0];
	ycoordinate = empty_cells[rank][1];

	/* After the gets coordinate, assign them -1 to get rid of repetetions. */
	empty_cells[rank][0] = -1;
	empty_cells[rank][1] = -1;
	
	return empty_cells;
}


/* ----------------------------------------------------------------------------------- */

vector <int> set_direction_vec(vector <int> direction, int board_type){ /* Creates a vector for directions. */
	if(board_type == 6) /* If the board_type is 6, there are 6 dimensions. */
		direction = {1,2,3,4,5,6,0,0,0,0};
	else /* If the board_type is not 6, there are 4 dimensions. */
		direction = {0,0,0,0,0,0,7,8,9,10};
	return direction;

}

/* ----------------------------------------------------------------------------------- */

void solve_puzzle(vector <vector<state>> board, int board_type){

	int xcoordinate, ycoordinate, is_changed = 0, alldirection, random_index, random_direction, number_of_empty;

	bool opr_completed = false;

	board = file_operation(board, &opr_completed, &board_type); /* Checks whether the user wants to save or not. */

	vector <vector<state>> oldboard = board; /* Creates a vector to compares the vectors. */

	vector <int> direction(10);

	vector <vector<int>> empty_cells = find_empty_cells(board); 

	number_of_empty = empty_cells_number(board, 0); /* Calculates empty cells on the board. */

	srand(time(NULL));

	for(int i = 0; i < number_of_empty && is_changed == 0 && opr_completed == false; ++i){ 
		
		empty_cells = random_empty_cell(empty_cells, board, xcoordinate, ycoordinate); /* Select one of empty cells and assign it's coordinate to xcoordinate and ycoordinate variables. */

		direction = set_direction_vec(direction, board_type); /* Sets a direction vector is unique to type of the board. */

		do{ /* Try every direction until it moves. */
			alldirection = 1;

			do{
				random_index = random()%direction.size();
				random_direction = direction[random_index];
			}while(random_direction == 0);
			direction[random_index] = 0; /* Makes the current direction 0 to get rid of try same direction again. */

			switch(random_direction){
				case 1: /* If direction is right, move right. */
					board = move_right_2(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 2: /* If direction is left, move left. */
					board = move_left_2(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 3: /* If direction is down and right, move down and right. */
					board = move_down_right(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 4: /* If direction is down and left, move down and left. */
					board = move_down_left(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 5: /* If direction is up and right, move up and right. */
					board = move_up_right(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 6: /* If direction is up and left, move up and left. */
					board = move_up_left(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 7: /* If direction is right, move right. */
					board = move_right(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 8: /* If direction is left, move left. */
					board = move_left(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 9: /* If direction is down, move down. */
					board = move_down(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				case 10: /* If direction is up, move up. */
					board = move_up(board, xcoordinate, ycoordinate);
					is_changed = is_change(oldboard, board);
					break;
				
			}
			for(int a : direction){ /* Checks all direction was tried or not. */
				if(a != 0) 
					alldirection = 0;
			}
		}while(is_changed == 0 && alldirection == 0);		
	}

	empty_cells.clear();

	if(is_changed == 1){ /* If the puzzle is changed, continue. */
		solve_puzzle(board, board_type);
	}
	
	else if(is_changed == 0 && opr_completed == false)/* Otherwise shows the results. */
		show_results(board);
	
}

/* ----------------------------------------------------------------------------------- */

void get_user_move(vector <vector<state>> board, int board_type){
	char direction, file_opr[256];
	int xcoordinate, ycoordinate, quitcontrol = 0, random_direction;
	vector <vector<state>> oldboard;
	string operation;
	bool opr_completed = false;
	srand(time(NULL));
	while(count_pegs(board) != 1 && quitcontrol == 0 && opr_completed == false){ /* Checks whether the game is completed or not, checks whether user wants to quit or not. */
		oldboard = board; /* Temp vector to compare the vector is changed or not. */
		direction = '0'; /* To get rid of garbage value. */
		cout << "Enter your move (like B4-R, enter 'q' to quit): ";

		cin.getline(file_opr, 256); /* Gets user move or file operations of user. */

		operation = file_opr;

		if(operation.compare(0, 4, "SAVE") == 0){ /* Checks user wants to save. */
			board = SAVE(board, &file_opr[5], &board_type); /* Save the board. */
			opr_completed = true; /* If file operation is completed, do not continue. */ 
		}

		if(opr_completed == false){
			if(operation.size() == 4){ /* If the size of string is not equals to 4, there must be a mistake. */
				ycoordinate = operation[0]-'A'; /* Get numeric value of y coordinate. */
				xcoordinate = operation[1]-'1'; /* Get numeric value of x coordinate. */
				direction = operation[3];
			}

			for(char x : operation) /* Controls whether user wants to quit. */
				if(x == 'q' || x == 'Q') /* If one of the character of the string is 'q' or 'Q', user wants to quit. */
					quitcontrol = 1; 
			if(board_type == 6){ /* If board_type is 6, continue. */
				switch(direction){
					case 'R': /* If direction is right, moves empty cell to left. */
						board = move_left_2(board, xcoordinate, ycoordinate+4);
						break;
					case 'L': /* If direction is left, moves empty cell to right. */
						board = move_right_2(board, xcoordinate, ycoordinate-4);
						break;
					case 'U':
					 	random_direction = random()%2; /* Produce a random value to decide up and right or up and left. */
					 	if(random_direction == 0){ /* If the random value is 0, first try to move down and right. */
						 	board = move_down_right(board, xcoordinate-2, ycoordinate-2); 
						 	if(is_change(oldboard, board) == 0) /* If move down and right movement is not legal, try move down and left. */
						 		board = move_down_left(board, xcoordinate-2, ycoordinate+2);
						}
						else{ /* If the random value is 1, try to move down and left. */
							board = move_down_left(board, xcoordinate-2, ycoordinate+2); /* If direction is up, moves empty cell to down. */
							if(is_change(oldboard, board) == 0) /* If move down and left movement is not legal, try move down and right. */
						 		board = move_down_right(board, xcoordinate-2, ycoordinate-2); /* If direction is up, moves empty cell to down. */
						}
						break;
					case 'D':
						random_direction = random()%2; /* Produce a random value to decide down and right or down and left. */
					 	if(random_direction == 0){ /* If the random value is 0, first try to move up and right. */
						 	board = move_up_right(board, xcoordinate+2, ycoordinate-2); /* If direction is down, moves empty cell to up. */
						 	if(is_change(oldboard, board) == 0) /* If move up and right movement is not legal, try move up and left. */
						 		board = move_up_left(board, xcoordinate+2, ycoordinate+2); /* If direction is down, moves empty cell to up. */
						}
						else{ /* If the random value is 1, try to move down and left. */
							board = move_up_left(board, xcoordinate+2, ycoordinate+2); /* If direction is down, moves empty cell to up. */
							if(is_change(oldboard, board) == 0) /* If move up and left movement is not legal, try move up and right. */
						 		board = move_up_right(board, xcoordinate+2, ycoordinate-2); /* If direction is down, moves empty cell to up. */
						}
					break;
				}
			}
			else{
				switch(direction){
					 case 'R': /* If direction is right, moves empty cell to left. */
						 board = move_left(board, xcoordinate, ycoordinate+2);
						 break;
					 case 'L': /* If direction is left, moves empty cell to right. */
						 board = move_right(board, xcoordinate, ycoordinate-2);
						 break;
					 case 'U': /* If direction is up, moves empty cell to down. */
						 board = move_down(board, xcoordinate-2, ycoordinate);
						 break;
					 case 'D': /* If direction is down, moves empty cell to up. */
						 board = move_up(board, xcoordinate+2, ycoordinate);
						 break;
				}
			}
		}
	}

	show_results(board); /* Shows the results. */
}

/* ----------------------------------------------------------------------------------- */

vector <vector<state>> file_operation(vector <vector<state>> board, bool *opr_completed,int *board_type){ /* Saves the board to a file. */
	char operation_arr[256];

	string operation_str;

	cin.getline(operation_arr, 256);

	operation_str = operation_arr;
	if(operation_str.compare(0, 4, "SAVE") == 0){
		board = SAVE(board, &operation_arr[5], board_type); /* Save the board. */
		*opr_completed = true;
		cin.get();
	}
	return board;
}

/* ----------------------------------------------------------------------------------- */

vector <vector<state>> LOAD(vector <vector<state>> board, string filename, bool *opr_completed, int * board_type){ /* Load the board from a file. */
	fstream load_back;

	string text;

	load_back.open(filename, ios::in); /* Open the file in input format. */

	if(!load_back){ /* If the file couldn't opened, prints an error. */
		cerr << "The file couldn't opened.";
	}
	else{
		board.clear(); /* Clears the board. */
		while(getline(load_back, text)){ /* Gets every line from the file. */
			vector <state> v1; /* Creates a vector. */

			for(char a: text){
				if(a == 'O'){ /* If a is 'O', insert wall state into v1 vector. */
					v1.push_back(state::WALL);
				}
				else if(a == 'P'){ /* If a is 'P', insert wall state into v1 vector. */
					v1.push_back(state::PEG);
				}
				else if(a == '.'){ /* If a is 'O', insert wall state into v1 vector. */
					v1.push_back(state::EMPTY);
				}
				else if(a >= '0' && a <= '9'){ /* If a is a number in between 0-9, it is board type and saves it as board type. */
					*board_type = a-'0';
				}
			}
			board.push_back(v1); /* Insert v1 vector into board. */
		}
		*opr_completed = true;
	}

	load_back.close(); /* Closes the file. */

	return board;
}

/* ----------------------------------------------------------------------------------- */

vector <vector<state>> SAVE(vector <vector<state>> board, string filename, int * board_type){
	fstream save_it;

	int i = 1;

	save_it.open(filename, ios::out); /* Open the file in output format. */

	for(auto &row : board){
		for(state col: row){ /* Checks every cells of board. */
			if(col == state::EMPTY){ /* If the cell is EMPTY, prints '.' to the file. */
				save_it << ". ";
			}
			else if(col == state::PEG){ /* If the cell is PEG, prints 'P' to the file. */
				save_it << "P ";
			}
			else if(col == state::WALL){ /* If the cell is WALL, prints 'O' to the file. */
				save_it << "O ";
			}
		}
		if(i == board.size()) /* At the last row, prints also board type to the file. */
			save_it << (*board_type);
		save_it << endl;
		i++;
	}
	save_it.close(); /* CLoses the file. */

	return board;
}

/* ---------------------------------- state::PEG MOVE FUNCTİONS -------------------------------- */

vector <vector<state>> move_right(vector <vector<state>> board, int x, int y){ /* Moves empty cell to right. */
	if(border_violation(board, x, y+2) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y+1] == state::PEG && board[x][y+2] == state::PEG && board[x][y] == state::EMPTY){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state::PEG;
			board[x][y+1] = state::EMPTY;
			board[x][y+2] = state::EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_left(vector <vector<state>> board, int x, int y){ /* Moves empty cell to left. */
	if(border_violation(board, x, y-2) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y-1] == state::PEG && board[x][y-2] == state::PEG && board[x][y] == state::EMPTY){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state::PEG;
			board[x][y-1] = state::EMPTY;
			board[x][y-2] = state::EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_down(vector <vector<state>> board, int x, int y){ /* Moves empty cell to down. */
	if(border_violation(board, x+2, y) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x+1][y] == state::PEG && board[x+2][y] == state::PEG  && board[x][y] == state::EMPTY){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state::PEG;
			board[x+1][y] = state::EMPTY;
			board[x+2][y] = state::EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_up(vector <vector<state>> board, int x, int y){ /* Moves empty cell to up. */
	if(border_violation(board, x-2, y) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x-1][y] == state::PEG && board[x-2][y] == state::PEG  && board[x][y] == state::EMPTY){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state::PEG;
			board[x-1][y] = state::EMPTY;
			board[x-2][y] = state::EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_right_2(vector <vector<state>> board, int x, int y){ /* Moves empty cell to right. */
	if(border_violation(board, x, y+4) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y] == state::EMPTY && board[x][y+2] == state:: PEG && board[x][y+4] == state:: PEG){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state:: PEG;
			board[x][y+2] = state:: EMPTY;
			board[x][y+4] = state:: EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_left_2(vector <vector<state>> board, int x, int y){ /* Moves empty cell to left. */
	if(border_violation(board, x, y-4) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y] == state::EMPTY && board[x][y-2] == state:: PEG && board[x][y-4] == state:: PEG){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state:: PEG;
			board[x][y-2] = state:: EMPTY;
			board[x][y-4] = state:: EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_down_right(vector <vector<state>> board, int x, int y){ /* Moves empty cell to down and right. */
	if(border_violation(board, x+2, y+2) == false && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y] == state::EMPTY && board[x+1][y+1] == state:: PEG && board[x+2][y+2] == state:: PEG){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state:: PEG;
			board[x+1][y+1] = state:: EMPTY;
			board[x+2][y+2] = state:: EMPTY;
			show_board(board);
		}
	}
	return board;
}
vector <vector<state>> move_down_left(vector <vector<state>> board, int x, int y){ /* Moves empty cell to down and left. */
	if(border_violation(board, x+2, y-2) == 0 && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y] == state::EMPTY && board[x+1][y-1] == state:: PEG && board[x+2][y-2] == state:: PEG){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state:: PEG;
			board[x+1][y-1] = state:: EMPTY;
			board[x+2][y-2] = state:: EMPTY;
			show_board(board);
		}
	}
	return board;
}

vector <vector<state>> move_up_right(vector <vector<state>> board, int x, int y){ /* Moves empty cell to up and right. */
	if(border_violation(board, x-2, y+2) == 0 && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y] == state::EMPTY && board[x-1][y+1] == state:: PEG && board[x-2][y+2] == state:: PEG){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state:: PEG;
			board[x-1][y+1] = state:: EMPTY;
			board[x-2][y+2] = state:: EMPTY;
			show_board(board);
		}
	}
return board;
}
vector <vector<state>> move_up_left(vector <vector<state>> board, int x, int y){ /* Moves empty cell to up and left. */
	if(border_violation(board, x-2, y-2) == 0 && border_violation(board, x, y) == false){ /* Checks is there a border violation. */
		if(board[x][y] == state::EMPTY && board[x-1][y-1] == state:: PEG && board[x-2][y-2] == state:: PEG){ /* Moves the pegs if it satisfies the rule. */
			board[x][y] = state:: PEG;
			board[x-1][y-1] = state:: EMPTY;
			board[x-2][y-2] = state:: EMPTY;
			show_board(board);
		}
	}
	return board;
}

/* ----------------------------------------------------------------------------------- */


/* ----------------------------------------- BOARD TYPES ----------------------------- */

vector <vector<state>> board_type_1(){
	vector <vector<state>> board{
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::WALL},
		{state::PEG, state::PEG, state::PEG, state::EMPTY, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::WALL, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL}
	};
	return board;
}

vector <vector<state>> board_type_2(){
	vector <vector<state>> board{
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::EMPTY, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL}
	};
	return board;
}

vector <vector<state>> board_type_3(){
	vector <vector<state>> board{
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::EMPTY, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL}
	};
	return board;
}

vector <vector<state>> board_type_4(){
	vector <vector<state>> board{
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::EMPTY, state::PEG, state::PEG, state::PEG},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL}
	};
	return board;
}

vector <vector<state>> board_type_5(){
	vector <vector<state>> board{
		{state::WALL, state::WALL, state::WALL, state::WALL, state::PEG, state::WALL, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::WALL},
		{state::PEG, state::PEG, state::PEG, state::PEG, state::EMPTY, state::PEG, state::PEG, state::PEG, state::PEG},
		{state::WALL, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::PEG, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::WALL, state::PEG, state::WALL, state::WALL, state::WALL, state::WALL}
	};
	return board;
}

vector <vector<state>> board_type_6(){
	vector <vector<state>> board{
		{state::WALL, state::WALL, state::WALL, state::WALL, state::EMPTY, state::WALL, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL},
		{state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG}
	};
	return board;
}


/* ----------------------------------------------------------------------------------- */
