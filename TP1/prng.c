#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmp.h"


int main(int argc,char* argv[])
{
     unsigned int k;
     int mode;
     mpz_t rand;
     unsigned int bit_size;
     unsigned long int seed;
     int isprime;
     unsigned int chiffre;
     mpz_t mod;
     mpz_t bord_max;
     mpz_t bord_add;


     if (argc < 2){
     	printf("Use : %s h to see the usage  \n", argv[0]);
     	exit(-1);
     }

     if(argc == 2){
          printf("Usage : %s  mode k   \n", argv[0]);
          printf(" mode <1> :  des nombres aléatoires d’au plus k bits  \n");
          printf(" mode <2> :  des nombres exactement  egale `a k bits \n");
          printf(" mode <3> :  des nombres  au plus  egale `a k chiffres decimaux \n");
          printf(" mode <4> :  des nombres exactement  egale `a k chiffres decimaux \n");
          exit(-1);
     }
      

     if(argc == 3){
           mode = atoi(argv[1]);

     k= atoi(argv[2]);

     
     
     
     printf("Entrer la seed  :");
     scanf("%ld", &seed);  
   
     gmp_randstate_t mon_generateur; 
     gmp_randinit_default(mon_generateur); 
     gmp_randseed_ui(mon_generateur, seed);
     printf("\n");

     switch (mode)
     {
          case 1 :
                    mpz_inits(rand,mod,NULL);
                    printf("Des nombres aléatoires d’au plus k bits\n");
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
                    mpz_clears(rand,mod,NULL);
          break;
          case 2 :
                        printf("Des nombres exactement  egale à k bits\n");
                         mpz_inits(rand,bord_add,NULL);
                         while(1){

                              mpz_urandomb(rand,mon_generateur,k-1);
                              mpz_ui_pow_ui(bord_add,2,k-1);
                              mpz_add(rand,rand,bord_add);
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
          break;
          case 3 :
                        printf("Des nombres  au plus  egale `a k chiffres decimaux \n");
                        mpz_inits(rand,bord_max,NULL);
                         mpz_set_ui(bord_max,k);

                         while(1){

                         mpz_urandomm(rand,mon_generateur,bord_max);
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
                         mpz_clears(rand,bord_max,NULL);
          break;
          case 4:
                         printf("Des nombres exactement  egale `a k chiffres decimaux\n");
                         mpz_inits(rand,bord_max,bord_add,NULL);
                         mpz_set_ui(bord_max,k);

                         while(1){

                              mpz_ui_pow_ui(bord_max,10,k-1);
                              mpz_urandomm(rand,mon_generateur,bord_max);
                              mpz_ui_pow_ui(bord_add,10,k-1);
                              mpz_add(rand,rand,bord_add);


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
                         mpz_clears(rand,bord_max,bord_add,NULL);
          break;
     }
 
 
     }
     else{
          printf("Use : %s h to see the usage  \n", argv[0]);
          exit(-1);
     }
    
     
     return 0;

}
