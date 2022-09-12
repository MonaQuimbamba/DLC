
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"
#include "math.h"

#include <sys/types.h>
#include <sys/resource.h>


unsigned long int cputime()
{
  struct rusage rus;

  getrusage (0, &rus);
  return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}


int main(int argc, char* argv[])
{
  unsigned int bit_size;
  unsigned int i;
  unsigned int n;
  unsigned long int start;

  mpz_t z_fact;
  

  if (argc != 2)
  {
    printf("Usage : %s n  (calcule la factorielle de n)\n", argv[0]);
    exit(-1);
  }
  
  n = atoi(argv[1]);
  
  start = cputime();

  mpz_init(z_fact);
  mpz_set_ui(z_fact, 1);

  i = 1;
  while (i <= n)
  {
    mpz_mul_ui(z_fact, z_fact, i);
    i++;
  }
  
  printf("\n");
  printf("Computation time : %lu ms\n", cputime() - start);
  printf("\n");
  printf("%u! = ", n);
//  gmp_printf("%Zu\n",z_fact);
  printf("\n");
  
  bit_size = mpz_sizeinbase(z_fact, 2);
  printf("%u bits, %u chiffres\n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));

  printf("\n");

  mpz_clear(z_fact);
  
  return 0;
}

