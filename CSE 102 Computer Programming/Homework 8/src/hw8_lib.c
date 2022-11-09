/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 1

void printmaze(cell_type maze[][8],int * counterx, int * countery){ /* Prints the current maze. */
	if((*countery)<8){ /* If vertical location is less than 8, continue. */
 
		if((*counterx) < 8){ /* If horizontal location is less than 8, continue. */

			switch(maze[(*countery)][(*counterx)]){
				case cell_wall:
					printf(" # "); /* If cell is wall print #. */
					break;

				case cell_free:
					printf("   "); /* If cell is free print space. */
					break;

				case cell_target:
					printf(" X ");  /* If cell is target print X. */
					break;

				case cell_p1:
					printf(" > "); /* If cell is player1 print >. */
					break;

				case cell_p2: 
					printf(" O "); /* If cell is player2 print O. */
					break;
			}
			(*counterx)+=1; /* Increases horizontal location. */

			printmaze(maze,counterx,countery);
		}

		else{ /* If horizontal location is not less than 8, continue. */
			(*countery)+=1; /* Increases vertical location. */

			(*counterx)=0; /* Assigns 0 to horizontal location. */

			printf("\n"); /* Goes to new line. */

			printmaze(maze,counterx,countery);
		}
	}	
}

void whereplayer(cell_type maze[][8], cell_type player, int * vertical, int * horizontal){ /* It finds current location of player. */

	if(maze[(*vertical)][(*horizontal)] != player){ /* If maze[vertical][horizontal] is not equal to player, continue. */

		if((*horizontal)<7){ /* If horizontal location is less than 7, increase horizontal location. */
			(*horizontal)+=1;
		}

		else{ /* If horizontal location is not less than 7, continue. */
			if((*vertical)<=7){  /* If vertical location is less or equal to 7, continue. */

				(*vertical)+=1; /* Increases vertical location. */

				(*horizontal)=0; /* Assigns 0 to horizontal location. */
			}
		}
		whereplayer(maze,player,vertical,horizontal);

	}
}

void getmove(char * movement){ /* Gets valid movements from the user. */

	char desiredmove;

	printf("ENTER THE DESİRED MOVEMENT ('r' for right, 'l' for left, 'u' for up, 'd' for down): ");

	scanf("%c",&desiredmove);

	getchar();

	if((desiredmove!= 'r' ) && (desiredmove!= 'l' ) && (desiredmove!= 'u' ) && (desiredmove!= 'd') && (desiredmove != 'q')){ /* If movement is not one of these, ask user again. */

		getmove(movement);
	}

	else (*movement) = desiredmove;

}

int check_move(cell_type maze[][8],move_type move,int * vertical,int * horizontal, cell_type player){ /* Checks move is valid or not and did player reach the target. */
	int flag = 0;
	if(move == move_right){
		if(maze[(*vertical)][(*horizontal)+1] == cell_target) flag=1; /* If movement is right and right cell is target, flag = 1. */

		if(maze[(*vertical)][(*horizontal)+1] == cell_free){ /* Makes player move. */

			maze[(*vertical)][(*horizontal)+1] = player;

			maze[(*vertical)][(*horizontal)] = cell_free;

		}
	}

	else if(move == move_left){
		if(maze[(*vertical)][(*horizontal)-1] == cell_target) flag=1; /* If movement is left and left cell is target, flag = 1. */

		if(maze[(*vertical)][(*horizontal)-1] == cell_free){ /* Makes player move. */
 
			maze[(*vertical)][(*horizontal)-1] = player;

			maze[(*vertical)][(*horizontal)] = cell_free;
		}
	}

	else if(move == move_down){
		if(maze[(*vertical)+1][(*horizontal)] == cell_target) flag=1; /* If movement is down and down cell is target, flag = 1. */

		if(maze[(*vertical)+1][(*horizontal)] == cell_free){ /* Makes player move. */

			maze[(*vertical)+1][(*horizontal)] = player;

			maze[(*vertical)][(*horizontal)] = cell_free;
		}
	}

	else if(move == move_up){
		if(maze[(*vertical)-1][(*horizontal)] == cell_target) flag=1; /* If movement is up and up cell is target, flag = 1. */

		if(maze[(*vertical)-1][(*horizontal)] == cell_free){ /* Makes player move. */

			maze[(*vertical)-1][(*horizontal)] = player;

			maze[(*vertical)][(*horizontal)] = cell_free;

		}
	}
	return flag;
}

void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)
{

}


void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE* infid;
	FILE* outfid;
	delete_words (infid, outfid, words_to_delete, number_of_words);
	printf("TO BE IMPLEMENTED\n");
}


int maze_move(cell_type maze[][8], cell_type player, move_type move)
{	
	char desiredmove;

	int a = 0, b = 0;

	int vertical = 0, horizontal = 0;

	int isreach;

	int flag = 0;

	printmaze(maze,&a,&b);

	whereplayer(maze,player,&vertical, &horizontal); /* Finds player current location. */

	getmove(&desiredmove); /* Gets move. */

	switch(desiredmove){
		case 'r':
			move = move_right;
			break;
		case 'l': 
			move = move_left;
			break;
		case 'u':
			move = move_up;
			break;
		case 'd': 
			move = move_down;
			break;
	}
	if(desiredmove != 'q'){ /* If user does not want to quit, continue. */
		isreach = check_move(maze, move, &vertical, &horizontal, player); /* Makes the movement and check player does reach the target or not. */

		if(isreach!=1) maze_move(maze, player, move); /* If player does not reach the target, continue to run. */

		else{ /* If player reaches the target, finish. */
			whereplayer(maze,player,&vertical, &horizontal);

			maze[vertical][horizontal] = cell_free;

			return 1;
		}

	}

}


void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n){
	
}
