#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmp.h"

/*
 *Modifiez le programme de l’exercice pr ́ec ́edent pour que les nombres
 g ́en ́er ́es aient une taille :
 — exactement  ́egale `a k bits
 — au plus  ́egale `a k chiffres d ́ecimaux
 — exactement  ́egale `a k chiffres d ́ecimaux
 *
 *
 * */


int main(int argc,char* argv[])
{
     unsigned int k;
     mpz_t rand;
     mpz_t bord_max;
     mp_bitcnt_t rand_b;
     unsigned int bit_size;
     unsigned long int seed;
     int isprime;
     unsigned int chiffre;


     if (argc != 2){
     	printf("Usage : %s k   \n", argv[0]);
     	exit(-1);
     }


     k= atoi(argv[1]);
     mpz_inits(rand,bord_max,NULL);
     mpz_set_str(bord_max, "8497391829048797593184398274916519319103580", 0);
     
     printf("Entrer la seed :");
     scanf("%ld", &seed);  
   
   
  

     gmp_randstate_t mon_generateur; 
     gmp_randinit_default(mon_generateur); 
     gmp_randseed_ui(mon_generateur, seed);

     int i=10;   
     while(1){

     	mpz_urandomm(rand,mon_generateur,bord_max);
     	bit_size = mpz_sizeinbase(rand, 2);
        chiffre = (unsigned int) ceil(bit_size/(log(10)/log(2)));

	if ( chiffre == k) {
         	// test to stop  
		isprime = mpz_probab_prime_p(rand, 10);
		if (isprime ==1 || isprime==2){
		printf("\n");
     		gmp_printf("le rand %Zd\n",rand);
     		printf("la seed %ld \n",seed);
     		printf("%u bits, %u chiffres \n", bit_size, (unsigned int) ceil(bit_size / (log(10) / log(2))));
     		printf("\n");
		break;
         }
	
       }
     }
     // free all 
     gmp_randclear (mon_generateur);
     mpz_clears(rand,bord_max,NULL);
     
     return 0;

}
