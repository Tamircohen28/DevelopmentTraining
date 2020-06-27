#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define FILE_NAME "C:\\Users\\Tamir Cohen\\Desktop\\DevelopmentTraining\\C\\Basics\\FilesOper\\test.txt"

void fprint_revers(FILE *fptr) {

	// going to the end of the file
	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);

	for (int i = size - 1; i >= 0; i--)
	{
		fseek(fptr, i, SEEK_SET);
		printf("%c", fgetc(fptr));
	}
}

int main() {

	FILE *fptr = fopen(FILE_NAME, "r+");

	if (!fptr) {
		printf("\nCould not open file");
		return(-1);
	}

	fprint_revers(fptr);
	fclose(fptr);
	fptr = NULL;
	return 0;
}