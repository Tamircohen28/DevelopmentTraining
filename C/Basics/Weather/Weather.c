
#include <stdio.h>
#include <stdbool.h>

#define MONTHS 12
#define YEARS 5
#define START_YEAR 2010

int main() {

// initialize rainfall data for 2011-2015
float rain[YEARS][MONTHS] =
{
    {4.3,4.3,4.3,3.0,2.0,1.2,0.2,0.2,0.4,2.4,3.5,6.6},
    {8.5,8.2,1.2,1.6,2.4,0.0,5.2,0.9,0.3,0.9,1.4,7.3},
    {9.1,8.5,6.7,4.3,2.1,0.8,0.2,0.2,1.1,2.3,6.1,8.4},
    {7.2,9.9,8.4,3.3,1.2,0.8,0.4,0.0,0.6,1.7,4.3,6.2},
    {7.6,5.6,3.8,2.8,3.8,0.2,0.0,0.0,0.0,1.3,2.6,5.2}
};

float sum;
float tsum = 0.0;
float months_rain[MONTHS];
// avarage for every year
printf("YEAR \t RAINFALL (Inches) \n");

for (size_t i = 0; i < YEARS; i++)
{
    sum = 0.0;
    for (size_t j = 0; j < MONTHS; j++)
    {
        sum += rain[i][j];
        months_rain[j] += rain[i][j];
    }
    tsum += sum;
    printf("%d \t %.1f \n", START_YEAR + i, sum);
}
printf("The yearly avarage is %.1f inches.\n", tsum/YEARS);
printf("\nMONTHLY AVERAGES:\n");
printf("Jan\tFeb\tMar\tApr\tMay\tJun\tJul\tAug\tSep\tOct\tNov\tDec\n");

for (size_t i = 0; i < MONTHS; i++)
{
    printf("%.1f\t", months_rain[i]/YEARS);
}

return 0;

}