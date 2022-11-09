#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "BoardGame2D.h"
#include "PegSolitaire.h"
#include "EightPuzzle.h"
#include "Klotski.h"

using namespace std;
using namespace Base;
using namespace derived_peg;
using namespace derived_puzzle;
using namespace derived_klotski;

namespace derived_peg{ /* Namespace for PegSolitaire. */
	/* Constructor for PegSolitaire class. */
	PegSolitaire::PegSolitaire(){ /* Clears the pegBoard vector and calls initialize function. */
		pegBoard.clear();
		initialize();
	}

	/* -------------------------------------------------------------------------------------------- */

	void PegSolitaire::initialize(){ /* Initializes the board manually. */
		pegBoard = {
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
	}

	/* -------------------------------------------------------------------------------------------- */

	void PegSolitaire::print(){ /* Prints the board. */
		char col = 'A';
		int row_num = 1;
		cout << "\033[2J\033[1;1H"; /* Clears the terminal. */
		cout << endl << " ";
		for(long unsigned int i = 0; i < pegBoard.size(); i++){ /* Prints number at the beginning of the rows. */
			cout << " " << col++;
		}
		cout << endl;
		for(auto& row: pegBoard){
			cout << row_num++; /* Prints letters at the beginning of the coloumns. */
			for(auto col: row){
				if(col == state::PEG){
					cout << " P";
				}
				else if(col == state::EMPTY){
					cout << " .";
				}
				else
					cout << "  ";
			}
			cout << endl;
		}
	}

	/* -------------------------------------------------------------------------------------------- */

	bool PegSolitaire::playAuto(mode movement){ /* Plays the board automatically. */
		int x_coor, y_coor, direction, size = pegBoard.size();

		bool success = false;

		vector <vector<int>> all_empty_coor = empty_cell_coor(); /* Gets the cells coordinates which are empty and keeps them in a vector. */

		for(long unsigned int i = 0; i < all_empty_coor.size() && success == false; i++){ /* Try to moves all empty cells. */
			empty_coor(x_coor, y_coor, all_empty_coor); /* Gets coordinates of one of the empty cells and keeps coordinates in x_coor and y_coor variables. */

			vector <int> all_directions = {1, 2, 3, 4}; /* Directions vector. */

			for(long unsigned int j = 0; j < all_directions.size() && success == false; j++){ /* Try to moves empty cells in any direction. */
				find_direction(direction, all_directions); /* Gets direction. */

				switch(direction){
					case 1:
						if(x_coor > 1) /* To avoid segmentation fault. */
							success = move(x_coor-2, y_coor, movement, 0, 1);
						break;
					case 2:
						if(x_coor+2 < size) /* To avoid segmentation fault. */
							success = move(x_coor+2, y_coor, movement, 0, -1);
						break;
					case 3:
						if(y_coor > 1) /* To avoid segmentation fault. */
							success = move(x_coor, y_coor-2, movement, 1, 0);
						break;
					case 4:
						if(y_coor+2 < size) /* To avoid segmentation fault. */
							success = move(x_coor, y_coor+2, movement, -1, 0);
						break;
				}
			}
		}
		if(success == true && movement == mode::MOVE){ /* If cell can move, and this is not simulation, prints the board. */
			print();
		}
		return success;
	}

	/* -------------------------------------------------------------------------------------------- */

	bool PegSolitaire::playUser(string input){ /* Gets the input and makes a move on input. */
		vector <string> directions = {"UP", "DOWN", "RIGHT", "LEFT"}; /* Creates a directions vector. */
		int direction = -1, size = pegBoard.size();
		bool success = false;
		mode movement = mode::MOVE;
		for(long unsigned int i = 0; i < directions.size(); i++){
			if(input.size() > 3){
				if(input.compare(3, directions[i].size(), directions[i]) == 0){ /* Compares the input with one of the element of directions vector, */
					direction = i;												  /* if they are equal, gets the direction. */
				}
			}
		}
		if(input.size() > 1){ /* To avoid segmentation fault. */
			int y_coor = input[0]- '1'; /* Gets coordinates. */
			int x_coor = input[1] - 'A'; /* Gets coordinates. */
			if(-1 < direction && direction < 4){ /* If direction is between -1 and 4, continue. */
				if(0 <= y_coor && y_coor < size && 0 <= x_coor && x_coor < size){ /* To avoid segmentation fault. */
					switch(direction){
						case 0:
							success = move(x_coor, y_coor, movement, -1 , 0);
							break;
						case 1:
							success = move(x_coor, y_coor, movement, 1 , 0);
							break;
						case 2:
							success = move(x_coor, y_coor, movement, 0 , 1);
							break;
						case 3:
							success = move(x_coor, y_coor, movement, 0 , -1);
							break;
					}	
				}
			}
		}
		if(success == true)
			print();
		else
			cerr << "The coordinates or movement is not legal." << endl;
		return success;
	}

	/* -------------------------------------------------------------------------------------------- */

	int PegSolitaire::boardScore(){ /* Calculates the score of the board. */
		int size = pegBoard.size();
		int score = 0;
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(pegBoard[i][j] == state::PEG) /* If the cell is a peg, increases the score. */
					score++;
			}
		}
		if(score == 1) /* If the score is one, returns 0. */
			score = 0;
		return score;
	}

	/* -------------------------------------------------------------------------------------------- */

	vector <vector<int>> PegSolitaire::empty_cell_coor() const{ /* Finds empty cells on the board, and keep their coordinates in a vector. */
		int boardSize = pegBoard.size();
		vector <int> x_y_coor; /* Creates 1D vector. */
		vector <vector<int>> all_coor; /* Creates 2D vector. */
		for(int row = 0; row < boardSize; row++){
			for(int col = 0; col < boardSize; col++){
				x_y_coor.clear(); /* Clears the 1D vector. */
				if(pegBoard[row][col] == state::EMPTY){ /* Finds empty cells. */
					x_y_coor.push_back(col); /* Puts the coloumn value into 1D vector. */
					x_y_coor.push_back(row); /* Puts the row value into 1D vector. */
					all_coor.push_back(x_y_coor); /* Puts the 1D vector into 2D vector. */
				}
			}
		}
		return all_coor; /* Returns 2D vector. */
	}

	/* -------------------------------------------------------------------------------------------- */

	void PegSolitaire::empty_coor(int& x_coor, int& y_coor, vector<vector<int>>& all_empty_coor){ /* Gets a vector which has coordinates of all empty cells as a parameter, */
		int random, rank;																			/* selects one of empty cell randomly, and puts its coordinates into x_coor and y_coor variables. */
		do{
			random = rand()%all_empty_coor.size();
			x_coor = all_empty_coor[random][0];
			y_coor = all_empty_coor[random][1];
			rank = random;
		}while(x_coor < 0 || y_coor < 0);

		all_empty_coor[rank][0] = -1; /* Makes it -1 to avoid repetititon. */
		all_empty_coor[rank][1] = -1; /* Makes it -1 to avoid repetititon. */
	}

	/* -------------------------------------------------------------------------------------------- */

	void PegSolitaire::find_direction(int& direction, vector<int>& all_directions){ /* Gets a vector which has directions as a parameter, selects one of direction and puts into direction variable. */
		int random, rank;
		do{
			random = rand()%all_directions.size();
			direction = all_directions[random];
			rank = random;
		}while(4 < direction || direction < 1);

		all_directions[rank] = -1; /* Makes it -1 to avoid repetititon. */
	}

	/* -------------------------------------------------------------------------------------------- */

	bool PegSolitaire::move(int x_coor, int y_coor, mode movement, int vertical, int horizontal){ /* Gets coordinates of cell as a parameter, gets the direction(vertical, horizontal), */
		bool success = false;																		/* if mode is MOVE, makes that move. */
		if(-1 < y_coor + vertical && y_coor + vertical < 9 && -1 < x_coor + horizontal && x_coor + horizontal < 9){
			if(pegBoard[y_coor][x_coor] == state::PEG){ /* If the the cell is PEG. */
				if(pegBoard[y_coor + vertical][x_coor + horizontal] == state::PEG){ /* If one unit side(right, left, down, up) of it also PEG. */
					if(pegBoard[y_coor + (2 * vertical)][x_coor +(2 * horizontal)] == state::EMPTY){ /* If two unit side(right, left, down, up) of it also EMPTY. */
						success = true;
						if(movement == mode::MOVE){ /* If mode is move, makes that move. */
							pegBoard[y_coor][x_coor] = state::EMPTY;
							pegBoard[y_coor + vertical][x_coor + horizontal] = state::EMPTY;
							pegBoard[y_coor + (2 * vertical)][x_coor + (2 * horizontal)] = state::PEG;
						}
					}	
				}
			}
		}
		return success;
	}
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
namespace derived_puzzle{ /* Namespace for EightPuzzle. */
	/* Constructor for EightPuzzle. */
	EightPuzzle::EightPuzzle(){
		puzzleBoard.clear();
		initialize();
	}

	/* -------------------------------------------------------------------------------------------- */

	void EightPuzzle::initialize(){ /* Initializes the board randomly. */
		vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 0};
		vector<vector<int>> new_version; /* Creates 2D vector. */
		vector<int> row; /* Creates 1D vector. */
		int rank, random_number; 
		for(int i = 0; i < 3; i++){
			row.clear();
			for(int j = 0; j < 3; j++){
				do{
					rank = rand()%9;
					random_number = numbers[rank]; /* Gets randomly a number from numbers vector. */
				}while(random_number == -1);

				numbers[rank] = -1;
				row.push_back(random_number); /* Put random number into row. */
			}
			new_version.push_back(row); /* Put 1D vector into 2D vector. */
		}
		puzzleBoard = new_version; /* Assigns 2D vector to PegSolitaire board. */
	}

	/* -------------------------------------------------------------------------------------------- */

	void EightPuzzle::print(){ /* Prints the PegSolitaire board. */
		int size = puzzleBoard.size();
		cout << "\033[2J\033[1;1H"; /* Clears the terminal. */
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				cout << "|_" << puzzleBoard[i][j] << "_|";
			}
			cout << endl;
		}
	}

	/* -------------------------------------------------------------------------------------------- */

	void EightPuzzle::find_target(int target, int& x_coor, int& y_coor){ /* Gets a target, finds it location and assigns it to x and y coordinates. */
		int size = puzzleBoard.size();
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(puzzleBoard[i][j] == target){ /* If the cell is target, gets its coordinates. */
					x_coor = j;
					y_coor = i;
				}
			}
		}
	}

	/* -------------------------------------------------------------------------------------------- */

	bool EightPuzzle::shift(int vertical, int horizontal, mode movement){ /* Moves the cell to any direction. */
		int x_coor, y_coor;
		vector<vector<int>> temp = puzzleBoard; /* Creates a temp variable to keep PegSolitaire board.*/
		find_target(0, x_coor, y_coor); /* Finds the location of empty cell. */
		bool valid = false;
		if(0 <= x_coor + horizontal && x_coor + horizontal < 3){ /* To avoid segmentation fault. */
			if(0 <= y_coor + vertical && y_coor + vertical < 3){ /* To avoid segmentation fault. */
				/* Makes the move. */
				puzzleBoard[y_coor][x_coor] = puzzleBoard[y_coor + vertical][x_coor + horizontal]; 
				puzzleBoard[y_coor + vertical][x_coor + horizontal] = 0;
				valid = true;
			}
		}
		if(movement == mode::SIMULATE) /* If the mode is simulate, restore the board. */
			puzzleBoard = temp;
		return valid;
	}

	/* -------------------------------------------------------------------------------------------- */

	int EightPuzzle::boardScore(){ /* Calculates the score of the board. */
		vector<vector<int>> normal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}; /* Creates a 2D vector which is solution. */
		int difference = 0;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(puzzleBoard[i][j] != normal[i][j]) /* Compares the current board with solution, and calculates the difference. */
					difference++;
			}
		}
		return difference;
	}

	/* -------------------------------------------------------------------------------------------- */

	bool EightPuzzle::is_solveable(){ /* Test the board is solveable or not. (If the size of the board is odd, number of inversion should be even to board be solveable.) */
		bool solveable;
		int inversion = 0;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				int l = j+1;
				for(int k = i; k < 3; k++){
					for(; l < 3; l++){
						if(puzzleBoard[i][j] > puzzleBoard[k][l] && puzzleBoard[k][l] != 0 && puzzleBoard[i][j] != 0) /* Calculates inversion. (Do not count empty cell.) */
							inversion += 1;
					}
					l = 0;
				}
			}
		}
		if(inversion % 2 == 0)
			solveable = true;
		else
			solveable = false;
		return solveable;
	}

	/* -------------------------------------------------------------------------------------------- */

	void EightPuzzle::simulate(mode movement){ /* Simulates the movement. */
		vector<int> directionsVec = {0, 1, 2, 3}; /* Creates a direction vector. */
		int rank, direction;
		bool valid = false;;
		do{
			rank = rand()%directionsVec.size(); /* Gets random direction. */
			direction = directionsVec[rank];
			switch(direction){
				case 0:
					valid = shift(1, 0, movement);
					break;
				case 1:
					valid = shift(-1, 0, movement);
					break;
				case 2:
					valid = shift(0, 1, movement);
					break;
				case 3:
					valid = shift(0, -1, movement);
					break;
			}
		}while(valid == false);
	}

	/* -------------------------------------------------------------------------------------------- */

	bool EightPuzzle::playAuto(mode movement){ /* Plays the board automatically. */
		bool success = false;
		if(boardScore() != 0 && is_solveable()){ /* If the game is not over and is solveable, continue. */
			simulate(movement); /* Simulate movement. */
			if(movement == mode::MOVE)
				print();
			success = true;
		}
		else if(is_solveable() == false){ /* If the game is not solveable, prints an error message. */
			cerr << "The board can't never be solved." << endl;
		}
		return success;
	}

	/* -------------------------------------------------------------------------------------------- */

	bool EightPuzzle::playUser(string input){ /* Gets input from the user and makes the move on input. */
		vector <string> directions = {"UP", "DOWN", "RIGHT", "LEFT"}; /* Creates a directions vector. */
		int direction = -1 ; /* Assigns direction to -1, to avoid garbage value. */
		bool success = false;
		mode movement = mode::MOVE;
		for(long unsigned int i = 0; i < directions.size(); i++){
			if(input.size() > 0){
				if(input.compare(0, directions[i].size(), directions[i]) == 0){ /* Gets the direction. */
					direction = i;
				}
			}
		}
		if(-1 < direction && direction < 4){ /* Makes a move according to direction. */
			switch(direction){
				case 0:
					success = shift(-1, 0, movement);
					break;
				case 1:
					success = shift(1, 0, movement);
					break;
				case 2:
					success = shift(0, 1, movement);
					break;
				case 3:
					success = shift(0, -1, movement);
					break;
			}	
		}
		if(success == true)
			print();
		else
			cerr << "The movement is not legal." << endl;
		return success;
	}
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

namespace derived_klotski{ /* Namespace for Klotski. */
	/* Constructor for Klotski. */
	Klotski::Klotski(){
		initialize();
	}

	/* -------------------------------------------------------------------------------------------- */

	void Klotski::initialize(){ /* Initializes the board manually. */
		/* Same letters present same brick. */
		vector <vector<char>> temp = {{'A', 'B', 'B', 'C'}, {'A', 'B', 'B', 'C'}, {'D', 'E', 'E', 'F'}, {'D', 'G', 'H', 'F'}, {'I', ' ', ' ', 'J'}};
		klotskiBoard = temp;
	}

	/* -------------------------------------------------------------------------------------------- */

	void Klotski::print(){ /* Prints the board. */
		cout << "\033[2J\033[1;1H"; /* Clears the terminal. */
		for(auto row: klotskiBoard){
			for(auto y: row){
				cout << " " << y; /* Print the letters. */
			}
			cout << endl;
		}
	}

	/* -------------------------------------------------------------------------------------------- */

	int Klotski::sizeBrick(char target){ /* Calculates the size of the brick(A brick 2 size, B brick 4 size, G brick 1 size). */
		int size = 0;
		for(auto row: klotskiBoard){
			for(auto y: row){
				if(y == target)
					size++;
			}
		}
		return size;
	}

	/* -------------------------------------------------------------------------------------------- */

	bool Klotski::shift(char target, int vertical, int horizontal, mode movement){ /* Gets the name of the brick and direction as parameters and moves the bricks. */
		vector <vector<char>> temp = klotskiBoard; /* Creates a 2D vector to keep KlotskiBoard. */
		bool valid = false;
		int brickSize = sizeBrick(target); /* Calculates size of the brick. */
		int moveNumber = 0; /* To provide all parts of the brick move together. */
		for(int repetition = 0; repetition < brickSize; repetition++){
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 4; j++){
					if(temp[i][j] == target && klotskiBoard[i][j] == target){ /* If the cell is same brick in first and last boards, makes the move. */
						if(-1 < i + vertical && i + vertical < 5 && -1 < j + horizontal && j + horizontal < 4){ /* To avoid segmentation fault. */
							if(temp[i+vertical][j+horizontal] == ' '){ /* If the cell is empty, makes the move. */
								temp[i+vertical][j+horizontal] = temp[i][j];
								temp[i][j] = ' ';
								moveNumber++; /* Increases number of moves. */
							}
						}
					}
				}
			}
		}
		if(moveNumber == brickSize) /* If the number of moves is equal to what it should be, the movement is valid. */
			valid = true;
		if(movement == mode::MOVE && valid == true) /* If the function is move mode and the movement is valid, assigns temp to klotskiBoard. */
			klotskiBoard = temp;
		return valid;
	}

	/* -------------------------------------------------------------------------------------------- */

	bool Klotski::playUser(string input){ /* Gets an input from the user, and makes a move. */
		vector <string> directions = {"UP", "DOWN", "RIGHT", "LEFT"}; /* Creates a directions vector. */
		int direction = -1; /* To avoid garbage value. */
		bool success = false;
		mode movement = mode::MOVE;
		for(long unsigned int i = 0; i < directions.size(); i++){
			if(input.size() > 2){
				if(input.compare(2, directions[i].size(), directions[i]) == 0){ /* Compares the input with direction, and gets the direction. */
					direction = i;
				}
			}
		}
		if(input.size() > 0){
			char target = input[0]; /* Gets the target bricks. */
			if(-1 < direction && direction < 4){ /* If direction is in between -1 and 4, continue. */
				if('A' <= target && target <= 'K'){ /* If the target is between A letter and K letter, continue. */
					switch(direction){
						case 0:
							success = shift(target, -1, 0, movement);
							break;
						case 1:
							success = shift(target, 1, 0, movement);
							break;
						case 2:
							success = shift(target, 0, 1, movement);
							break;
						case 3:
							success = shift(target, 0, -1, movement);
							break;
					}	
				}
			}
		}
		if(success == true)
			print();
		else /* If the coordinates or movement is not legal print an error message. */
			cerr << "The coordinates or movement is not legal." << endl;
		return success;
	}	

	/* -------------------------------------------------------------------------------------------- */

	bool Klotski::playAuto(mode movement){ /* Plays the board automatically. */
		int rank, direction;
		char target;
		vector<char> targetVec = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}; /* Creates a vector which keeps bricks letters. */
		bool success = false, solved = false;

		if(klotskiBoard[4][1] == 'B' && klotskiBoard[4][2] == 'B') /* If the state is final state, the puzzle is already solved. */
			solved = true;

		for(int i = 0; i < 10 && success == false && solved == false; i++){ /* Try every brick until it moves. */
			vector<int> directionsVec = {0, 1, 2, 3}; /* Creates a direction vector. */

			do{
				rank = rand()%10;
				target = targetVec[rank]; /* Gets a random brick. */
			}while(target < 0);
			targetVec[rank] = -1;


			for(int attempt = 0; attempt < 4 && success == false; attempt++){ /* Try every direction until it moves. */
				do{
					rank = rand()%4;
					direction = directionsVec[rank]; /* Gets a random direction. */
				}while(direction == -1);
				directionsVec[rank] = -1;

				switch(direction){
					case 0:
						success = shift(target, -1, 0, movement);
						break;
					case 1:
						success = shift(target, 1, 0, movement);
						break;
					case 2:
						success = shift(target, 0, 1, movement);
						break;
					case 3:
						success = shift(target, 0, -1, movement);
						break;	
				}
			}
		}
		if(success == true && movement == mode::MOVE){ /* If the movement is succesfull and the function is move mode, print. */
			print();
		}
		return success;
	}

	/* -------------------------------------------------------------------------------------------- */

	int Klotski::boardScore(){ /* Calculates score of the board. */
		/* Calculates the distance from first position of B brick to final position of B brick. */
		int x_coor, y_coor, distance = 0;
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 4; j++){
				if(klotskiBoard[i][j] == 'B'){
					y_coor = i;
					x_coor = j;
				}
			}
		}
		if(x_coor - 2 < 0)
			distance += 2 - x_coor;
		else
			distance += 2 - x_coor;
		if(y_coor - 4 < 0)
			distance += 4 - y_coor;
		else
			distance += y_coor - 4;
		return distance;

	}
}

