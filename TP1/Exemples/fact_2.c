
#include <math.h>
#include <stdio.h>

#include "gmp.h"

int main()
{
  unsigned int n;
  unsigned int fact = 1;

  unsigned long int fact_long = 1;

  unsigned long long int fact_long_long = 1;

  mpz_t z_fact;
  

  mpz_init(z_fact);
  mpz_set_ui(z_fact, 1);
  
  n = 1;
  while (n <= 25)
  {
    fact *= n;
    fact_long *= n;
    fact_long_long *= n;
    mpz_mul_ui(z_fact, z_fact, n);
    
    gmp_printf(" n = %2u      n! (long long) = %22llu      n! (mpz_t) = %Zu\n", n, fact_long_long, z_fact);

    n++;
  }
  
  mpz_clear(z_fact);
  
  return 0;
}

