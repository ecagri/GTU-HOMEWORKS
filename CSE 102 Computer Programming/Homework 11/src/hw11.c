#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/* -------------------------------------------------------------------- */

typedef struct Movie_Budget{
	int budget;
	int year;
	char * name;
	struct Movie_Budget * nextp;	
}Movie_Budget;

typedef struct Movie_Name{
	double score;
	char * name;
	char * genre;
	struct Movie_Name * nextp;
}Movie_Name;

/* -------------------------------------------------------------------- */

/* Theese functions provides to fill the list. */

void read(char filename[], Movie_Budget ** budgetmovie, Movie_Name ** namemovie); /* Fills list with the information from text. */

void insert_end(struct Movie_Budget **head, int budget, int year, char* name_); /* Adds a element to list for Movie_Budget. */

void insert_end2(struct Movie_Name **head, char * genre, char* name, double score); /* Adds a element to list for Movie_Name. */

double convertdbl(char string[]); /* Converts string to double. */

void update(Movie_Budget ** movieb); /* Deletes same elements in the list for Movie_Budget. */

void update2(Movie_Name ** movien); /* Deletes same elements in the list for Movie_Name. */

/* These are menu functions. */

void listofsorteddata(Movie_Budget * movieb, Movie_Name * movien); /* Sorts data. */

void frequenceofgenres(Movie_Name * movien, int option); /* Finds genre types and frequences. */

void to_year(Movie_Budget * movieb); /* Finds movies until or since some years. */

void to_score(Movie_Name * movien); /* Finds movies until or since some scores. */

void find_movie(Movie_Budget * movieb, Movie_Name * movien); /* Gets a string and find the movie which has same name. */

void calculate_IMDB(Movie_Name * movien); /* Calculates avarage points of movies. */

/* These are listofsorteddata functions. */

void budgetscoreyear(Movie_Budget * movieb, Movie_Name * movien, int operation); 

/* -------------------------------------------------------------------- */

int main(){
	char filename[10] = "Movies.txt"; /* Name of the txt file. */

	Movie_Budget * movieb = NULL; /* Creating a movie_budget list. */

	Movie_Name * movien = NULL; /* Creating a movie_name list. */

	int option;

	movieb = (Movie_Budget*)(malloc(sizeof(Movie_Budget))); /* Allocate memory for list. */

	movien = (Movie_Name*)(malloc(sizeof(Movie_Name))); /* Allocate memory for list. */

	read(filename, &movieb, &movien); /* Calls read function. */

	do{ /* Works until 8 is entered. */
		printf("1. List of the Sorted Data\n");

		printf("2. List of the Genres\n");

		printf("3. List of the Movie Through the Years\n");

		printf("4. List of the Movie Through the Scores \n");

		printf("5. All Informations of a Single Movie\n");

		printf("6. Avarage of the IMBD Scores\n");

		printf("7. Frequence of the Genres\n");

		printf("8. Exit\n");

		printf("Please Select an operation:");

		scanf("%d", &option); /* Gets user option. */

		switch(option){
			case 1: /* If option is 1, continue. */
				listofsorteddata(movieb, movien); /* Calls listofsorteddata function. */
				break;
			case 2:	/* If option is 2, continue. */
				frequenceofgenres(movien, option); /* Calls frequenceofgenres function with case number. */
				break;
			case 3: /* If option is 3, continue. */
				to_year(movieb); /* Calls to_year function. */
				break;
			case 4: /* If option is 4, continue. */
				to_score(movien); /* Calls to_score function. */
				break;
			case 5: /* If option is 5, continue. */
				find_movie(movieb, movien); /* Calls find_movie function. */
				break;
			case 6: /* If option is 6, continue. */
				calculate_IMDB(movien); /* Calls calculate_IMDB function. */
				break;
			case 7: /* If option is 7, continue. */
				frequenceofgenres(movien, option); /* Calls frequnceofgenres function with case number. */
				break;
			case 8:
				break;
			default: /* If option is not 8 or a menu option, prints try again. */
				printf("TRY AGAİN\n\n");
		}
	}while(option != 8);

}

/* -------------------------------------------------------------------- */

void read(char filename[], Movie_Budget ** addbudget, Movie_Name ** addname){ 
	FILE * fptr; /* Creates a file pointer. */

	char a, *string, *name, *genre;

	double score;

	int i = 0, count = -5, year, budget; /* Count is -5 to get rid of first line. */

	fptr = fopen(filename, "r"); /* Opens the file in read mode. */

	while(fscanf(fptr, "%c", &a)!= EOF){ /* Gets every char until the end of the file. */
		i++; /* Increases i every time. */

		if((a == 44) || (a == 10)){ /* If char a is ',' or new line sign, continue. */

			string = (char*)(calloc(i,sizeof(char))); /* Allocates memory for string. */

			fseek(fptr, -i, SEEK_CUR); /* Goes i character back. */ 

			fscanf(fptr, "%[^,\n]%*c", string); /* Gets string until ',' or new line sign. */
	
			switch(count%5){ 
				case 0: /* If it is first element of line, gets budget. */

					budget = (int)(convertdbl(string)); /* Converts string to integer and assigns it to budget. */

					break;
				case 1: /* If it is second element of line, gets genre. */
					genre = (char*)(calloc(i,sizeof(char))); /* Allocates memory for genre string. */

					strcpy(genre, string); /* Copy the string to genre. */

					break;
				case 2: /* If it is third element of line, gets name. */
					name = (char*)(calloc(i,sizeof(char))); /* Allocates memory for name string. */

					strcpy(name, string); /* Copy the string to name. */

					break;
				case 3: /* If it is fourth element of line, gets score. */
					score = convertdbl(string); /* Converts string to double and assigns it to score. */

					break;
				case 4:	/* If it is fifth element of line, gets year. */
					year = (int)(convertdbl(string)); /* Converts string to integer and assigns it to year. */

					insert_end(addbudget, budget, year, name); /* Adds new element to addbugdet list. */

					insert_end2(addname, genre, name, score); /* Adds new element to addname list. */
					break;
			}

			count++; /* Increases count. */

			free(string); /* free the memory of string. */
 
			i = 0; /* Makes i zero. */
		}

	}

	*addbudget = (*addbudget)->nextp; /* Gets next element of addbudget. */

	*addname = (*addname)->nextp; /* Gets next element of addname .*/

	update(addbudget); /* Updates addbudget list(Deletes elements which has same name). */

	update2(addname); /* Updates addname list(Deletes elements which has same name). */

}

/* -------------------------------------------------------------------- */

void update(Movie_Budget ** movieb){
	Movie_Budget * temp, *keeper; /* Creates two Movie_Budget list. */

	temp = (Movie_Budget*)(malloc(sizeof(Movie_Budget))); /* Allocates memory for temp. */

	keeper = (Movie_Budget*)(malloc(sizeof(Movie_Budget))); /* Allocates memory for keeper. */

	keeper = *movieb; /* Assigns movieb to keeper. */

	*movieb = NULL; /* Makes movieb NULL. */

	int flag;

	while(keeper != NULL){ /* Continues until keeper list ends. */

		flag = 0;

		temp = keeper->nextp; /* Temp is the next element of keeper list. */

		while(temp != NULL){ /* Continues until temp list ends. */

			if(strcmp(temp->name,keeper->name) == 0){	/* If it finds a movie which has same name in the rest of the list, contiune. */
				flag = 1; /* Makes flag 1. */				
				break;

			}
			temp = temp->nextp; /* Temp is the next element of temp list. */

		}		

		if(flag == 0){ /* If flag is zero continue. */

			insert_end(movieb, keeper->budget, keeper->year, keeper->name); /* Add the element to movieb list. */

		}

		keeper = keeper->nextp; /* Keeper is the next element of keeper list. */

	}
}

/* -------------------------------------------------------------------- */

void update2(Movie_Name ** movien){
	Movie_Name * temp, *keeper; /* Creates two Movie_Name list. */

	temp = (Movie_Name*)(malloc(sizeof(Movie_Name))); /* Allocates memory for temp. */

	keeper = (Movie_Name*)(malloc(sizeof(Movie_Name))); /* Allocates memory for keeper. */

	keeper = *movien; /* Assigns movien to keeper. */

	*movien = NULL; /* Makes movien NULL. */

	int flag;

	while(keeper != NULL){ /* Continues until keeper list ends. */

		flag = 0;

		temp = keeper->nextp; /* Temp is the next element of keeper list. */

		while(temp != NULL){ /* Continues until temp list ends. */

			if(strcmp(temp->name,keeper->name) == 0){ /* If it finds a movie which has same name in the rest of the list, contiune. */
				flag = 1; /* Makes flag 1. */				
				break;

			}
			temp = temp->nextp; /* Temp is the next element of temp list. */

		}		

		if(flag == 0){ /* If flag is zero continue. */

			insert_end2(movien, keeper->genre, keeper->name, keeper->score); /* Add the element to movien list. */

		}

		keeper = keeper->nextp; /* Keeper is the next element of keeper list. */

	}
}

/* -------------------------------------------------------------------- */

double convertdbl(char string[]){
	double d;

	if(strcmp(string,"unknown") != 0) sscanf(string, "%lf",&d); /* If it is not unknown convert int to double number. */

	else d = -1; /* If it is unknown return -1. */

	return d;
}

/* -------------------------------------------------------------------- */

void insert_end(struct Movie_Budget **head, int budget, int year, char* name){ 
    struct Movie_Budget *newnode = malloc(sizeof(Movie_Budget));

    newnode->budget = budget;

    newnode->year = year;

    newnode->name = name;
    
    newnode->nextp = NULL;

    if(*head == NULL)
 		*head = newnode;
    else
    {
        struct Movie_Budget *lastnode = *head;

        while(lastnode->nextp != NULL)
			lastnode = lastnode->nextp;

        lastnode->nextp = newnode;
    }
}

/* -------------------------------------------------------------------- */

void insert_end2(struct Movie_Name **head, char * genre, char* name, double score){ 
    struct Movie_Name *newnode = malloc(sizeof(Movie_Name));

    newnode->score = score;

    newnode->genre = genre;

    newnode->name = name;

    newnode->nextp = NULL;

    if(*head == NULL)
 		*head = newnode;
    else
    {
        struct Movie_Name *lastnode = *head;

        while(lastnode->nextp != NULL)
			lastnode = lastnode->nextp;

        lastnode->nextp = newnode;
    }
}

/* -------------------------------------------------------------------- */

void calculate_IMDB(Movie_Name * movien){
	double sum = 0;

	int counter = 0;

	while(movien != NULL){ /* Continues until list ends. */
		sum += movien->score; /* Adds score of each element to sum. */

		counter++; /* Increases counter by one every time. */

		movien = movien->nextp; /* movien is the next element of movien list. */
	}

	printf("Avarage is :%f\n",sum/counter); /* Prints avarage of scores. */
}

/* -------------------------------------------------------------------- */

void find_movie(Movie_Budget * movieb , Movie_Name * movien){
	char string[100]; /* Allocate memory for string. */

	printf("Enter the name of the movie: "); 

	scanf(" %[^\n]%*c", string); /* Gets movie name. */

	while(movieb != NULL){ /* Continues until list ends. */
		if(strcmp(movieb->name, string) == 0){ /* If it finds the movie in the list, print it. */
			if(movieb->budget > 0) printf("Budget: %d\n",movieb->budget); /* If budget is bigger than 0, prints it. */

			else printf("Budget: UNKNOWN\n"); /* If budget is less than 0 (unknown), prints unknown. */

			printf("Genre: %s\nName: %s\nScore: %f\nYear: %d\n",movien->genre,movien->name,movien->score,movieb->year); /* Prints other element of movie. */

			break;
		}
		movieb = movieb->nextp; /* movieb is the next element of movieb list. */

		movien = movien->nextp; /* movien is the next element of movien list. */
	}
}

/* -------------------------------------------------------------------- */

void to_score(Movie_Name * movien){
	double score;

	int is_greater, flag = 0;;

	Movie_Name * head = (Movie_Name*)(malloc(sizeof(Movie_Name))); /* Allocates memory for head list. */

	head = movien; /* Assign movien list to head. */

	printf("Please enter a score: ");

	scanf("%lf", &score); /* Gets score. */

	printf("Less (0) or greater(1): ");

	scanf("%d", &is_greater); /* Gets is_greater. */

	while(head != NULL){ /* Continues until list ends. */
		if(is_greater == 1){ /* If user wants to finds movies which has greater point than that score, continue. */
			if(head->score > score){ /* If score of movies is greater score than referance point, continue. */
				printf("%s\n",head->name); /* Prints name of the movie. */
 
				flag++; /* Increases flag by one. */
			}
		}
		else if(is_greater == 0){ /* If user wants to finds movies which has less point than that score, continue. */
			if(head->score < score){ /* If score of movies is less score than referance point, continue. */
				printf("%s\n",head->name); /* Prints name of the movie. */

				flag++; /* Increases flag by one. */
			}
		}

		head = head->nextp; /* Head is the next element of head list. */
	}

	if(flag == 0){ /* If flag is zero, runs the function again. */
		printf("TRY AGAİN\n");
		to_score(movien);
	}
}	

void to_year(Movie_Budget * movieb){
	int year, is_greater, flag = 0;

	Movie_Budget * head;

	head = (Movie_Budget*)(malloc(sizeof(Movie_Budget))); /* Allocates memory for head list. */

	head = movieb; /* Assign movien list to head. */

	printf("Please enter a year: ");

	scanf("%d", &year); /* Gets year. */

	printf("Less (0) or greater(1): "); /* Gets is_greater. */

	scanf("%d", &is_greater);

	while(head != NULL){ /* Continues until list ends. */
		if(is_greater == 1){ /* If user wants to finds movies which has greater year than that year, continue. */
			if(head->year > year){ /* If score of movies is greater year than referance year, continue. */
				printf("%s\n",head->name); /* Prints name of the movie. */

				flag++; /* Increases flag by one. */
			}
		}
		else if(is_greater == 0){ /* If user wants to finds movies which has less year than that year, continue. */
			if(head->year < year){ /* If score of movies is less year than referance year, continue. */
				printf("%s\n",head->name); /* Prints name of the movie. */

				flag++; /* Increases flag by one. */
			}
		}

		head = head->nextp; /* Head is the next element of head list. */
	}

	if(flag == 0){ /* If flag is zero, runs the function again. */
		printf("TRY AGAİN\n");
		to_year(movieb);
	}

}

void listofsorteddata(Movie_Budget * movieb,Movie_Name * movien){
	int operation;
	do{ /* Continues until gets valid operation. */

		printf("1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n\n");

		printf("Please Select an operation: ");

		scanf("%d", &operation); /* Gets operation. */

		switch(operation){
			case 1: /* If operation is 1, continue. */
				budgetscoreyear(movieb, movien, operation); /* Calls accordingbudget function. */
				break;
			case 2: /* If operation is 2, continue. */
				printf("This function is not working.\n");
				break;
			case 3: /* If operation is 3, continue. */
				printf("This function is not working.\n");
				break;
			case 4: /* If operation is 4, continue. */
				budgetscoreyear(movieb, movien, operation); /* Calls accordingscore function. */
				break;
			case 5: /* If operation is 5, continue. */
				budgetscoreyear(movieb, movien, operation); /* Calls accordingyear function. */
				break;
		default:
			printf("TRY AGAIN\n");
			break;
		}
	}while(operation<1 || operation>5); /* If operation is valid, break. */
}

void budgetscoreyear(Movie_Budget * movieb ,Movie_Name * movien, int cases){

	Movie_Budget * headb = malloc(sizeof(Movie_Budget)); /* Allocates memory for headb list. */

	Movie_Name * headn = malloc(sizeof(Movie_Name)); /* Allocates memory for headn list. */

	Movie_Budget * tempb = malloc(sizeof(Movie_Budget)); /* Allocates memory for tempb list. */

	Movie_Name * tempn = malloc(sizeof(Movie_Name)); /* Allocates memory for tempn list. */

	Movie_Budget * keeperb = malloc(sizeof(Movie_Budget)); /* Allocates memory for keeperb list. */

	Movie_Name * keepern = malloc(sizeof(Movie_Name)); /* Allocates memory for keepern list. */

	headb = movieb; /* Assigns movieb to headb. */

	headn = movien; /* Assigns movien to headn. */

	int operation, i, interval = 0;

	double bottom, top, min;

	printf("1- Single selection\n2- Multiple selection\n");

	printf("Please Select an operation: ");

	scanf("%d", &operation); /* Gets operation. */

	if(operation == 1){ /* If operation is 1, continue. */
		printf("Please enter a value: ");

		scanf("%lf", &bottom); /* Gets bottom border. */

		top = bottom; /* Assign bottom to top. */
	}

	else if(operation == 2){ /* If operation is 2, continue. */
		printf("Please enter start value: ");

		scanf("%lf", &bottom); /* Gets bottom border. */

		printf("Please enter end value: ");

		scanf("%lf", &top); /* Gets top border. */
	}

	printf("\n\n");

	/* This part creates new list which is that interval. */

	while(movieb != NULL){ /* Continues until movieb list ends. */
		if(cases == 1){
			if(top >= movieb->budget && movieb->budget >= bottom){ /* If budget is in between top and bottom, continues. */
				insert_end(&tempb, movieb->budget, movieb->year, movieb->name); /* Adds the element to tempb list. */
				insert_end2(&tempn, movien->genre, movien->name, movien->score); /* Adds the element to tempn list. */
				interval++; /* Increases interval by one. */
			}
		}
		else if(cases == 4){
			if(top >= movien->score && movien->score >= bottom){ /* If score is in between top and bottom, continues. */
				insert_end(&tempb, movieb->budget, movieb->year, movieb->name); /* Adds the element to tempb list. */
				insert_end2(&tempn, movien->genre, movien->name, movien->score); /* Adds the element to tempn list. */
				interval++; /* Increases interval by one. */
			}
		}
		else if(cases == 5){
			if(top >= movieb->year && movieb->year >= bottom){ /* If year is in between top and bottom, continues. */
				insert_end(&tempb, movieb->budget, movieb->year, movieb->name); /* Adds the element to tempb list. */
				insert_end2(&tempn, movien->genre, movien->name, movien->score); /* Adds the element to tempn list. */
				interval++; /* Increases interval by one. */
			}
		}
		movieb = movieb->nextp; /* Movieb is the next element of movieb list. */

		movien = movien->nextp; /* Movien is the next element of movien list. */
	}

	/* The rest of the function is for the printing elements in ascending order. */
	
	tempb = tempb->nextp; /* Tempb is the next element of tempb list. */

	tempn = tempn->nextp; /* Tempn is the next element of tempn list. */

	keeperb = tempb; /* Assigns tempb to keeperb. */

	keepern = tempn; /* Assigns tempn to keepern. */

	movieb = headb; /* Assigns headb to movieb. */

	movien = headn; /* Assigns headn to movien. */

	if(cases == 1){ /* For budget. */
		for(i=0;i<interval;i++){ /* Works numberofinterval times. */
			min = top;
			while(tempb != NULL){ /* Continues until tempb list ends. */
				if(tempb->budget <= min && tempb->budget >-2){ /* If budget is less than min and bigger than -2, continue. */
					min = tempb->budget; /* Assign tempb->budget to min. */
				}
				tempb = tempb->nextp; /* Tempb is the next element of tempb list. */
			}
			tempb = keeperb; /* Assigns keeperb to tempb. */

			while(tempb != NULL){ /* Continues until tempb list ends. */
				if(tempb->budget == min){ /* If budget is equals to min, prints it. */
					if(tempb->budget>=0) 
						printf("%d ",tempb->budget);
					else{
						printf("UNKNOWN ");
					}
					printf("%s %s %lf %d\n",tempn->genre, tempb->name, tempn->score, tempb->year);
					tempb->budget = -9; /* Makes budget -9 to get rid of that element. */
				}
				tempb = tempb->nextp; /* Tempb is the next element of tempb list. */
				tempn = tempn->nextp; /* Tempn is the next element of tempn list. */
			}
			tempn = keepern; /* Assigns keepern to tempn. */
			tempb = keeperb; /* Assigns keeperb to tempb. */
		}
	}
	else if(cases == 5){ /* For year */
		for(i=0;i<interval;i++){ /* Works numberofinterval times. */
			min = top;
			while(tempb != NULL){ /* Continues until tempb list ends. */
				if(tempb->year <= min && tempb->year >-2){ /* If year is less than min and bigger than -2, continue. */
					min = tempb->year; /* Assign tempb->year to min. */
				}
				tempb = tempb->nextp; /* Tempb is the next element of tempb list. */
			}
			tempb = keeperb; /* Assigns keeperb to tempb. */
			while(tempb != NULL){ /* Continues until tempb list ends. */
				if(tempb->year == min){ /* If budget is equals to min, prints it. */
					if(tempb->budget>=0) 
						printf("%d ",tempb->budget);
					else{
						printf("UNKNOWN ");
					}
					printf("%s %s %lf %d\n",tempn->genre, tempb->name, tempn->score, tempb->year);
					tempb->year = -9; /* Makes year -9 to get rid of that element. */
				}
				tempb = tempb->nextp; /* Tempb is the next element of tempb list. */
				tempn = tempn->nextp; /* Tempn is the next element of tempn list. */
			}
			tempn = keepern; /* Assigns keepern to tempn. */
			tempb = keeperb; /* Assigns keeperb to tempb. */
		}
	}
	else if(cases == 4){ /* For score. */
		for(i=0;i<interval;i++){ /* Works numberofinterval times. */
			min = top;
			while(tempn != NULL){ /* Continues until tempb list ends. */
				if(tempn->score <= min && tempn->score >-2){ /* If score is less than min and bigger than -2, continue. */
					min = tempn->score; /* Assign tempb->score to min. */
				}
				tempn = tempn->nextp; /* Tempb is the next element of tempb list. */
			}
			tempn = keepern; /* Assigns keeperb to tempb. */
			while(tempn != NULL){ /* Assigns keeperb to tempb. */
				if(tempn->score == min){ /* If budget is equals to min, prints it. */
					if(tempb->budget>=0) 
						printf("%d ",tempb->budget);
					else{
						printf("UNKNOWN ");
					}
					printf("%s %s %lf %d\n",tempn->genre, tempb->name, tempn->score, tempb->year);
					tempn->score = -9; /* Makes score -9 to get rid of that element. */
				}
				tempb = tempb->nextp; /* Tempb is the next element of tempb list. */
				tempn = tempn->nextp; /* Tempn is the next element of tempn list. */
			} 
			tempn = keepern; /* Assigns keepern to tempn. */
			tempb = keeperb; /* Assigns keeperb to tempb. */
		}
	}
	/* Free the memory. */
	tempb = NULL;

	tempn = NULL;

	headb = NULL;

	headn = NULL;

	free(tempb);

	free(tempn);

	free(headb);

	free(headn);

}

void frequenceofgenres(Movie_Name * movien, int option){

	int flag, frequence;

	Movie_Name * head = malloc(sizeof(Movie_Name)); /* Allocates memory for head. */

	Movie_Name * temp = malloc(sizeof(Movie_Name)); /* Allocates memory for temp. */

	temp = movien; /* Assign movien to temp. */

	while(temp != NULL){ /* Continues until temp ends. */
		flag = 0;
		frequence = 0;
		head = movien;

		while(strcmp(head->name, temp->name) != 0){ /* Compares temp with movien elements until temp. */
			if(strcmp(head->genre, temp->genre) == 0){ /* If it found same genre, continue. */
				flag++; /* Increases flag by one and breaks the loop. */
				break;
			}
			head = head->nextp; /* Head is the next element of head list. */
		}
		if(flag == 0){ /* If it couldn't same genre, continue. */
			if(option == 2) printf("%s\n",temp->genre); /* If option is 2, prints just genre. */
			head = movien; /* Goes back head of the movien list. */
			if(option == 7){ /* If option is 7, continue. */
				while(head != NULL){ /* Continues until head list ends. */
					if(strcmp(temp->genre, head->genre) == 0){ /* If it founds same genre, increases frequence by one. */
						frequence++;
					}
					head = head->nextp; /* Head is the next element of head list. */
				}
				printf("%s %d\n",temp->genre, frequence); /* Prints genre and frequence. */
			}
		}

		temp = temp->nextp; /* Temp is the next element of temp list. */
	}

	free(temp); /* Free temp. */
}
