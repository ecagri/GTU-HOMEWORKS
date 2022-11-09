#include <stdio.h>

#include <string.h>

#define N 30

void fix_spelling_error(char text[15], char dictionary[15]); 

void possible_answers(char dictionary[15],char word[N]);

void find_best_correction(char word[N], char possible[N], char max_possible[N]);

int seperate_punctuations(char word[N], char * punctuation, char firstpart[N], char secondpart[N]);

void makeitsmall(char word[N]);

void makeitcapital(char word[N], char max_possible[N]);


int main(){

	char text[15] = "text.txt"; /* Assigns name of the text file to char array.*/

	char dictionary[15] = "dictionary.txt"; /* Assigns name of the dictionary file to char array. */

	fix_spelling_error(text,dictionary); /* Call the fix_speelling_error functions with name of files parameters. */

	return 0;
}

void fix_spelling_error(char text[15], char dictionary[15]){
	char word[N]; /* Creates a char array. */

	char firstpart[N]; /* Creates a char array. */

	char secondpart[N]; /* Creates a char array. */

	char punctuation; /* Creates a char variable to keep the punctuation. */

	int flag; /* A flag for is there a punctuation in the word. */

	FILE * fptr; 

	fptr = fopen(text, "r+"); /* Opens the file in r+ mode. */

	while(fscanf(fptr,"%s",word) != EOF){ /* Gets string until end of the file. */

		fseek(fptr,-strlen(word),SEEK_CUR); /* Return the cursor by word lenght. */

		do{

			if(strlen(word) < 2 ){ /* If lenght of the word is less than 2, does not check, prints the word. */

				fprintf(fptr,"%s",word);	

				break;
			}
			/* If lenght of the word is not less than 2 continue. */

			flag = seperate_punctuations(word, &punctuation, firstpart, secondpart); /* Assigns seperate_punctuations function to flag. */

			if(flag == 1){ /* If there is a punctuation, continue. */
				possible_answers(dictionary, firstpart); /* Corrects the part before punctuation. */

				fprintf(fptr,"%s%c",firstpart, punctuation); /* Prints the correct word and punctuation. */

				strcpy(firstpart,secondpart); /* Copy secondpart of the word to first part of the word. */

				strcpy(word,firstpart); /* Copy firstpart of the word to word. */
			}

			else{ /* If theere is not a punctuation, continue. */
				possible_answers(dictionary, firstpart); /* Corrects the word. */

				fprintf(fptr,"%s", firstpart); /* Prints the correct word. */
			}

		}while(flag>0); /* This loops continues until flag = 0. */
	}
	fclose(fptr); /* Closes the file. */
}

void possible_answers(char dictionary[15],char word[N]){ /* Gets word and the name of the dictionary as parameters. */
	char possible[N]; /* Creates a char array. */

	char max_possible[N]; /* Creates a char array. */

	char temp_word[N]; /* Creates a char array. */

	strcpy(temp_word,word); /* Copies the word to temp_word variable. */

	strcpy(max_possible,""); /* Cleans max_possible variable. */

	strcpy(possible,""); /* Cleans possible variable. */

	FILE *fptr;

	fptr = fopen(dictionary,"r"); /* Opens the dictionary file in r mode. */

	makeitsmall(word); /* Converts capital letters into small letters. */

	while(fscanf(fptr,"%s",possible) != EOF){ /* Gets possible words from the dictionary file. */

		find_best_correction(word, possible, max_possible);

		if(strlen(word)<2){ /* If lenght of the word is less than 2, does not change it. */
			strcpy(max_possible,word); /* Copies word to max_possible variable. */
			break;
		}

		if(strcmp(word,possible) == 0){ /* If word and possible word is same, does not change the word. */
			strcpy(max_possible,word); /* Copies word to max_possible variable. */
			break;
		}
	}
	if(max_possible[0] == '\0'){ /* If at the end of the check, max_possible variable is empty, does not change the word. */
		strcpy(max_possible,word); /* Copies word to max_possible variable. */
	}	

	makeitcapital(temp_word, max_possible); /* Converts letters which is capital letters at the beginning of the function into capital letters. */

	strcpy(word,max_possible); /* Copies max_possible to word to return. */

	fclose(fptr); /* Closes the file. */

}

void find_best_correction(char word[N], char possible[N], char max_possible[N]){ /* Gets word, possible and max_possible variable as parameters. */
	int i;

	int counter = 0;

	int lenword = strlen(word); /* Assigns lenght of the word to lenword variable. */

	int lenpossible = strlen(possible); /* Assigns lenght of the possible to lenpossible variable. */

	int lendifference = lenword - lenpossible; /* Finds lenght difference. */

	int flag = 0;

	char differ; /* This is a variable to compare consonant to wovel. */

	for(i=0;i<N;i++){ 
		if(word[i] == '\0' || possible[i] == '\0') break; /* If string of word or possible ends, break the loop. */

		if(word[i] == possible[i]) counter++; /* Compares the i. element of word with i. element of possible, if they are equal, increases counter by one. */

		else differ = possible[i]; /* If they are not equal, takes i. element of possible. */
	}

	if(counter == lenword-1 || counter == lenpossible-1){
		if(-2 < lendifference && lendifference < 2) flag = 1;
	}

	if(flag == 1 && max_possible[0] == '\0') strcpy(max_possible,possible); /* If flag = 1 and max_possible is not empty array, copies possible to max_possible. */

	if(flag == 1){ /* If flag = 1, continue. */
		if(differ == 97 || differ == 101 || differ == 105 || differ == 111 || differ == 117){ /* If char difference is wovel letter, continue. */
			if(max_possible[0]!= '\0') strcpy(max_possible,possible); /* If max_posibble is not empty array, copies possible to max_possible. */
		}
	}
}

int seperate_punctuations(char word[N], char * punctuation, char firstpart[N], char secondpart[N]){ /* This function gets word, and seperate it words. */
	int i;

	int flag; /* It is flag for is there a puntuation or not .*/

	for(i=0;i<N;i++){
		if(word[i] == '\0'){ /* If string ends, flag equals to 0, and breaks the loop. */
			flag = 0;
			break;
		}
		if(((47<word[i] && word[i]<58) || (64<word[i] && word[i]<91) || (96<word[i] && word[i]<123))!=1){ /* If i. index of word, not equal a letter or number, it is punctuation. */
			flag = 1;

			(*punctuation) = word[i]; /* Assign i. index of word to punctuation to return. */

			break;
		}
	}

	if(i==N) flag = 0; /* If loop does not break until end of the loop, flag equals 0. */

	strncpy(firstpart, &word[0], i); /* Copies word at the beginning to index i to firstpart variable. */

	firstpart[i] = '\0'; /* Makes firstpart variable string. */

	if(flag == 1){ /* If there is a punctuation, continues. */
		strcpy(secondpart,&word[i+1]);  /* Copies word from i+1. index to at the end of the string, to secondpart variable. */
	}

	return flag; /* Returns flag. */
}

void makeitsmall(char word[N]){ /* Gets word as parameter and makes it letters small. */
	int i;

	for(i=0; i<N; i++){
		if(word[i] == '\0') break;

		if(64<word[i] && word[i]<91){ /* If i. index of word is a capital letter, makes it small. */
			word[i]+=32;
		}
	}
}


void makeitcapital(char temp_word[N], char max_possible[N]){ /* Gets the first version of word and makes max_possible letters capital. */
	int i;

	for(i=0; i<N; i++){
		if(temp_word[i] == '\0') break;

		if(64<temp_word[i] && temp_word[i] < 91){ /* If first version of i. index of word  is capital, makes i. index of max_possible capital. */
			max_possible[i]-=32;
		}
	}
}
