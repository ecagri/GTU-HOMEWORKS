#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSİZE 20


/* I couldn't find enough words on the Internet. And my antonyms and synoynms words cannot be actual synonym or antonym. */

typedef struct words{ /* Words struct. */
	int possibility;
	char name[MAXSİZE];
	struct antonymssynonyms * antsyn; /* Antonyms or synonyms of words. */
	struct words * nextp;
}words;

typedef struct antonymssynonyms{ /* Antonyms or synonyms struct. */
	char name[MAXSİZE];
	struct antonymssynonyms * nextp;
}antonymssynonyms;

void addnode_words(words ** w1, char * name); /* Adds word to the list. */

void addnode_antysn(words * w1, char * name, int option); /* Adds antonyms or a synoymns to a word. */

words * read(char * filename, words * w1, int * wordnumber;); /* Read text files. And creates a list. */

void update_txt(char * filename, int numberofant, words * w1); /* Update the txt, after user quits. */

int existing_account(char * filename, words * w1); /* Check the user is registered. */

words * submenu(words * w1, int * numberofant,int numberofsyn); 

void randomlyask(words * w1, int numberofant, int numberofsyn, int * posofant, int * posofsyn); /* Ask a word from list to user. */

words * add_antoynm(words * w1, char * word, int numberofant); /* Add antonyms word to the list. */

void recorduser(words * w1, char * filename); /* Record user datas to bin file. */

int main(){
	int option, logicvalue, numberofant, numberofsyn, isexist = 0;

	char username[MAXSİZE];

	int lenght, i;

	words * w1; /* Creates a list. */

	w1 = read("antonyms.txt", w1, &numberofant); /* Fill this list with the informations from text files. */

	w1 = read("synonyms.txt", w1, &numberofsyn); /* Fill this list with the informations from text files. */

	do{ /* Main menu. */

		printf("1- Log into existing account\n2- Log into new account\n3- Quit\nYour option: ");

		logicvalue = scanf("%d", &option); /* Gets user option. */

		switch(option){
			case 1:
				/* Log into existing account. */
				printf("Enter your user name: ");

				scanf("%s", username); /* Gets user name. */

				lenght = strlen(username); 

				for(i=0;i<lenght;i++){
					if(username[i] == '\n') break;
				}

				strcpy(&username[i], ".bin"); /* Converts username string to username.bin string. */

				isexist = existing_account(username, w1); /* Checks user exist, if exits, gets datas of user. */

				if(isexist == 1){ /* If user exist, continue. */
					w1 = submenu(w1, &numberofant, numberofsyn); /* Go to submenu. */

					update_txt("antonyms.txt", numberofant, w1); /* Updates the txt files after submenu. */

					recorduser(w1, username); /* Record user datas. */
				}
				break;
			case 2:
				/* Log into new account. */
				printf("Enter your user name: ");

				scanf("%s", username); /* Gets user name. */

				lenght = strlen(username);

				for(i=0;i<lenght;i++){
					if(username[i] == '\n') break;
				}

				strcpy(&username[i], ".bin"); /* Converts username string to username.bin string. */

				w1 = submenu(w1, &numberofant, numberofsyn); /* Go to submenu. */

				update_txt("antonyms.txt", numberofant, w1); /* Updates the txt files after submenu. */

				recorduser(w1, username); /* Record user datas. */
				break;
			case 3:
				break;
			default: /* If user enter a number is 1 or 2 or 3, prints try again. */
				printf("TRY AGAİN\n\n");
				break;
		}
	}while(option != 3 && logicvalue == 1); /* If option is quit or logicvalue is not equal to 1, ends the program. */
	return 0;
}

void addnode_words(words ** w1, char * name){
	struct words *new = malloc(sizeof(words)); /* Creates a new struct. */

	new->antsyn = NULL; /* Makes new struct does not have any antonyms or synonyms. */
    
    strcpy(new->name, name); /* Copies name to new struct name. */

    new->nextp = NULL; /* Makes next pointer of new NULL. */

    if(*w1 == NULL) /* If list is empty, assigns new to w1. */
 		*w1 = new;
    else /* If list is not empty, continues. */
    {
        struct words *last = *w1; /* Creates a last struct, and assigns w1 to last. */

        while(last->nextp != NULL) /*Goes until next pointer of last NULL. */
			last = last->nextp;

        last->nextp = new; /* Assigns new to next pointer of last. */
    }

}

void addnode_antysn(words * w1, char * name, int option){
	struct antonymssynonyms *new = malloc(sizeof(antonymssynonyms)); /* Creates a new struct. */
    
    strcpy(new->name, name); /* Copies name to new struct name. */

    new->nextp = NULL; /* Makes next pointer of new NULL. */

   	if(option == 1) while(w1->nextp != NULL) w1 = w1->nextp; /* If option is 1, goes until end of the w1 list. */

    if(w1->antsyn == NULL) /* If w1->antsyn is NULL, assign new to w1->antsyn. */
 		w1->antsyn = new;
    else /* If list is not empty, continues. */
    {
        struct antonymssynonyms *last = w1->antsyn; /* Creates a last struct, and assigns w1->antsyn to last. */

        while(last->nextp != NULL) last = last->nextp; /*Goes until next pointer of last NULL. */

        last->nextp = new; /* Assigns new to next pointer of last. */
    }    
}

words * read(char * filename, words * w1, int * wordnumber){
	FILE * fptr; 

	words * head = malloc(sizeof(words)); /* Creates a list. */

	int counter = 0, i = 0;

	char * string, c;

	(*wordnumber) = 0;

	fptr = fopen(filename, "r");

	fseek(fptr, 0, SEEK_SET);

	if(fptr == NULL){ /* If fptr is NULL, prints an error. */
		printf("The file couldn't open.\n");
	}
	else{
		while(fscanf(fptr, "%c", &c) != EOF){ /* Gets char by one by. */
			i++;
			if(c == 32 || c == 10){ /* If char equal 32 or 10, continue. */
				if(c == 10) {
					counter = 0;
				}

				string = calloc(i,sizeof(char)); /* Creates a dynamic char array. */

				fseek(fptr, -i, SEEK_CUR); /* Moves the cursor back by i. */

				fscanf(fptr,"%s", string); /* Gets the word. */

				switch(counter){
					case 0: /* If word is the first word of the line, gets it as word. */
						if(strlen(string)>1){
							addnode_words(&w1, string); /* Adds words to list. */
							(*wordnumber) += 1; /* Increases wordnumber by one. */
						}
						break;
					default: /* If word is not the first word of the line, gets it as antoynms or synoynms. */
						if(strlen(string)>1) addnode_antysn(w1, string,1); /* Adds words to antsyn list. */
						break;
				}
				counter++;
				i = 0;
			}

		}
		fseek(fptr, 0, SEEK_SET); /* Moves the cursor to the at the beginning of file. */
		fclose(fptr); /* Closes file. */
	}
	head = w1; /* Keeps the address of w1. */
	
	while(w1 != NULL){ /* Continues until w1 list ends. */
		w1->possibility = 1; /* Makes possibility of words 1. */

		w1 = w1->nextp;
	}	
	return head; /* Returns addres of w1. */
}

int existing_account(char * filename, words * w1){
	int counter = 0, flag = 0;

	FILE * fout;

	fout = fopen(filename, "rb");

	if(fout == NULL){ /* If fout is NULL, prints an error. */
		printf("The user couldn't found. \n");
	}
	
	else{ /* If there is a user, continues. */

		flag = 1; /* Makes flag 1. */

		printf("WELCOME!\n");

		while(w1 != NULL){ /* Continues until w1 list ends. */
			fread(&w1->possibility, sizeof(int), 1, fout); /* Reads binary file and assigns the datas to words possibilities. */

			w1 = w1->nextp;

			counter++;
		}
		fclose(fout); /* Close list. */
	} 
	return flag;	
}

words * submenu(words * w1, int * numberofant, int numberofsyn){
	int option, logicvalue, posofant = 1, posofsyn = 1, isantsyn, i;

	words * head = malloc(sizeof(words)); /* Creates a head list. */

	head = w1; /* Keeps the addres of w1 list. */

	char word[MAXSİZE];
	while(1){
		w1 = head; /* Assign head to w1 every time. */

		printf("1- Ask\n2- Add new word\n3- Log out\nYour option: ");

		logicvalue = scanf("%d", &option); /* Gets user option. */

		switch(option){
			case 1: /* If option is ask, continues. */
				randomlyask(w1, *numberofant, numberofsyn, &posofant, &posofsyn); /* Calls randomlyask function .*/
				break;
			case 2: /* If option is add new word, continues. */
				printf("Do you want add antonym or synonym word(1: antonynm, 0: synonym) :");
				scanf("%d", &isantsyn); /* Gets user option. */

				if(0 == isantsyn || isantsyn == 1){
					printf("Enter the word: ");

					scanf("%s", word); /* Gets the word which user wanting to add. */
				}

				if(isantsyn == 1){ /* If user wants to add antonym continues. */
					/* Add antonym word. */

					w1 = add_antoynm(w1, word, *numberofant); /* Calls add_antonyms function and assing it to w1 list. */

					head = w1; /* Keeps the address of w1 list. */
 
					for(i=0;i<(*numberofant);i++){ /* Continues until antonyms words ends. */
						w1 = w1->nextp;
					}

					w1->possibility = 1; /* Makes new word possibility 1. */

					printf("Enter the first antonym: ");

					scanf("%s", word); /* Gets first antonyms. */

					w1->antsyn = malloc(sizeof(antonymssynonyms)); /* Allocate memory for first antonyms. */

					strcpy(w1->antsyn->name,word); /* Assing new word to words antonyms. */

					printf("Enter the second antonym: ");

					scanf("%s", word); /* Gets second antonyms. */

					w1->antsyn->nextp = malloc(sizeof(antonymssynonyms)); /* Allocate memory for second antonyms. */

					strcpy(w1->antsyn->nextp->name, word); /* Assing new word to words antonyms. */

					w1->antsyn->nextp->nextp = NULL; 

					(*numberofant) += 1; /* Increases antonyms number by one. */

					w1 = head; /* Turns the list to beginning. */
				}
				else if(isantsyn == 0){  /* If user wants to add synonyms continues. */
					/* Add synonym word. */

					addnode_words(&w1, word); /* Add the words to the end of the list. */

					while(w1->nextp != NULL){ /* Continues until last word. */
						w1 = w1->nextp;
					}
					w1->possibility = 1; /* Makes new word possiblity 1. */

					printf("Enter the first antonym: ");

					scanf("%s", word); /* Gets first synonyms. */

					w1->antsyn = malloc(sizeof(antonymssynonyms)); /* Allocate memory for first synonyms. */

					strcpy(w1->antsyn->name,word); /* Assing new word to words synonyms. */

					printf("Enter the second antonym: ");

					scanf("%s", word);

					w1->antsyn->nextp = malloc(sizeof(antonymssynonyms)); /* Allocate memory for second antonyms. */

					strcpy(w1->antsyn->nextp->name, word); /* Assing new word to words synonyms. */

					w1->antsyn->nextp->nextp = NULL;

					numberofsyn++; /* Increases numberofsynoynms by one. */

					w1 = head; /* Turns the list to beginning. */
				}
				break;
		}
		if(option == 3 || logicvalue != 1) break; /* If user wants to exit, exit. */
	}
	return w1;
}

void randomlyask(words * w1, int numberofant, int numberofsyn, int * posofant, int * posofsyn){
	int possibility = (*posofant) + (*posofsyn); /* Makes possibility to sum of possibilities of antonyms and synonyms. */

	words * head = malloc(sizeof(words)); /* Creates a list. */

	words * head2 = malloc(sizeof(words)); /* Creates a list. */

	antonymssynonyms * head3 = malloc(sizeof(antonymssynonyms)); /* Allocate memory for head3. */

	int i, newpossibility, flag, random, istrue = 0 , option;

	char answer[MAXSİZE];

	head = w1; /* Assign the address of w1 to head. */

	possibility = rand()%possibility; 

	if(possibility<(*posofant)){ /* If possibility is less than possibility of antonyms, continue. */
		do{	
			w1 = head; /* Turns the w1 to the begginnig. */

			random = rand()%numberofant; 

			for(i=0;i<random;i++){ /* Goes random step further. */
				w1 = w1->nextp;
			}

			newpossibility = rand()%w1->possibility; /* Gets words possiblity and random it. */

			if(newpossibility == 0){ /* If result of the random is 0, word is found. */
				flag = 1;
			}
		}while(flag != 1);
		printf("What is the antonym of %s:",w1->name);

		scanf("%s", answer); /* Gets answer of user. */

		head3 = w1->antsyn; /* Keeps address of w1->antsyn. */

		while(w1->antsyn != NULL){ /* Continues until w1->antysn ends. */
			if(strcmp(answer, w1->antsyn->name) == 0){ /* Search the answer in w1->antysn list. */
				istrue = 1;
				printf("You know!\n");
				break;
			}
			w1->antsyn = w1->antsyn->nextp;
		}
		w1->antsyn = head3;
		if(istrue == 1) w1->possibility *= 2; /* If user answered question correctly, makes the possiblity of asking the word half. */

		else{ /* If user couldnt know the question, continues. */
			printf("You couldnt know. Do you want to add this word as antoynms of %s(Yes: 1, No: 0) :",w1->name); 

			scanf("%d", &option); /* Gets user option. */

			if(option == 1) addnode_antysn(w1, answer,0); /* If user wants to add the word to antonyms , adds it. */

			strcpy(answer, w1->name);
			w1 = head;
			for(i=0;i<numberofant;i++){
				if(strcmp(answer,w1->name) != 0) w1->possibility *= 2; /* If user didnt know the answer, makes the possibility of asking the other word double. */
				w1 = w1->nextp;
			}
		}
		(*posofsyn) *=2; /* Makes possibility of asking synoynm question double. */

	}
	else{ /* If possibility is not less than possibility of antonyms, continue. */
		for(i=0;i<numberofant;i++){ /* Goes until antonyms list ends. */
			w1 = w1->nextp;
		}
		head2 = w1; /* Keeps the addres of where the synonyms words start. */

		do{
			w1 = head2; /* Turn the beginning of synonyms words start. */

			random = rand()%numberofsyn;

			for(i=0;i<random;i++){ /* Goes random step further. */
				w1 = w1->nextp;
			}

			newpossibility = rand()%w1->possibility; /* Gets words possiblity and random it. */

			if(newpossibility == 0){ /* If result of random is 0, word is found. */
				flag = 1;
			}
		}while(flag != 1);	
		printf("What is the synonym of %s:",w1->name);

		scanf("%s", answer); /* Gets user answer. */

		head3 = w1->antsyn; /* Keeps the adress of synoynms of words. */

		while(w1->antsyn != NULL){ /* Goes until w1->antysn ends. */
			if(strcmp(answer, w1->antsyn->name) == 0){ /* Search the words in synonyms list. */
				istrue = 1;
				break;
			}
			w1->antsyn = w1->antsyn->nextp;
		}
		w1->antsyn = head3; /* Turn the beginnig of synoynms list. */
		if(istrue == 1){
			printf("You knew!\n");

			w1->possibility *= 2; /* If user know the answer, makes the possiblity of asking the word, half. */
		}

		else{ /* If user couldnt know the question, continues. */
			printf("Do you want to add this word as synonyms of %s(Yes: 1, No: 0) :",w1->name);

			scanf("%d", &option); /* Gets user option. */

			if(option == 1) addnode_antysn(w1, answer,0); /* If user wants to add the word to synonyms , adds it. */

			strcpy(answer, w1->name);
			w1 = head2;
			for(i=0;i<numberofsyn;i++){
				if(strcmp(answer,w1->name) != 0) w1->possibility *= 2; /* If user didnt know the answer, makes the possibility of asking the other word double. */
				w1 = w1->nextp;
			}
		}
		(*posofant) *=2; /* Makes possibility of asking antonyms question double. */
	} 

	w1 = head;
}


words * add_antoynm(words * w1, char * word, int numberofant){
	int i;

	antonymssynonyms * head2 = malloc(sizeof(antonymssynonyms)); /* Creates a list. */

	words * head = malloc(sizeof(words)); /* Creates a list. */

	words *keeper = malloc(sizeof(words)); /* Creates a list. */

	words *list; /* Creates a list. */

	keeper = w1; /* Keeps the address of w1 list. */

	for(i=0;i<numberofant;i++){
		addnode_words(&list, w1->name); /* Adds all the antonyms words to new list. */

		head2 = w1->antsyn;

		while(w1->antsyn != NULL){ /* Fills the antonyms of that words .*/
			addnode_antysn(list, w1->antsyn->name, 1);
			w1->antsyn = w1->antsyn->nextp;
		}
		w1->antsyn = head2;

		w1 = w1->nextp;
	}	

	addnode_words(&list, word); /* Adds new word. */

	while(w1 != NULL){ 
		addnode_words(&list, w1->name); /* Adds all the synonyms words to new list. */
		head2 =w1->antsyn;
		while(w1->antsyn != NULL){
			addnode_antysn(list, w1->antsyn->name, 1); /* Fills the synonyms of that words .*/
			w1->antsyn = w1->antsyn->nextp;
		}
		w1->antsyn = head2;
		w1 = w1->nextp;
	}

	w1 = keeper;

	head = list;

	for(i=0;i<numberofant;i++){ /* Fills the possiblity of antonyms words. */
		list->possibility = w1->possibility;
		w1 = w1->nextp;
		list = list->nextp;
	}

	list->possibility = 1; /* Fills the possiblity of new word. */

	list = list->nextp;

	while(w1 != NULL){
		list->possibility = w1->possibility; /* Fills the possiblity of synonyms words. */
		w1 = w1->nextp;
		list = list->nextp;
	}

	return head; /* Return address of new list. */
}

void update_txt(char * filename, int numberofant, words * w1){
	FILE * fptr;

	antonymssynonyms * head;

	int i;

	fptr = fopen(filename, "w"); 

	if(fptr != NULL){ /* Updates antonyms.txt. */
		for(i=0;i<numberofant;i++){
			fprintf(fptr, "%s",w1->name);

			head = w1->antsyn;

			while(w1->antsyn != NULL){
				fprintf(fptr, " %s",w1->antsyn->name);
				w1->antsyn = w1->antsyn->nextp;
			}
			w1->antsyn = head;
			w1 = w1->nextp;
			fprintf(fptr, "\n");
		}
		fclose(fptr);
	}

	fptr = fopen("synonyms.txt", "w");

	if(fptr != NULL){ /* Updates synonyms.txt. */
		while(w1 != NULL){
			fprintf(fptr, "%s",w1->name);

			head = w1->antsyn;

			while(w1->antsyn != NULL){
				fprintf(fptr, " %s",w1->antsyn->name);
				w1->antsyn = w1->antsyn->nextp;
			}
			w1->antsyn = head;
			w1 = w1->nextp;
			fprintf(fptr, "\n");
		}
		fclose(fptr);
	}
}

void recorduser(words * w1, char * filename){
	FILE * fptr;

	fptr = fopen(filename, "wb");

	while(w1 != NULL){ /* Continues until w1 list ends. */
		fwrite(&w1->possibility, sizeof(int), 1, fptr); /* Record the possiblities of words to username.bin. */
		w1 = w1->nextp;
	}
	fclose(fptr);
}
