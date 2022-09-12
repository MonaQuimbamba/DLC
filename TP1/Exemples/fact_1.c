
#include <math.h>
#include <stdio.h>

int main()
{
  unsigned int n;
  unsigned int fact = 1;

  unsigned long int fact_long = 1;

  unsigned long long int fact_long_long = 1;


  printf("\n");
  printf("Taille en bits du type unsigned int : %lu\n", 8 * sizeof(unsigned int));
  printf("\n");
  n = 1;
  while (n <= 25)
  {
    fact *= n;
    printf(" n = %2u      n! (int) = %12u\n", n, fact);
    n++;
  }

  printf("\n");
  printf("\n");
  printf("Taille en bits du type unsigned long int : %lu\n", 8 * sizeof(unsigned long int));
  printf("\n");
  n = 1;
  while (n <= 25)
  {
    fact_long *= n;
    printf(" n = %2u      n! (long) = %22lu\n", n, fact_long);
    n++;
  }

  printf("\n");
  printf("\n");
  printf("Taille en bits du type unsigned long long int : %lu\n", 8 * sizeof(unsigned long long int));
  printf("\n");
  n = 1;
  while (n <= 25)
  {
    fact_long_long *= n;
    printf(" n = %2u      n! (long long) = %22llu\n", n, fact_long_long);
    n++;
  }
  
  return 0;
}
