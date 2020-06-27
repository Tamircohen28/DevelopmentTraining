#define _CRT_SECURE_NO_WARNINGS
/* 
Author: Tamir Cohen
Date: 27/06/2020
Description:
Writing a function that counts how many diffrenet words in a file.
a word is a string seperated by space containing only alphabatic characters.
*/
// <----------- Includes ------------->
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// <----------- Defines ------------->
#define WORD_BASE_LEN 20
#define NUM_OF_WORDS 1000
#define FILE_PATH "C:\\Users\\Tamir Cohen\\Desktop\\aladdin.txt"


bool IsWord(char *cptr) {
	// checkes if a word is all letters
	char *index = cptr;

	while (*index)
	{
		if (isalpha((unsigned char)*index) == 0) {
			return false;
		}
		index++;
	}
	return true;
}

char* GetWord(FILE *fptr) {
	// returns the next word in a file
	char c;
	char *word;
	size_t WordLen = 0;
	size_t current_size = WORD_BASE_LEN;

	// aloc default space
	word = (char *)calloc(current_size, sizeof(char));

	if (!word) {
		printf("\n[GetWord]: Enable to calloc\n");
		exit(EXIT_FAILURE);
	}

	// what about last word
	while ((c = fgetc(fptr)) != EOF)
	{
		// if we reached a valid end of word
		if (c == ' ' || c == '\n' || c == '\t') {

			// only if i found somthing
			if (WordLen > 0) {
				word[WordLen] = '\0';
				return word;
			}
		}
		else {
			// about to overflow
			if (WordLen == current_size) {
				// allocating more memory
				word = (char *)realloc(word, current_size * 2);
				current_size = current_size * 2;

				if (!word) {
					printf("\n[GetWord]: Enable to realloc\n");
					exit(EXIT_FAILURE);
				}
			}

			// insert next char
			word[WordLen] = c;
			WordLen++;
		}
	}

	if (WordLen > 0) {
		word[WordLen] = '\0';
		return word;
	}
	return NULL;
}


int main() {
	FILE *fptr = fopen(FILE_PATH, "r");
	size_t words_index = 0;
	size_t current_size = NUM_OF_WORDS;
	char **words = (char **)calloc(NUM_OF_WORDS, WORD_BASE_LEN * sizeof(char));
	char *current_word = NULL;
	bool insert = true;

	if (!fptr) {
		printf("\nEnable to open file %s\n", FILE_PATH);
		exit(EXIT_FAILURE);
	}

	// going over the file until i reach the end
	while ((current_word = GetWord(fptr)) != NULL)
	{
		insert = true;
		if (IsWord(current_word)) {
			for (size_t i = 0; i < words_index; i++)
			{
				// found the same word again
				if (strncmp(current_word, words[i], sizeof(current_word)) == 0) {
					insert = false;
					break;
				}
			}

			// need to insert new word
			if (insert) {

				// overflow, allocate more memory
				if (words_index == current_size) {
					words = (char **)realloc(words, current_size * 2);
					if (!words) {
						printf("\n[main]: Enable to realloc\n");
						exit(EXIT_FAILURE);
					}
					current_size = current_size * 2;
				}
				
				// allocate memory for new word
				words[words_index] = (char *)calloc(strlen(current_word) + 1, sizeof(char));
				if (!words[words_index]) {
					printf("\n[main]: Enable to calloc %s\n", FILE_PATH);
					exit(EXIT_FAILURE);
				}

				strncpy(words[words_index], current_word, sizeof(words[words_index]));
				words_index++;
			}

		}
	}
	free(current_word);
	current_word = NULL;
	free(words);
	words = NULL;

	printf("\nNum of diffrent words in file is %d\n", words_index);
	return 0;
}