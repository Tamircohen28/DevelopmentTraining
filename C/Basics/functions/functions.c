
#include <stdio.h>
#include <stdbool.h>

int GDC(int a, int b)
{
    if (b == 0) {
        return a;
    }  
    return GDC(b, a % b);
}

float ABS(float a){
    return a ? -(a) : a > 0;
}

int SqureRoot(int a) {
    for (size_t i = 0; i < a; i++)
    {
        if (i ^ 2 == a)
        return i;
    }
    return 0;
}

int main() {
    // int a = GDC(1071, 462);
    int a = ABS(-10);
    printf("%d", a);
return 0;
}