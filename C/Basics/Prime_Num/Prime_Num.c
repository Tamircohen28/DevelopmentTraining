
#include <stdio.h>
#include <stdbool.h>
#define C_ARRAY_SIZE 1000

int main() {

int primes[C_ARRAY_SIZE] = {2, 3};
int primes_index = 2;
bool found = false;
for (size_t num = primes[primes_index - 1] + 1; num < C_ARRAY_SIZE; num++)
{
    for (size_t i = 0; i < primes_index; i++)
    {   
        // if the number is not primery
        if (num % primes[i] == 0 && num != primes[i])
        {
            goto Not_prime;
        }
    }
    // number is a prime
    primes[primes_index] = num;
    primes_index++;

    Not_prime: continue;
}

printf("Found %d Prime numbers:\n", primes_index);
for (size_t i = 0; i < primes_index; i++)
{   
    printf("%d\n", primes[i]);
}

return 0;

}