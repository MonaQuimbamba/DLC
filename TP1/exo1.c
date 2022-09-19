#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmp.h"

/*
 Ecrivez un programme qui lit un entier k sur la ligne de commande,
puis g ́en`ere et affiche des nombres al ́eatoires d’au plus k bits. Le programme
s’arrˆetera lorsque le nombre al ́eatoire g ́en ́er ́e sera multiple de 20 (variante :
lorsque le nombre g ́en ́er ́e sera premier).
Am ́eliorer votre programme pour que les nombres g ́en ́er ́es soient diff ́erents
`a chaque ex ́ecution.
Am ́eliorer votre programme pour qu’il affiche la graine utilis ́ee.
Am ́eliorer votre programme pour qu’il puisse prendre en entr ́ee une valeur
de graine `a laquelle initialiser le g ́en ́erateur (tr`es utile pour faire du rejeu).
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
     mpz_t mod;


     if (argc != 2){
     	printf("Usage : %s k   \n", argv[0]);
     	exit(-1);
     }


     k= atoi(argv[1]);
     mpz_inits(rand,bord_max,mod,NULL);
     mpz_set_str(bord_max, "8497391829048797593184398274916519319103580", 0);
     
     printf("Entrer la seed :");
     scanf("%ld", &seed);  
   
   
  

     gmp_randstate_t mon_generateur; 
     gmp_randinit_default(mon_generateur); 
     gmp_randseed_ui(mon_generateur, seed);

     int i=10;   
     while(1){

     	mpz_urandomb(rand,mon_generateur,k);
     	bit_size = mpz_sizeinbase(rand, 2);
      chiffre = (unsigned int) ceil(bit_size/(log(10)/log(2)));
      mpz_mod_ui(mod,rand,20);
	   if ( mpz_cmp_ui(mod,0) ==0 ) {
         	// test to stop  
		
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
     mpz_clears(rand,bord_max,mod,NULL);
     
     return 0;

}
