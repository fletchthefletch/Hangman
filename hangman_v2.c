/*
Created by Fletcher van Ameringen on 9/03/2019
Enjoy!!

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_WORDS_POSSIBLE 213

void guess_show(char lett);
bool is_letter_in_word(char *str);
void printer();
void read_word();
void computer_read();
int load_rand();

char word[40], guess_word[40], guessed_letters[40];
bool keep_playing = true, isin = false, used_before, comp_player = false;;
int word_len, fail, g_len;
int max_num = NUMBER_OF_WORDS_POSSIBLE; // number of words in directory
int random; 

FILE *f;

int main() {
	int i;
	char choice[10];
	
	strcpy(choice, "y");
	// preset game choice to 'play'
	printf("___________________________________\n");
	printf("********Welcome to Hangman!********\n");
	printf("___________________________________\n");
	
	while (strcmp(choice, "y") == 0) {
		comp_player = false;
		printf("\n\n");
		read_word();
		while (fail < 6) {
			char letter[10];
			int correct;
			used_before = false;
			
			printer();
			printf("\n\n\n\n");
			printf(">> P2 guess a letter: ");

			fgets(letter, 10, stdin);
			letter[strlen(letter)-1] = '\0';

			for (i = 0; i < g_len; i++) {
				if (guessed_letters[i] == letter[0]) {
					used_before = true;
				}
			}
			while (used_before) {
			   used_before = false;				
				printf(">> P2 guess a different letter: ");
				fgets(letter, 10, stdin);
				letter[strlen(letter)-1] = '\0';
				for (i = 0; i < g_len; i++) {
					if (guessed_letters[i] == letter[0]) {
						used_before = true;
					}
				}				
			}
			printf("\n");
			isin = is_letter_in_word(letter);
			
			if (isin == false) {
				fail++;
			}
			guessed_letters[g_len] = letter[0];
			g_len++;
			guessed_letters[g_len] = '\0';
			guess_show(letter[0]);
			printf("Guessed Letters: "); 
			for (i = 0; i < g_len-1; i++) {
				printf("%c, ", guessed_letters[i]);
			}
			printf("%c\n_____________________\n\n\n", guessed_letters[i]);
			correct = strcmp(guess_word, word);
			if (correct == 0) {
				printf("Player 2 wins!\n\n");
				break;
			}
	}
		if (fail == 6) {
			printer();
			printf("Sorry, you could not save the man today :-(\n");
			if (!comp_player) {
				printf("Player 1 wins!\n");
			} else {
				printf("Computer wins!\n");
			}
		}
		printf("The word was: %s", word);

		printf("\n\n");
		printf("Would you like to play again? y/n: ");
		fgets(choice, 10, stdin);
		choice[strlen(choice)-1] = '\0';
		while ((strcmp(choice, "y") != 0) && (strcmp(choice, "n") != 0)) {
			printf("Would you like to play again? y/n: ");
			fgets(choice, 10, stdin);
			choice[strlen(choice)-1] = '\0';					
		}
	}
	printf("Thank you for playing!\n");
	exit(0);
}

/* Check to see if a letter is in Player 1's word */
bool is_letter_in_word(char *str) {
	int i = 0;
	while (i < word_len) {
		if (word[i] == str[0]) {
			return true;
		}
		i++;
	}
	return false;
}

/* Show the word as it has been guessed thus far */
void guess_show(char lett) {
	int i = 0, k;
	bool is_here = false;
	
	while (i < word_len) {
		if (word[i] == lett) {
			guess_word[i] = lett;
			is_here = true;
			printf("Nice!\n");
		} 
		
		for (k = 0; k < g_len; k++) {
			if (guessed_letters[k] == lett) {
				is_here = true;
				break;
			}
		}
		if (!is_here) {
			guess_word[i] = '*';
			// Hide letters that have not been guessed
		}
		i++;
		is_here = false;
	}
	printf("\n");
	printf("Word: %s\n", guess_word);
}

/* Read in Player 1's word, and assign important info to globals */
void read_word() {
	char mode[10];
	int i;
	
	printf("Player vs Player (1), or Computer vs Player (2)? ");
	fgets(mode, 10, stdin);
	mode[strlen(mode)-1] = '\0';
	while ((strcmp(mode, "1") != 0) && (strcmp(mode, "2") != 0)) {
		printf("Player vs Player (1), or Computer vs Player (2)? ");
		fgets(mode, 10, stdin);
		mode[strlen(mode)-1] = '\0';
	}
	if (strcmp(mode, "1") == 0) {
		printf(">> Player 1 enter a lowercase word: ");
		fgets(word, 40, stdin);
		word[strlen(word)-1] = '\0';
	} else if (strcmp(mode, "2") == 0) {
		comp_player = true; 
		printf("Selecting random word...\n");
		computer_read();
		printf("Word has been chosen...\n");
	}
	
	word_len = strlen(word);
	for (i = 0; i < word_len; i++) {
		guess_word[i] = '*';
	}
	strcpy(guessed_letters, "\0");
	
	guess_word[i] = '\0';
	printf("\n");
	printf("Word: %s\n", guess_word);
	printf("Length: %d\n\n", word_len);
	fail = 0;
	g_len = 0;
}

void computer_read() {
	int i;
	char temp[100];
	
	strcpy(temp, "\0");
	f = fopen("words.txt", "r");
	if (f == NULL) {
		printf("File not found.\n");
		exit(0);
	}

	random = load_rand();
	i = 0;
	while (fgets(temp, 100, f) != NULL) {
		if (i == random) {
			break;
		}
		i++;
	}
	fclose(f);
	temp[strlen(temp)-1] = '\0';
	strcpy(word, temp);
	printf("Word Number: %d / %d\n", random, max_num);
}

int load_rand() {
	srand((unsigned) time(0));
	random = (rand() + rand() + rand() + rand()) % max_num + 1;
	while (random > max_num) {
		random /= 10;
	}
	return random;
}


/* Print the hangman 'picture' - differing 
according to how man incorrect letters have been entered */
void printer() {
	printf("|\t,-------|\n");
	if (fail == 0) {
		printf("|\t\t|\n");
		printf("|\t\t|\n");
		printf("|\t\t|\n");
	} else if (fail == 1) {
		printf("|\to\t|\n");
		printf("|\t\t|\n");
		printf("|\t\t|\n");
	} else if (fail == 2) {
		printf("|\to\t|\n");
		printf("|       |   	|\n");
		printf("|\t\t|\n");				
	} else if (fail == 3) {
		printf("|\to\t|\n");
		printf("|      -|   	|\n");
		printf("|\t\t|\n");	
	} else if (fail == 4) {
		printf("|\to\t|\n");
		printf("|      -|-  	|\n");
		printf("|\t\t|\n");
	} else if (fail == 5) {
		printf("|\to\t|\n");
		printf("|      -|-  	|\n");
		printf("|        \\      |\n");
	} else if (fail == 6) {
		printf("|\to\t|\n");
		printf("|      -|-  	|\n");
		printf("|      / \\      |\n");
	}
	printf("|\t\t|\n");
	printf("|______________/|_\n");
}
