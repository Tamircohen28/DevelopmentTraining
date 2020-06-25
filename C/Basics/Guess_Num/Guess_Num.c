/*
Author: Tamir Cohen
Description: This progrem prints my name.
Date: 24/03/2020
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main() {

time_t t;
srand((unsigned) time(&t));
int rand_num = rand() % 21; // randome number between 0 - 20
int try;
bool Result = false;

printf("This is guessing game.\nI have chosen a number between 0 and 20 which you must guess.\n");

for (uint8_t i = 5; i >= 1; i--)
{
    printf("\nYou have %d tries left\n", i);
    printf("Enter your guess: ");
    scanf("%d", &try);

    if (try > rand_num) {
        printf("Sorry %d is wrong. My numer is less than that\n", try);
    }

    else if (try < rand_num) {
        printf("Sorry %d is wrong. My numer is bigger than that\n", try);
    }

    else if (try == rand_num) {
        Result = true;
        break;
    }
}

if (Result) {
    printf("\nCongratulations. You guessed it!");
}
else
{
    printf("\nYou are out of tries, My number was %d", rand_num);
}

return 0;
   /*
   to build project use ctrl+shift+bד
   to run project using exstention: ctrl+alt+n 
   */
}