#ifndef BOARDGAME
#define BOARDGAME

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace Base{

	enum class mode{MOVE, SIMULATE};

	class BoardGame2D{
	public:
		virtual void playUser() final{ /* Gets input from the user and calls playUser function until it returns false. */
			bool success;
			char input[256];
			cin.ignore();
			do{
				cout << "ENTER YOUR MOVE(for PegSolitaire 5C RIGHT, for EightPuzzle RIGHT, for Klotski I RIGHT): ";
		      	cin.getline(input, 256); /* Gets the input. */
				success = playUser(input); /* Calls playUser function */
			}while(success == true && endGame() != true); /* If movement is succesful and game is not end, continues. */
		}
		virtual bool playAuto(mode) = 0;
		virtual bool playUser(string) = 0;
		virtual void playAutoAll() final{ /* Calls playAuto function until it returns false. */
		 	bool success;
		 	do{
		 		success = playAuto(mode::MOVE);
		 	}while(success == true);
		 	print();
		}
		virtual bool endGame() final{ /* Simulates the board, and there is no movement returns true. */
			return !(playAuto(mode::SIMULATE));
		}
		virtual int boardScore() = 0;
		virtual void initialize() = 0;
		virtual void print() = 0;
		friend ostream& operator<<(ostream& os, BoardGame2D& obj){ /* Prints the table. */
			obj.print();
			return os;
		}
	};
}
using namespace Base;

namespace{
	void playVector(vector<BoardGame2D*> all_games){ /* Gets BoardGame2D object pointer array, and prints the menu. */
		int option;
		char input[256];
		for(long unsigned int i = 0; i < all_games.size(); i++){
			BoardGame2D * current_object = all_games[i]; /* Gets i.th object as the current object. */
			current_object->print();
		    do{
		      cout << "\nMENU" << endl << endl;
		      cout << "1- PLAY AUTO ONE MOVE\n2- PLAY AUTO ALL MOVES\n3- PLAY USER ONE MOVE\n4- PLAY USER ALL MOVES\n5- SHOW SCORE\n6- PRINT\n7- EXIT\n";
		      cout << "YOUR OPTION: ";
		      cin >> option;
		      switch(option){
		      	case 1:
		      		current_object->playAuto(mode::MOVE); 
		      		break;
		      	case 2:
		      		current_object->playAutoAll(); /* This part may get some time. */
		      		break;
		      	case 3:
		      		/* Play user. */
		      		cout << "ENTER YOUR MOVE(for PegSolitaire 5C RIGHT, for EightPuzzle RIGHT, for Klotski I RIGHT): ";
		      		cin.ignore();
		      		cin.getline(input, 256);
		      		current_object->playUser(input);
		      		break;
		      	case 4:
		      		current_object->playUser();
		      		break;
		      	case 5:
		      		cout << current_object->boardScore();
		      		break;
		      	case 6:
		      		cout << *current_object;
		      }
		    }while(0 < option && option < 7); /* Continues for every object until user wants to exit. */
		}
	}
}

#endif // BOARDGAME 