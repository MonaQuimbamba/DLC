
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gmp.h"

int main(int argc, char* argv[])
{
  gmp_randstate_t prng;

  signed int i;
    
  unsigned int bit_size;
  unsigned int n;

  mpz_t z_base;
  mpz_t z_exponent;
  mpz_t z_modulus;
  mpz_t z_result;
  
  gmp_randinit_default(prng);
  gmp_randseed_ui(prng, time(NULL));

  mpz_inits(z_base, z_exponent, z_modulus, z_result, NULL);
  
  if (argc != 2)
  {
    printf("Usage : %s bit_size\n", argv[0]);
    exit(-1);
  }
  
  bit_size = atoi(argv[1]);
  
  mpz_urandomb(z_base, prng, bit_size);
  mpz_urandomb(z_exponent, prng, bit_size);
  mpz_urandomb(z_modulus, prng, bit_size);
  
/*
  mpz_set_ui(z_result, 1);
  for (i = bit_size - 1; i >= 0; i--)
  {
    // result <-- result^2 mod modulus
    mpz_mul(z_result, z_result, z_result);
    mpz_mod(z_result, z_result, z_modulus);
    
    if (mpz_tstbit(z_exponent, i) == 1)
    {
      // result <-- result * base mod modulus
      mpz_mul(z_result, z_result, z_base);
      mpz_mod(z_result, z_result, z_modulus);      
    }
  }
  
  printf("\n");
  gmp_printf("%Zd ^ %Zd mod %Zd = %Zd\n", z_base, z_exponent, z_modulus, z_result);
  printf("\n");
*/
  
  mpz_powm(z_result, z_base, z_exponent, z_modulus);
  
  printf("\n");
//  gmp_printf("%Zd ^ %Zd mod %Zd = %Zd\n", z_base, z_exponent, z_modulus, z_result);
  printf("\n");
  
  gmp_randclear(prng);

  mpz_clears(z_base, z_exponent, z_modulus, z_result, NULL);
  
  return 0;
}

