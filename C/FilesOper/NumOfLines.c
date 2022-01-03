#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

int NumOfLines(FILE *fptr) {
	char c;
	int count = 0;

	while ((c = fgetc(fptr)) != EOF)
	{
		if (c == '\n') {
			count++;
		}
	}
	// N times '\n' means N + 1 rows
	return (count + 1);
}

int main2() {
	FILE *fptr = fopen("C:\\Users\\Tamir Cohen\\Desktop\\DevelopmentTraining\\C\\Basics\\FilesOper\\test.txt", "r");
	
	if (fptr == NULL)
	{
		printf("File does not exist\n");
		return -1;
	}

	int Nlines = NumOfLines(fptr);
	fclose(fptr);
	fptr = NULL;

	printf("The file has %d lines", Nlines);
	return 0;
}