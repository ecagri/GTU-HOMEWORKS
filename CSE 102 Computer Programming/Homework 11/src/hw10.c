#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

 /* -------------------------------------------------------------
 	I used math.h library, it was not crucial but 
 it makes much easier my program. I hope that was not a problem. 
 ---------------------------------------------------------------*/

/* Defining struct... */
typedef struct Movie{
	double budget;
	int genre;
	char * name;
	double score;
	int year;
}Movie;

typedef struct genres{
	char * name;
}genres;

/* Defining functions... */

int count(char filename[]); /* Counts the number of line in txt. */

Movie * read(char filename[],int * elementnumber,  genres ** genre1, int * genreelements); /* Reads file and creates a dynamic array. */

double strtodbl(char string[], int elementnumber); /* Converts string to double number. */

int strtoint(char stringg[], int elementnumber); /* Converts string to integer number. */

genres * addgenre(genres * genresofmovie, int * elementnumber, char * string, int * index); /* Adds genres struct a element. */

Movie * update(Movie * movies, int * elementnumber); /* Update the Movie struct. Erases the movies which has same name. */

void listof_data(Movie * movies, int elementnumber); 

int findmax(Movie * movies, int elementnumber); /* Find max score in the txt. */


/* Main function... */

void main(){
	char filename[20] = {"Movies.txt"};

	Movie * movies;

	genres * genre1;

	int elementnumber, option, genreelements=0, i, year,issince, max, ishigh, flag;

	double avarage,sum = 0;

	double score;

	movies = read(filename, &elementnumber, &genre1, &genreelements);

	movies = update(movies,&elementnumber);

	while(1){

		printf("1. List of the Sorted Data\n");

		printf("2. List of the Genres\n");

		printf("3. List of the Movie Through the Years\n");

		printf("4. List of the Movie Through the Scores \n");

		printf("5. All Informations of a Single Movie\n");

		printf("6. Avarage of the IMBD Scores\n");

		printf("7. Frequence of the Genres\n");

		printf("8. Exit\n");

		printf("Please Select an operation:");

		scanf("%d", &option);

		switch(option){
			case 1: 
				listof_data(movies, elementnumber);
				break;
			case 2:
				for(i=0;i<genreelements;i++){
					printf("%s\n",genre1[i].name);
				}
				break;
			case 3: 
				max = findmax(movies, elementnumber);

				do{
					printf("Enter a year:");

					scanf("%d",&year);
				}while(year>max);

				printf("Until(0) or Since(1) %d: ",year);

				scanf("%d",&issince);

				if(issince==0){

					for(i=0;i<elementnumber;i++){

						if(movies[i].year<year){

							printf("%s\n",movies[i].name);
						}
					}
				}
				else{

					for(i=0;i<elementnumber;i++){

						if(movies[i].year>=year){

							printf("%s\n",movies[i].name);
						}
					}
				}
				break;
			case 4: 
				while(1){
					printf("Enter the score:");

					scanf("%lf",&score);

					printf("Is great or less than score (1: great and equal, 0: less):");

					scanf("%d",&ishigh);
					if(ishigh == 1){
						for(i=0;i<elementnumber;i++){
							if(movies[i].score>=score){

								printf("%s\n",movies[i].name);
								flag = 1;
							}
						}
					}
					else{
						for(i=0;i<elementnumber;i++){
							if(movies[i].score<score){

								printf("%s\n",movies[i].name);
								flag = 1;
							}
						}
					}
					if(flag == 1) break;
				}
				break;
			case 5: 
				break;
			case 6: 
				for(i=0;i<elementnumber;i++){
					sum += movies[i].score;
				}
				if(sum!= 0){
					avarage = sum/elementnumber;
				}
				else avarage = 0;
				printf("Avarage :%f\n",avarage);
				break;
			case 7: 
				//frequence_genres();
				break;
			case 8: 
				exit(1);
				break;
			default: 	
				printf("TRY AGAİN.\n\n\n");
				break;
		}
	}
}

/* Creating functions... */

int count(char filename[]){
	FILE * fptr;

	int i = 0;
	
	char * string;

	char a;

	fptr = fopen(filename, "r");

	while(fscanf(fptr, "%c", &a)!= EOF){ /* Get a char from the txt and if it is \n char, increases the size. */
		if(a == 10) i++;
	}

	fclose(fptr);

	return i;
}

Movie * read(char filename[], int * elementnumber, genres ** genre1,int * genreelements){
	FILE * fptr;

	int i = 0, counter = 0, movienumber = 0, index = 1;

	Movie * movies;

	char a;

	char * string;
	
	fptr = fopen(filename, "r");
	
	(*elementnumber) = count(filename);

	movies = (Movie*)(calloc((*elementnumber), sizeof(Movie))); /* Creates a movies struct. */

	while(fscanf(fptr, "%c", &a) != EOF){ /* Gets char until end of the file. */
		i++;

		if(a == ',' || a == 10){ /* If the char is ',' or '\n', continue. */

			fseek(fptr,-i,SEEK_CUR); /* Goes back by the number i. */

			string = (char*)(calloc(i,sizeof(char))); /* Creates a char array. */

			fscanf(fptr,"%[^,\n]%*c",string); /* Gets string from the file. */
			switch(counter%5){ 
				case 0: /* If first element of the line, gets it as budget. */
					if(strcmp(string, "unknown") == 0) movies[movienumber].budget = -1;
					else movies[movienumber].budget = strtodbl(string, i-1);

					break;
				case 1: /* If second element of the line, gets it as genre. */
					*genre1 = addgenre(*genre1,genreelements,string,&index);

					movies[movienumber].genre = index;

					break;
				case 2:	/* If third element of the line, gets it as name. */
					movies[movienumber].name = (char*)(calloc(i,sizeof(char)));
					strcpy(movies[movienumber].name,string);
					break;
				case 3: /* If fourth element of the line, gets it as score. */
					movies[movienumber].score = strtodbl(string, i-1);
					break;
				case 4: /* If fifth element of the line, gets it as year. */
					movies[movienumber].year = strtoint(string, i-1);
					movienumber++;
					break;
			}
			counter++; /* Increases counter by one. */

			i = 0; /* Makes i, 0. */

		}
	}
	fclose(fptr);

	return movies;

}

double strtodbl(char string[], int elementnumber){
	int i, temp = 0;

	double sum = 0;

	for(i=0;i<elementnumber;i++){
		if(string[i] != 46) temp++;
		else break;
	}

	for(i=0;i<elementnumber;i++){
		if(string[i] != 46){
			sum += (string[i]-48) * pow(10,--temp);
		}
	}
	return sum;
}

int strtoint(char string[], int elementnumber){
	int i;

	int number = 0;

	int temp = elementnumber-1;

	for(i=0;i<elementnumber-1;i++){ 
		number += (string[i]-48) * pow(10,--temp);
	}
	return number;
}

genres * addgenre(genres * genresofmovie, int * elementnumber, char * string, int * index){
	genres * temp; /* Creates a temp struct. */

	int flag = 0, i;

	temp = (genres*)(calloc((*elementnumber)+1,sizeof(genres)));

	for(i=0;i<(*elementnumber);i++){
		temp[i].name = (char *)(calloc(strlen(genresofmovie[i].name),sizeof(char))); /* Creates a temp.name char array. */

		strcpy(temp[i].name, genresofmovie[i].name); /* Copies the i. index of genresofmovie name to i. index of temp name. */

		free(genresofmovie[i].name);

	}
	for(i=0;i<(*elementnumber);i++){	
		if(strcmp(temp[i].name,string) == 0){ /* If the string has already taken, gets index of it. */
			flag = 1;

			(*index) = i;
		}
	}

	if(flag == 0){ /* If the string has not taken yet, adds the string temp struct, increases elementnumber and makes last element index. */
		temp[i].name = (char *)(calloc(strlen(string),sizeof(char)));

		strcpy(temp[(*elementnumber)].name, string);

		(*index) = (*elementnumber);

		(*elementnumber) +=1;
	}
	return temp;

}

Movie * update(Movie * movies, int * elementnumber){
	int i, j, numberofsame=0;

	for(i=0;i<(*elementnumber);i++){
		for(j=i+1;j<(*elementnumber);j++){
			if(strcmp(movies[i].name,movies[j].name) ==0){
				movies[i] = movies[j]; /* Update old movies. */
				movies[j].year = -1; /* Makes year of same movie -1. */
				numberofsame++; /* Calculates same movies. */
				break;
			}
		}
	}

	Movie * new; /* Creates a new struct. */

	new = (Movie*)(calloc((*elementnumber)-numberofsame,sizeof(Movie)));

	for(i=0,j=0;i<(*elementnumber);i++){ /* Assigns every element of movies struct to new struct if the year of that movie is not -1. */
		if(movies[i].year != -1){
			new[j] = movies[i];
			j++;

		}
	}
	(*elementnumber) -=numberofsame; /* Decreases element number. */
	return new; /* Returns new struct. */
}

void listof_data(Movie * movies, int elementnumber){
	int operation1, operation2, value, endvalue;

	printf("1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n\n");

	printf("Please Select an operation: ");

	scanf("%d", &operation1);

	printf("1. Single Selection\n2. Multiple Selection");

	scanf("%d", &operation2);

	if(operation2 == 1){
		printf("Enter value:");
		scanf("%d",&value);
		endvalue = value;
	}
	if(operation2 == 2){
		printf("Enter the start value: ");
		scanf("%d",&value);
		printf("Enter the end value: ");
		scanf("%d",&endvalue);
	}

	switch(operation1){
		case 1:
			break;
		case 2:	
			break;
		case 3:
			break;
		case 4:	
			break;
		case 5:
			break;
	}
}


int findmax(Movie * movies, int elementnumber){
	int i=0;

	int max;

	max = movies[0].year; /* Assigns first year of the movies struct. */

	for(i=0;i<elementnumber;i++){ 
		if(movies[i].year>max){ /* If movies[i].year is greater than max, makes max that year. */
			max = movies[i].year;
		}
	}
	return max;
}
