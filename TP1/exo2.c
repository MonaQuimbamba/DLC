#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmp.h"

/*
 *Modifiez le programme de l’exercice pr ́ec ́edent pour que les nombres
 g ́en ́er ́es aient une taille :
 — exactement  ́egale `a k bits   : 2^(k-1) =< nombre <= 2^k -1
 — au plus  ́egale `a k chiffres d ́ecimaux
 — exactement  ́egale `a k chiffres d ́ecimaux
 *
 *


* generer un rand entre 0 et 2^(k-1) - 1
 et puis ajouter 2^(k)-1


au plus k chiffres
 * generer entre  0 e<= nombre << 10^(k)-1

 * */


int main(int argc,char* argv[])
{
     unsigned int k;
     mpz_t rand;
     mpz_t bord_add;
     unsigned long int max;
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
     mpz_inits(rand,bord_add,NULL);
    

     
     printf("Entrer la seed :");
     scanf("%ld", &seed);  
   
   
   /*
 generer un rand entre 0 et 2^(k-1) - 1
 et puis ajouter 2^(k)-1
   */

  
   gmp_randstate_t mon_generateur; 
   gmp_randinit_default(mon_generateur); 
   gmp_randseed_ui(mon_generateur, seed);

     while(1){

     	mpz_urandomb(rand,mon_generateur,k-1);
      //add ici rand + 2^k-1 
     	bit_size = mpz_sizeinbase(rand, 2);
      chiffre = (unsigned int) ceil(bit_size/(log(10)/log(2)));

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
     // free all 
     gmp_randclear (mon_generateur);
     mpz_clears(rand,bord_add,NULL);
     
     return 0;

}
