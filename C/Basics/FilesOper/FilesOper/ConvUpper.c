#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define TEMP_FILE_NAME "Temp.txt"
#define ORIGIN_FILE_NAME "C:\\Users\\Tamir Cohen\\Desktop\\DevelopmentTraining\\C\\Basics\\FilesOper\\test.txt"


bool MakeUpper(FILE *fptr) {
	/* function has to recieve file ptr that can be read & write */

	// open temporary file
	FILE *ftemp_ptr = fopen(TEMP_FILE_NAME, "w+");

	if (!ftemp_ptr) {
		return false;
	}

	// write all upper to tempory file
	char c;
	while ((c = fgetc(fptr)) != EOF)
	{
		fputc(toupper(c), ftemp_ptr);
	}

	// going back to start of the file
	rewind(fptr);
	rewind(ftemp_ptr);

	// copy temp to original
	while ((c = fgetc(ftemp_ptr)) != EOF)
	{
		fputc(c, fptr);
	}
	fclose(ftemp_ptr);
	ftemp_ptr = NULL;

	remove(TEMP_FILE_NAME);
	return true;
}



int main3() {
	FILE *fptr = fopen(ORIGIN_FILE_NAME, "r+");

	if (!fptr) {
		printf("\nCould not open file");
		return(-1);
	}

	MakeUpper(fptr);
	fclose(fptr);
	fptr = NULL;
	return 0;
}