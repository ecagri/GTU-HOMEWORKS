#include <iostream>
#include <vector>
#include "hw1_lib.h"
using namespace std;

int main(){

	vector <vector<state>> board;

	int board_type  = 0, human_player = 0;

	cout << "Please enter the board type (1-6, -1 for quit): ";
	cin >> board_type;

	switch(board_type){ /* Selects board type. */
		case 1:	
			board = board_type_1();
			break;
		case 2:
			board = board_type_2();
			break;
		case 3:
			board = board_type_3();
			break;
		case 4:	
			board = board_type_4();
			break;
		case 5:
			board = board_type_5();
			break;
		case 6:
			board = board_type_6();
			break;
		default:
			cout << "The program will be terminated...";
			exit(-1);
	}

	cout << "Is it a human player(1 for yes,0 for no): ";
	cin >> human_player;



	switch(human_player){ /* Selects the user. */
		case 0:
			if(board_type != 6){ /* If board type is not 6, applies standard procedure. */
				show_board(board, board.size()); /* Shows board first. */

				solve_puzzle(board, board.size()); /* Solves puzzle then. */
			}
			else{ /* Applies special procedure for type 6 board. */
				show_board_2(board, board.size()); /* Shows board first. */

				solve_puzzle_2(board, board.size()); /* Solves puzzle then. */
			}
			break;
		case 1:
			if(board_type != 6){ /* If board type is not 6, applies standard procedure. */
				show_board(board, board.size()); /* Shows board first. */

				get_user_move(board); /* Gets movements from user. */
			}
			else{ /* Applies special procedure for type 6 board. */
				show_board_2(board, board.size()); /* Shows board first. */

				get_user_move_2(board); /* Gets movements from user. */
			}

			break;
		default:
			cout << "The program will be terminated...";
			exit(-2);
	}

	return 0;
}