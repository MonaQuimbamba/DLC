
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gmp.h"

#define N 10

int main(int argc, char* argv[])
{
  unsigned int i;

  gmp_randstate_t prng;

  mpz_t z_n[N];
  
  
  gmp_randinit_default(prng);
  gmp_randseed_ui(prng, time(NULL));

  for (i = 0; i < N; i++)
    mpz_init(z_n[i]);
  
  for (i = 0; i < N; i++)
    mpz_urandomb(z_n[i], prng, 100);
  
  printf("\n");
  for (i = 0; i < N; i++)
    gmp_printf("%u (%p) : %Zd\n", i, z_n[i], z_n[i]);

  printf("\n");
  i = 0;
  while (i < 10)
  {
    gmp_printf("%u (%p) : %Zd  =>  ", i, z_n[i], z_n[i]);
    if (mpz_odd_p(z_n[i]))
      printf("impair\n");
    else
      printf("pair\n");
    i++;
  }
/*  
*/
  printf("\n");
  i = 0;
  while (i < 10)
  {
    gmp_printf("%u (%p) : %Zd  =>  ", i, z_n[i], z_n[i]);
    if (mpz_odd_p(z_n[i++]))
      printf("impair\n");
    else
      printf("pair\n");
  }
/*    
*/  
  printf("\n");

  gmp_randclear(prng);

  for (i = 0; i < N; i++)
    mpz_clear(z_n[i]);
  
  return 0;
}

