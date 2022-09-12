
#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"

int main()
{
  char sz_n[1000];
  int result;  
  mpz_t z_n;
  
    
  mpz_init(z_n);

  printf("\n");
  printf("Saisissez la valeur de n : ");
  scanf("%s", sz_n);
    
  mpz_set_str(z_n, sz_n, 0);
  
  result = mpz_probab_prime_p(z_n, 4);
  
  printf("\n");
  printf("mpz_probab_prime_p() retourne %d  =>  n est ", result);
  switch (result)
  {
    case 0 :
      printf("composé\n");
      break;

    case 1 :
      printf("probablement premier\n");
      break;

    case 2 :
      printf("premier\n");
      break;
  }
  printf("\n");
  
  mpz_clear(z_n);
  
  return 0;
}
