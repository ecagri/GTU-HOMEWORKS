/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>

#include <stdlib.h>

#include "hw8_lib.h"


void test_clean_file () 
{
	
}


void test_maze_move ()
{
	cell_type maze[8][8];

	cell_type player;

	move_type move;

	int a, b; /* Variables for random. */

	int i, j; /* Variables for loops. */

	int isreach; 

	for(i=0;i<8;i++){ /* Clear the maze. */
		for(j=0;j<8;j++){
			maze[i][j] = cell_free;
		}
	}

	for(i=0;i<8;i++){ /* Makes edges of the maze wall. */
		if(i == 0 || i == 7){
			for(j=0;j<8;j++){
				maze[i][j] = cell_wall;
			}
		}
		else{
			maze[i][0] = cell_wall;
			maze[i][7] = cell_wall;
		}
	}

	for(i=2;i<=4;i+=2){ /* Creates some walls and empty places for the maze game. */
		for(j=7-i;j>0;j--){
			maze[j][i] = cell_wall;
		}

		b = 1 + rand()%2;

		while(b>0){	
			a = 1 + rand() % (6-i);

			maze[a][i] = cell_free;

			b--;
		}
	}

	for(i=3;i<=5;i+=2){ /* Creates some walls and empty places for the maze game. */
		for(j=7-i;j<7;j++){
			maze[i][j] = cell_wall;
		}

		b = 1 + rand()%2;

		while(b>0){	
			a = 8-i + rand() % (i-1);

			maze[i][a] = cell_free;

			b--;
		}
	}

	maze[1][6] = cell_target; /* Target point. */ 

	maze[6][1] = cell_p1; /* Starting point for player 1. */

	player = cell_p1; 

	isreach = maze_move(maze,player,move); /* Calls the function. */

	if(isreach == 1){
		printf("CONGRULATİONS...\n");
	}

	else printf("GAME OVER...\n");

	player = cell_p2;

	maze[6][1] = cell_p2;

	isreach = maze_move(maze,player,move); /* Calls the function. */

	if(isreach == 1){
		printf("CONGRULATİONS...\n");
	}

	else printf("GAME OVER...\n");

}


void test_towers_of_hanoi ()
{
	
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
