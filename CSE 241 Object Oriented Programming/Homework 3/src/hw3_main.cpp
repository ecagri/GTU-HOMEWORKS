#include "hw3_lib.h"
#include <vector>
using namespace std;

/* My program is not working for type 6 board. */

int PegSolitaire::how_many_pegs = 0;

int main(){
	vector <PegSolitaire> vector_of_boards; /* Creates a vector of object of PegSolitaire class. */

	PegSolitaire temp; /* Creates a temp object. */

	int option_1, option_2, board_type, current_board;

	char size;

	string movement;

	string filename, name;

	do{ /* Continues until user wants to quit. */
		cout << "---MENU---" << endl << endl;
		cout << "1- ADD NEW BOARD" << endl << endl;
		if(vector_of_boards.size() > 0) /* Get rid of segmentation fault. */
			cout << "2- BOARD OPERATİONS" << endl << endl;
		cout << "3- NUMBER OF PEGS ON ALL BOARDS" << endl << endl;
		cout << "4- QUIT" << endl << endl;
		cout << "Enter your option: ";
		cin >> option_1;
		cout << endl;

		switch(option_1){
			case 1:
				cout << "---SUBMENU---" << endl << endl;
				cout << "1- ADD NEW BOARD FROM A FILE" << endl << endl;
				cout << "2- ADD NEW BOARD WİTH SIZE" << endl << endl;
				cout << "3- ADD NEW BOARD WİTH DEFAULT SIZE" << endl << endl;
				cout << "4- ADD NEW BOARD WİTH BOARD TYPES" << endl << endl;
				cout << "Enter your option: ";
				cin >> option_2;
				cout << endl;

				switch(option_2){
					case 1:
						cout << "Enter the name of the file(without .txt part): " ;
						cin >> filename;
						if(temp.read(filename) == true){ /* If the read function is successful, sets the name of the temp board and push the temp board to board vector. */
							temp.set_name_of_board(filename);
							vector_of_boards.push_back(temp);
						}
						break;
					case 2:
						cout << "Enter the board size: ";
						cin >> size;
						temp.set_board(size-'0');
						if(size > '5' && size <= '9'){ /* Sets the name of the temp board and push the temp board to board vector. */
							temp.set_name_of_board(); 
							vector_of_boards.push_back(temp);
						}
						break;
					case 3:
						temp.set_board(5);
						temp.set_name_of_board();
						vector_of_boards.push_back(temp);
						break;
					case 4:
						cout << "Enter the type of the board: ";
						cin >> board_type;
						if(board_type > 0 && board_type < 7){ /* Sets the name of the temp board and push the temp board to board vector. */
							temp.set_board_types(board_type);
							temp.set_name_of_board();
							vector_of_boards.push_back(temp);
						}
						break;
				}
				break;
			case 2:
				if(vector_of_boards.size() > 0){

					cout << "Enter the name of the board: ";
					cin >> name;

					for(int i = 0; i < vector_of_boards.size(); i++){ /* Finds the index of current board. */
						if(vector_of_boards[i].correct_board(name) == true){
							current_board = i;
						}
					}
					do{
						if(vector_of_boards[current_board].correct_board(name) == true){
							cout << "---SUBMENU---" << endl << endl;
							cout << "1- USER MAKES 1 MOVE" << endl << endl;
							cout << "2- COMPUTER MAKES 1 MOVE" << endl << endl;
							cout << "3- COMPUTER MAKES MOVES UNTIL THE GAME END" << endl << endl;
							cout << "4- SAVE THE BOARD" << endl << endl;
							cout << "5- SHOW STATİSTİCS" << endl << endl;
							cout << "6- QUIT" << endl << endl;
							cout << "Enter your option: ";
							cin >> option_2;
							cout << endl;
							switch(option_2){
								case 1:
									vector_of_boards[current_board].show_board();
									if(vector_of_boards[current_board].current_type() != 6){
										cout << "Enter the row number and col char(like 4B): ";
										cin >> movement;
										if(movement.size() == 2 && movement[0] > '0' && movement[0] <= '9' && movement[1] >= 'A' && movement[1] <= 'I'){
											vector_of_boards[current_board].play(movement[0]-'1', movement[1]-'A');
										}
										movement.clear();
									}
									else
										cout << "This function is not working for type 6 board" << endl;
									break;
								case 2:
									if(vector_of_boards[current_board].current_type() != 6){
										vector_of_boards[current_board].show_board();
										vector_of_boards[current_board].play();
									}
									else 
										cout << "This function is not working for type 6 board" << endl;
									break;
								case 3:
									if(vector_of_boards[current_board].current_type() != 6){
										vector_of_boards[current_board].show_board();
										vector_of_boards[current_board].playGame();
										vector_of_boards[current_board].show_statistics();	
									}
									else 
										cout << "This function is not working for type 6 board" << endl;
									break;
								case 4:
									vector_of_boards[current_board].write(name);
									break;
								case 5:
									vector_of_boards[current_board].show_statistics();
									break;
							}
						}
					}while(option_2 != 6);
				}
				break;
			case 3:
				cout << PegSolitaire::count_pegs() << endl;
		}
	}while(option_1 != 4);
}

