#include <iostream>
#include <vector>
#include "hw2_lib.h"
using namespace std;

/* While computer is playing the peg game, Enter must be pressed at every step. */
/* Instead of entering board type, the user can use LOAD function. */
/* There is just SAVE option in the solve_puzzle and get_user_move function. In solve_puzzle function, save command can be entered instead of pressing Enter. */
/* In get_user_move function, SAVE command can be entered instead of input of movement. */

int main(){

	vector <vector<state>> board;

	vector <vector<state>> oldboard;

	int board_type = -1, human_player = 0;

	char file_opr[256];

	decltype (1 > 0) opr_completed;

	string operation;

	do{
		opr_completed = false;

		board_type = -1; 

		cout << "Please enter the board type (1-6, -1 to quit): ";
		
		cin.getline(file_opr, 256); /* Gets board type or file operation. */

		operation = file_opr;

		if(operation.size() == 1) /* If the size of input is one, it it board type. */
			board_type = operation[0]-'0';
		else /* If the size of input is not 1, it is file operation. */
			if(operation.compare(0, 4, "LOAD") == 0) /* Controls is it load operation or not. */
				board = LOAD(board, &file_opr[5], &opr_completed, &board_type); /* Load the board from the file. */

		if(opr_completed == false){ /* If file operation is not completed, continue. */
			board.clear(); /* Clears the board. */

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
					cerr << "The program will be terminated...";
					exit(-1);
			}
		}
		if(board_type > 0){
			cout << "Is it a human player(1 for yes,0 for no): ";
			cin >> human_player; 

			cin.get();

			show_board(board); /* Shows board first. */

			switch(human_player){ /* Selects the user. */
				case 0:
					solve_puzzle(board, board_type); /* Solves puzzle then. */
					break;
				case 1:
					get_user_move(board, board_type); /* Gets movements from user. */
					break;
				default:
					cerr << "The program will be terminated...";
					exit(-2);
			}
		}
	}while(board_type > 0 && board_type < 7 && human_player >= 0 && human_player < 2);

	return 0;
}
