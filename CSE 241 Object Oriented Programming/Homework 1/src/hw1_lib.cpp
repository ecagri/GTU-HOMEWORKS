#include "hw1_lib.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

/* ----------------------------------------------------------------------------------- */

void show_board(vector <vector<state>> board, int boardsize){
	char letters;
	cout << endl <<' ';
	for(int k = 0; k < boardsize; k++){ /* Sets letters from right to left for output. */
		letters = 65 + k;
		cout << ' ' << letters;
	}
	cout << endl;
	for(int i = 0; i < boardsize; ++i){ /* Prints the pegs, walls and empty cells until end of the board. */
		cout << i+1; /* Prints number from top the bottom.  */
		for(int j = 0; j < boardsize; ++j){
			if(board[i][j] == state::WALL){
				cout << "  ";
			}
			else if(board[i][j] == state::PEG){
				cout << " P";
			}
			else if(board[i][j] == state::EMPTY){
				cout << " .";
			}
		}
		cout << endl;
	}
}

void show_board_2(vector <vector<state>> board, int boardsize){
	char letters;
	int j = 0;
	cout << endl <<' ';
	for(int k = 0; k < boardsize; k++){ /* Sets letters right to left for output. */
		letters = 65 + k;
		cout << ' ' << letters;
	}
	cout << endl;
	for(int i = 0; i < boardsize; ++i){ /* Prints the pegs, walls and empty cells until end of the board. */
		if(i%2 == 0) /* Prints number from top the bottom.  */
			cout << ++j;

		for(int j = 0; j < boardsize; ++j){
			if(board[i][j] == state::WALL){
				cout << "  ";
			}
			else if(board[i][j] == state::PEG){
				cout << " P";
			}
			else if(board[i][j] == state::EMPTY){
				cout << " .";
			}
		}
		cout << endl;
	}
}

/* ----------------------------------------------------------------------------------- */

int control_board(vector <vector<state>> board, int boardsize){
	int numberofpegs = 0, control = 0;
	for(int i = 0; i < boardsize; ++i){ /* Counters the pegs. */
		for(int j = 0; j < boardsize; ++j){
			if(board[i][j] == state::PEG)
				numberofpegs++;
		}
	}

	if(numberofpegs == 1) /* If there is only one peg, the game is completed. */
		control = 1;
	return control;
}	

/* ----------------------------------------------------------------------------------- */

void show_results(vector <vector<state>> board, int boardsize){
	int numberofpegs = 0;
	for(int i = 0; i < boardsize; ++i){ /* Counters the pegs. */
		for(int j = 0; j < boardsize; ++j){
			if(board[i][j] == state::PEG)
				numberofpegs++;
		}
	}
	if(numberofpegs < 1) /* If number of pegs is less than 1, there must be a mistake. */
		cout << "ERROR!!!";
	else
		cout << numberofpegs << " pegs has been left on the board."; /* Prints the number of pegs on the board. */
}

/* ----------------------------------------------------------------------------------- */

void get_user_move(vector <vector<state>> board){
	string movement;
	char direction;
	int xcoordinate, ycoordinate, quitcontrol = 0;
	while(control_board(board, board.size()) != 1 && quitcontrol == 0){ /* Checks whether the game is completed or not, checks whether user wants to quit or not. */
		direction = '0'; /* To get rid of garbage value. */
		cout << "Enter your move (like B4-R, enter 'q' to quit): ";
		cin >> movement; /* Gets user's movement. */

		if(movement.size() == 4){ /* If the size of string is not equals to 4, there must be a mistake. */
			ycoordinate = movement[0]-'A'; /* Get numeric value of y coordinate. */
			xcoordinate = movement[1]-'1'; /* Get numeric value of x coordinate. */
			direction = movement[3];
		}

		for(char x : movement) /* Controls whether user wants to quit. */
			if(x == 'q' || x == 'Q') /* If one of the character of the string is 'q' or 'Q', user wants to quit. */
				quitcontrol = 1;
		if(xcoordinate >= 0 && xcoordinate < board.size() && ycoordinate >= 0 && ycoordinate < board.size()){
			switch(direction){
				 case 'R': /* If direction is right, moves right. */
					 board = move_right(board, xcoordinate, ycoordinate);
					 break;
				 case 'L': /* If direction is left, moves left. */
					 board = move_left(board, xcoordinate, ycoordinate);
					 break;
				 case 'U': /* If direction is up, moves up. */
					 board = move_up(board, xcoordinate, ycoordinate);
					 break;
				 case 'D': /* If direction is down, moves down. */
					 board = move_down(board, xcoordinate, ycoordinate);
					 break;
			}
		}
	}

	show_results(board, board.size()); /* At the end of the loop, shows results of the game. */
}

void get_user_move_2(vector <vector<state>> board){
	string movement;
	char direction;
	int xcoordinate, ycoordinate, quitcontrol = 0, random_direction;
	vector <vector<state>> oldboard;
	srand(time(NULL));
	while(control_board(board, board.size()) != 1 && quitcontrol == 0){ /* Checks whether the game is completed or not, checks whether user wants to quit or not. */
		oldboard = board; /* Temp vector to compare the vector is changed or not. */
		direction = '0'; /* To get rid of garbage value. */
		cout << "Enter your move (like B4-R, enter 'q' to quit): ";
		cin >> movement;

		if(movement.size() == 4){ /* If the size of string is not equals to 4, there must be a mistake. */
			ycoordinate = movement[0]-'A'; /* Get numeric value of y coordinate. */
			xcoordinate = (movement[1]-'1')*2;  /* Get numeric value of x coordinate. */
			direction = movement[3];
		}

		for(char x : movement) /* Controls whether user wants to quit. */
			if(x == 'q' || x == 'Q') /* If one of the character of the string is 'q' or 'Q', user wants to quit. */
				quitcontrol = 1; 
		if(xcoordinate >= 0 && xcoordinate < board.size() && ycoordinate >= 0 && ycoordinate < board.size()){

			switch(direction){
				case 'R': /* If direction is right, moves right. */
					board = move_right_2(board, xcoordinate, ycoordinate);
					break;
				case 'L': /* If direction is left, moves left. */
					board = move_left_2(board, xcoordinate, ycoordinate);
					break;
				case 'U':
				 	random_direction = random()%2; /* Produce a random value to decide up and right or up and left. */
				 	if(random_direction == 0){ /* If the random value is 0, first try to move up and right. */
					 	board = move_up_right(board, xcoordinate, ycoordinate); 
					 	if(is_change(oldboard, board, board.size()) == 0) /* If move up and right movement is not legal, try move up and left. */
					 		board = move_up_left(board, xcoordinate, ycoordinate);
					}
					else{ /* If the random value is 1, try to move up and left. */
						board = move_up_left(board, xcoordinate, ycoordinate); 
						if(is_change(oldboard, board, board.size()) == 0) /* If move up and left movement is not legal, try move up and right. */
					 		board = move_up_right(board, xcoordinate, ycoordinate); 
					}
					break;
				case 'D':
					random_direction = random()%2; /* Produce a random value to decide down and right or down and left. */
				 	if(random_direction == 0){ /* If the random value is 0, first try to move down and right. */
					 	board = move_down_right(board, xcoordinate, ycoordinate);
					 	if(is_change(oldboard, board, board.size()) == 0) /* If move down and right movement is not legal, try move down and left. */
					 		board = move_down_left(board, xcoordinate, ycoordinate);
					}
					else{ /* If the random value is 1, try to move down and left. */
						board = move_down_left(board, xcoordinate, ycoordinate);
						if(is_change(oldboard, board, board.size()) == 0) /* If move down and left movement is not legal, try move down and right. */
					 		board = move_down_right(board, xcoordinate, ycoordinate);
					}
				break;
			}
		}
	}

	show_results(board, board.size()); /* Shows the results. */
}

/* ----------------------------------------------------------------------------------- */

int is_change(vector <vector<state>> oldboard, vector <vector<state>> newboard, int boardsize){
	int is_changed = 0, differences = 0;
	for(int i = 0; i < boardsize; ++i){
		for(int j = 0; j < boardsize ; ++j){
			if(oldboard[i][j] != newboard[i][j]) /* Compares old and new board, and there is a difference, increases the differences variable. */
				differences++;
		}
	}
	if(differences > 0) /* If differences is bigger than 0, it is changed. */
		is_changed = 1;

	return is_changed;
}

/* ----------------------------------------------------------------------------------- */

int empty_cells(vector <vector<state>> board, int boardsize){
	int number_of_empty = 0;
	for(int i = 0; i < boardsize; ++i){
		for(int j = 0; j < boardsize ; ++j){
			if(board[i][j] == state::EMPTY) /* Counters the empty cells on the board. */
				number_of_empty++;
		}
	}

	return number_of_empty;
}

/* ----------------------------------------------------------------------------------- */

void solve_puzzle(vector <vector<state>> board, int boardsize){
	int number_of_empty, rank, cell = 0, xcoordinate, ycoordinate, is_changed = 0, j, random_direction, random_index;

	vector <vector<state>> oldboard = board; /* Creates a vector to compares the vectors. */

	int direction[4] = {1,2,3,4};

	number_of_empty = empty_cells(board, boardsize); /* Calculates empty cells on the board. */

	srand(time(NULL));

	for(int i = 0; i <= number_of_empty && is_changed == 0; ++i){ /* Try as many empty cells, if there is no change on the board. */
		cell = 0;

		rank = random()%number_of_empty + 1; /* Produce a value to find which space must used. */

		for(xcoordinate = 0; xcoordinate < boardsize && cell != rank; xcoordinate++){ /* Finds empty cell which has that rank */
			for(ycoordinate = 0; ycoordinate < boardsize && cell != rank; ycoordinate++){
				if(board[xcoordinate][ycoordinate] == state::EMPTY){
					cell++;
				}
			}	
		}
		xcoordinate -=1; /* Takes x coordinate of empty cell. */
		ycoordinate -=1; /* Takes y coordinate of empty cell. */

		for(int attempts = 0; attempts < 4 && is_changed == 0; attempts++){ /* Try every direction until it moves. */
			do{
				random_index = random()%4;
				random_direction = direction[random_index];
			}while(random_direction == 0);
			direction[random_index] = 0; /* Makes the current direction 0 to get rid of try same direction again. */

			switch(random_direction){
				case 1: /* If direction is right, move right. */
					if(ycoordinate >= 2) /* To get rid of minus y coordinate. */
						board = move_right(board, xcoordinate, ycoordinate-2);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 2: /* If direction is left, move left. */
					if(ycoordinate+2 < boardsize) /* To avoid to exceed the border of the vector. */
						board = move_left(board, xcoordinate, ycoordinate+2);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 3: /* If direction is down, move down. */
					if(xcoordinate >= 2) /* To get rid of minus x coordinate. */
						board = move_down(board, xcoordinate-2, ycoordinate);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 4: /* If direction is up, move up. */
					if(xcoordinate+2 < boardsize) /* To avoid to exceed the border of the vector. */
						board = move_up(board, xcoordinate+2, ycoordinate);
					is_changed = is_change(oldboard, board, boardsize);
					break;
			}
		}
		
		for(int x = 0; x < 4; x++) /* Resets the direction array. */
			direction[x] = x+1;
		
		
	}

	if(is_changed == 1) /* If the puzzle is changed, continue. */
		solve_puzzle(board, boardsize);
	
	else /* Otherwise shows results. */
		show_results(board, boardsize); 

}

void solve_puzzle_2(vector <vector<state>> board, int boardsize){
	int number_of_empty, rank, cell = 0, xcoordinate, ycoordinate, is_changed = 0, j, random_direction, random_index;

	vector <vector<state>> oldboard = board; /* Creates a vector to compares the vectors. */

	int direction[6] = {1,2,3,4,5,6};

	number_of_empty = empty_cells(board, boardsize); /* Calculates empty cells on the board. */

	srand(time(NULL));

	for(int i = 0; i <= number_of_empty && is_changed == 0; ++i){ /* Try as many empty cells, if there is no change on the board. */
		cell = 0;

		rank = random()%number_of_empty + 1; /* Produce a value to find which space must used. */

		for(xcoordinate = 0; xcoordinate < boardsize && cell != rank; xcoordinate++){ /* Finds empty cell which has that rank */
			for(ycoordinate = 0; ycoordinate < boardsize && cell != rank; ycoordinate++){
				if(board[xcoordinate][ycoordinate] == state::EMPTY){
					cell++;
				}
			}	
		}
		xcoordinate -=1; /* Takes x coordinate of empty cell. */
		ycoordinate -=1; /* Takes y coordinate of empty cell. */

		for(int attempts = 0; attempts < 6 && is_changed == 0; attempts++){ /* Try every direction until it moves. */
			do{
				random_index = random()%6;
				random_direction = direction[random_index];
			}while(random_direction == 0);
			direction[random_index] = 0; /* Makes the current direction 0 to get rid of try same direction again. */

			switch(random_direction){
				case 1: /* If direction is right, move right. */
					if(ycoordinate >= 4) /* To avoid to exceed the border of the vector. */
						board = move_right_2(board, xcoordinate, ycoordinate-4);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 2: /* If direction is left, move left. */
					if(ycoordinate+4 < boardsize) /* To avoid to exceed the border of the vector. */
						board = move_left_2(board, xcoordinate, ycoordinate+4);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 3: /* If direction is down and right, move down and right. */
					if(xcoordinate >= 4 && ycoordinate >= 2) /* To avoid to exceed the border of the vector. */
						board = move_down_right(board, xcoordinate-4, ycoordinate-2);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 4: /* If direction is down and left, move down and left. */
					if(xcoordinate >= 4 && ycoordinate+2 < boardsize) /* To avoid to exceed the border of the vector. */
						board = move_down_left(board, xcoordinate-4, ycoordinate+2);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 5: /* If direction is up and right, move up and right. */
					if(xcoordinate+4 < boardsize && ycoordinate >= 2) /* To avoid to exceed the border of the vector. */
						board = move_up_right(board, xcoordinate+4, ycoordinate-2);
					is_changed = is_change(oldboard, board, boardsize);
					break;
				case 6: /* If direction is up and left, move up and left. */
					if(xcoordinate+4 < boardsize && ycoordinate+2 < boardsize) /* To avoid to exceed the border of the vector. */
						board = move_up_left(board, xcoordinate+4, ycoordinate+2);
					is_changed = is_change(oldboard, board, boardsize);
					break;
			}
		}
		
		for(int x = 0; x < 6; x++) /* Resets the direction array. */
			direction[x] = x+1;
		
	}

	if(is_changed == 1) /* If the puzzle is changed, continue. */
		solve_puzzle_2(board, boardsize);
	
	else /* Otherwise shows the results. */
		show_results(board, boardsize);

}

/* ---------------------------------- state::PEG MOVE FUNCTİONS -------------------------------- */

vector <vector<state>> move_right(vector <vector<state>> board, int x, int y){
	if(board[x][y+1] == state::PEG && board[x][y+2] == state::EMPTY && board[x][y] == state::PEG){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state::EMPTY;
		board[x][y+1] = state::EMPTY;
		board[x][y+2] = state::PEG;
		show_board(board, board.size());
	}
	return board;
}

vector <vector<state>> move_left(vector <vector<state>> board, int x, int y){
	if(board[x][y-1] == state::PEG && board[x][y-2] == state::EMPTY && board[x][y] == state::PEG){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state::EMPTY;
		board[x][y-1] = state::EMPTY;
		board[x][y-2] = state::PEG;
		show_board(board, board.size());
	}
	return board;
}

vector <vector<state>> move_down(vector <vector<state>> board, int x, int y){
	if(board[x+1][y] == state::PEG && board[x+2][y] == state::EMPTY  && board[x][y] == state::PEG){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state::EMPTY;
		board[x+1][y] = state::EMPTY;
		board[x+2][y] = state::PEG;
		show_board(board, board.size());
	}
	return board;
}

vector <vector<state>> move_up(vector <vector<state>> board, int x, int y){
	if(board[x-1][y] == state::PEG && board[x-2][y] == state::EMPTY  && board[x][y] == state::PEG){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state::EMPTY;
		board[x-1][y] = state::EMPTY;
		board[x-2][y] = state::PEG;
		show_board(board, board.size());
	}
	return board;
}

vector <vector<state>> move_right_2(vector <vector<state>> board, int x, int y){
	if(board[x][y] == state::PEG && board[x][y+2] == state:: PEG && board[x][y+4] == state:: EMPTY){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state:: EMPTY;
		board[x][y+2] = state:: EMPTY;
		board[x][y+4] = state:: PEG;
		show_board_2(board, board.size());
	}
	return board;
}

vector <vector<state>> move_left_2(vector <vector<state>> board, int x, int y){
	if(board[x][y] == state::PEG && board[x][y-2] == state:: PEG && board[x][y-4] == state:: EMPTY){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state:: EMPTY;
		board[x][y-2] = state:: EMPTY;
		board[x][y-4] = state:: PEG;
		show_board_2(board, board.size());
	}
	return board;
}

vector <vector<state>> move_down_right(vector <vector<state>> board, int x, int y){
	if(board[x][y] == state::PEG && board[x+2][y+1] == state:: PEG && board[x+4][y+2] == state:: EMPTY){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state:: EMPTY;
		board[x+2][y+1] = state:: EMPTY;
		board[x+4][y+2] = state:: PEG;
		show_board_2(board, board.size());
	}
	return board;
}
vector <vector<state>> move_down_left(vector <vector<state>> board, int x, int y){
	if(board[x][y] == state::PEG && board[x+2][y-1] == state:: PEG && board[x+4][y-2] == state:: EMPTY){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state:: EMPTY;
		board[x+2][y-1] = state:: EMPTY;
		board[x+4][y-2] = state:: PEG;
		show_board_2(board, board.size());
	}
	return board;
}

vector <vector<state>> move_up_right(vector <vector<state>> board, int x, int y){
	if(board[x][y] == state::PEG && board[x-2][y+1] == state:: PEG && board[x-4][y+2] == state:: EMPTY){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state:: EMPTY;
		board[x-2][y+1] = state:: EMPTY;
		board[x-4][y+2] = state:: PEG;
		show_board_2(board, board.size());
	}
return board;
}
vector <vector<state>> move_up_left(vector <vector<state>> board, int x, int y){
	if(board[x][y] == state::PEG && board[x-2][y-1] == state:: PEG && board[x-4][y-2] == state:: EMPTY){ /* Moves the pegs if it satisfies the rule. */
		board[x][y] = state:: EMPTY;
		board[x-2][y-1] = state:: EMPTY;
		board[x-4][y-2] = state:: PEG;
		show_board_2(board, board.size());
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
		{state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL},
		{state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL},
		{state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL, state::WALL},
		{state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG, state::WALL, state::PEG}
	};
	return board;
}


/* ----------------------------------------------------------------------------------- */
