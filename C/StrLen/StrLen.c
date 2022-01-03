/* 
Author: Tamir Cohen
Date: 25/06/20
Description: Strlen exresice using pointers
*/ 
#include <stdio.h>
#include <stdbool.h>

int Strlen(const char *ptr) {
    const char *index = ptr;

    // while not '\0'
    while (*index)
    {
        index++;
    }
    return index - ptr;
}

int main() {
    printf("\nString length is %d", Strlen("tamir cohen"));
return 0;

}