#include <stdio.h>

#include <stdlib.h>

#define N 3

typedef enum options{ /* Defines the options. */
	right,
	left,
	up,
	down
}options;

void clearaarray(int array[][10]); /* Takes an two dimensional array and makes every element of it 0. */

void randomly_placed(int array[][10]); /* Takes an two dimensional array and fills it randomly. */

void print_current(int array[][10]); /* Prints the current puzzle. */

int move(options myoption,int array[][10],int * startlocationx, int * startlocationy); /* Provides to make movement in puzzle. */

int check(int array[][10]); /* Checks the puzzle is solved or not. */

void findempty(int array[][10], int *startlocationx, int *startlocationy); /* Finds empty location. */

int is_solveable(int array[][10]); /* Controls puzzle is solveable or not. */

/*------------------------------------------------------------------------------------*/

int main(){
	
	int startlocationx, startlocationy, valid, logicvalue;
	
	options myoption;

	char desire;
	
	int myPuzzle[10][10];

	int cansolve=0;

	printf("PUZZLE İS BEİNG CREATED...\n");

	while(cansolve!=1){ /* This blocks provides to get rid of unsolveable puzzles. */

		clearaarray(myPuzzle); /* Makes 0 of each element of array. */

		randomly_placed(myPuzzle); /* Fills the array randomly. */

		cansolve = is_solveable(myPuzzle); /* If it is solveable returns 1, is not returns 0. */

	}

	while(1){
		print_current(myPuzzle); 

		if(check(myPuzzle)==1){ /* Checks puzzle is solved or not. */

			printf("YOU WON THE GAME!!!!\n");

			break;
		}

		printf("Enter the first letter of what do you want to do (right :r , left: l , up: u, down: d , exit: q):"); /* Gets desire from the user. */

		scanf(" %c", &desire);

		if(desire=='q')	break; /* If desire is quit, ends the program. */

		while(1){ /* This blocks provides gets valid input from the user. */

			if(desire!='r' && desire!='l' && desire!='d' && desire!='u'){

				printf("Please enter valid input: \n");

				scanf(" %c", &desire);
			}
			else break;

		}

		switch(desire){ 
			case 'r': /* If desire is 'r', option is right. */
				myoption=right;
				break;
			case 'l': /* If desire is 'l', option is left. */
				myoption=left;
				break;
			case 'u': /* If desire is 'u', option is up. */
				myoption=up;
				break;
			case 'd': /* If desire is 'd', option is down. */
				myoption=down;
				break;
		}

		printf("Enter the starting point (x y):");

		do{ 

			logicvalue=scanf("%d %d",&startlocationx,&startlocationy); /* Gets location of starting point. */

		}while(logicvalue!=2);

		valid = move(myoption,myPuzzle,&startlocationx,&startlocationy);

		if(valid!=1) printf("YOU COULDN'T MOVE!\n"); /* Checks desired movement is valid or not. */

	}

	return 0;
}

/*------------------------------------------------------------------------------------*/

void clearaarray(int array[][10]){
	int i, j;

	for(i=0;i<N;i++){

		for(j=0;j<N;j++){

			array[i][j]=0;
		}
	}
}

/*------------------------------------------------------------------------------------*/

void randomly_placed(int array[][10]){
	int i, a=0, j, b=(N*N);

	int myNumbers[N*N];

	int counter=0;

	for(i=0;i<(N*N);i++){ /* Creates an array from 0 to N*N. The elements of this array increases one by one. */

		myNumbers[i]=counter;

		counter++;
	}

	for(i=0;i<N;i++){

		for(j=0;j<N;j++){

			do{ /* Continues until valid number is got. */
				a=rand()%b;
			}while(myNumbers[a] ==-1); 

			array[i][j] = myNumbers[a]; /* Gets myNumbers elements randomly. */

			myNumbers[a] = -1; /* Makes the element which is taken -1 */ 
		}
	}
}

/*------------------------------------------------------------------------------------*/

void print_current(int array[][10]){ /* Prints each element of array in a puzzle format. */
	int i, j, a;

	for(i=0;i<N;i++){

		for(a=0;a<(8*N)+1;a++){
			printf("*");
		}

		printf("\n");

		for(j=0;j<N;j++){
			printf("*   %d\t",array[i][j]);
		}

		printf("*\n");
	}

	for(a=0;a<(8*N)+1;a++){
		printf("*");
	}

	printf("\n");

}

/*------------------------------------------------------------------------------------*/

int move(options myoption,int array[][10], int * startlocationx, int * startlocationy){
	int emptyx, emptyy, flag;

	int tempx, tempy;

	findempty(array, &emptyx, &emptyy); /* Finds location of empty point(0 element) of array. */

	tempx = emptyx; /* Assign emptyx to tempx to keep the x cordinates of empty point. */

	tempy = emptyy; /* Assign emptyy to tempy to keep the y cordinates of empty point. */

	if(*startlocationx==emptyx || *startlocationy==emptyy){ /* Controls the location which movement start if has same x or y cordinates with empty point. */

		switch(myoption){

			case right: /* If desired movement is right. */
				for(;emptyy>(*startlocationy);emptyy--){ /* Swips numbers from start location to empty location. */

					array[emptyx][emptyy]=array[emptyx][emptyy-1]; /* Assigns the value of the point which is on the left of empty point to empty point. */

					array[emptyx][emptyy-1]=0; /* Assigns 0 to the point which is on the left of empty point. */
					}
				break;

			case left: /* If desired movement is left. */
				for(;emptyy<(*startlocationy);emptyy++){ /* Swips numbers from start location to empty location. */

					array[emptyx][emptyy]=array[emptyx][emptyy+1]; /* Assigns the value of the point which is on the right of empty point to empty point. */

					array[emptyx][emptyy+1]=0; /* Assigns 0 to the point which is on the right of empty point. */
				}	
				break;
			case up: /* If desired movement is up. */
				for(;emptyx<(*startlocationx);emptyx++){ /* Swips numbers from start location to empty location. */

					array[emptyx][emptyy]=array[emptyx+1][emptyy]; /* Assigns the value of the point which is under the empty point to empty point. */

					array[emptyx+1][emptyy]=0; /* Assigns 0 to the point which is under the empty point. */
				}
				break;
			case down: /* If desired movement is down. */
				for(;emptyx>(*startlocationx);emptyx--){ /* Swips numbers from start location to empty location. */

					array[emptyx][emptyy]=array[emptyx-1][emptyy]; /* Assigns the value of the point which is over the empty point to empty point. */

					array[emptyx-1][emptyy]=0; /* Assigns 0 to the point which is over the empty point. */
				}	
				break;
			}
		if(emptyx == tempx && emptyy == tempy) flag=0; /* If empty location does not changes, the desired movement did not happen. */

		else flag=1;
	}
	else flag=0;

	return flag; /* Returns a value to check movement happened or not. */
}

/*------------------------------------------------------------------------------------*/

int check(int array[][10]){
	int i, j, controller=1, flag=1;

	for(i=0;i<N;i++){

		for(j=0;j<N;j++){

			if((i == N-1) && (j == N-1)) break;

			if(array[i][j] != controller) flag=0; /* Until last element, if a element is not equal to its total index ([i][j] != (N*i)+j), the puzzle is not solved. */

			controller++;
		}
	}
	return flag;
}

/*------------------------------------------------------------------------------------*/

void findempty(int array[][10], int *startlocationx, int *startlocationy){
	int i, j;
	for(i=0;i<N;i++){

		for(j=0;j<N;j++){

			if(array[i][j]==0){ /* If array[i][j]=0, i is our x location, j is our y location. */
				*startlocationx=i;

				*startlocationy=j;
			}
		}
	}
}

/*------------------------------------------------------------------------------------*/

int is_solveable(int array[][10]){

	/* If N is odd, then puzzle instance is solvable if number of inversions is even in the input state.
	   If N is even, puzzle instance is solvable if 
        	the blank is on an even row counting from the bottom (second-last, fourth-last, etc.) and number of inversions is odd.
   		 	the blank is on an odd row counting from the bottom (last, third-last, fifth-last, etc.) and number of inversions is even. */

	int emptyx, emptyy, i, j, k, l, counter=0;

	int disordered=0; /* Number of inversions. */

	int flag=0;

	int temparray[N*N];

	int temparray2[N*N];

	findempty(array, &emptyx, &emptyy);

	for(i=0;i<N;i++){

		for(j=0;j<N;j++){ /* Converts our two dimensional array to one dimensional arrays. */
			temparray[counter] = array[i][j]; /* First, one dimensional array. */

			temparray2[counter] = array[i][j]; /* Second, one dimensional array. */

			counter++;
		}
	}

	for(i=0;i<counter;i++){

		for(j=i;j<counter;j++){

			if(temparray[i]!=0 && temparray2[j]!=0){ 

				if(temparray[i] > temparray2[j]){ /* Compares temparray[i] and temparray2[j], j is start from i. elemet to last element. */
					disordered++;
				}
			}
		}
	}

	if(N%2!=0){ /* If N is even, */
		if(disordered%2==0) flag=1; /* If number of inversion is even, puzzle is solveable. */
	} 
	else{ /* If N is odd, */
		emptyx = N-emptyx;

		if(disordered%2==0){ /* If number of inversion is even, */
			if(emptyx%2!=0) flag=1; /* If the blank is on odd row, puzzle is solveable. */
		}

		else{ /* If number of inversion is odd, */
			if(emptyx%2==0) flag=1; /* If the blank is on even row, puzzle is solveable. */
		}
	}
	return flag;
}

/*------------------------------------------------------------------------------------*/