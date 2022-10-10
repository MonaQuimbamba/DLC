#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "gmp.h"


/***
  ́fonction test fermat base qui prend en entree deux en-
tiers n et a et qui teste le crit`ere de Fermat sur l’entier n pour la
base a.

***/
bool test_fermat_base(mpz_t n,mpz_t a){
        mpz_t z_gcd,z_mod,z_expo;
        mpz_inits(z_gcd,z_mod,z_expo,NULL);
        mpz_gcd(z_gcd,n,a);
        mpz_sub_ui(z_expo,n,1);
        mpz_powm (z_mod, a,z_expo, n);

        if (mpz_cmp_ui (z_gcd,1)==0 && mpz_cmp_ui(z_mod,1)==0){
              mpz_clears(z_gcd,z_mod,z_expo,NULL);
        
              return true;
        }
        return false;
}


bool test_fermat_base_v1(mpz_t n,mpz_t a){
        mpz_t z_mod,z_expo;
        mpz_inits(z_mod,z_expo,NULL);
        mpz_sub_ui(z_expo,n,1);
        mpz_powm (z_mod, a,z_expo, n);

        if (mpz_cmp_ui(z_mod,1)==0){
              mpz_clears(z_mod,z_expo,NULL);
              return true;
        }
        return false;
}

/***
 fonction test fermat qui prend en entr ́ee deux entiers n
et t et qui d ́ecide si l’entier n est compos ́e ou probablement premier
sur la base du test de Fermat tent ́e avec t bases dont les valeurs sont
choisies al ́eatoirement entre 2 et n − 2.
***/

int test_fermat(mpz_t z_n,int t, mpz_t base){

        gmp_randstate_t mon_generateur; 
        gmp_randinit_default(mon_generateur); 
        gmp_randseed_ui(mon_generateur, 2);

        mpz_t rand_base,bord_max , tmp_max;
        mpz_inits(rand_base,bord_max,tmp_max,NULL);

        mpz_sub_ui(tmp_max,z_n,1);

        mpz_set(bord_max,tmp_max);

        for( int i= 0 ; i < t ; i++ ){
             mpz_urandomm(rand_base,mon_generateur,bord_max);
            if(test_fermat_base_v1(z_n,rand_base) == false) {
                /*gmp_printf(" n %Zu est compose dans la base %Zu ", z_n,rand_base);
                 int bit_size = mpz_sizeinbase(rand_base, 2);
                 printf("%u bits \n", bit_size);
                 */
                 mpz_clears(rand_base,bord_max,tmp_max,NULL);
                return 0;
            }

            // add the goood base 
            mpz_set(base,rand_base);
        }

        
        
        mpz_clears(rand_base,bord_max,tmp_max,NULL);
        return 1;
  

}


/***
  Programme qui prend en entr ́ee une taille b, un nombre de
bases t et un nombre d’entiers test ́es r sp ́ecifi ́es par l’utilisateur. Ce
programme g ́en`erera r entiers de taille exactement b bits et appellera
pour chacun d’eux la fonction test fermat pour tester leur primalit ́e
avec t bases. Utilisez ce programme pour v ́erifier exp ́erimentalement le
th ́eor`eme sur la densit ́e des nombres premiers 1. Par exemple, obtenez
une estimation de la densit ́e de premiers parmi les entiers de taille 512
ou 1024 bits.
***/

void program_fermat(int b , int t, int r,mpz_t base){


        mpz_t rand,bord_add;
        gmp_randstate_t mon_generateur; 
        gmp_randinit_default(mon_generateur); 
        gmp_randseed_ui(mon_generateur, time(NULL));

        mpz_inits(rand,bord_add,NULL);

        for (int i =0 ; i < r ; i++){
            mpz_urandomb(rand,mon_generateur,b-1);
            mpz_ui_pow_ui(bord_add,2,b-1);
            mpz_add(rand,rand,bord_add);
            test_fermat(rand,t,base);
        }
}


/**
programme qui prend en entr ́ee une taille b, un nombre de
bases t et un nombre de premiers g ́en ́er ́es r sp ́ecifi ́es par l’utilisateur. Ce
programme g ́en ́erera des entiers de taille exactement b bits et appellera
pour chacun d’eux la fonction test fermat pour tester leur primalit ́e
avec t bases. Le programme devra s’arrˆeter lorsque r nombres auront
 ́et ́e d ́eclar ́es premiers par votre test. Pour chacun des nombres d ́eclar ́es
1. La densit ́e des nombres premiers autour de x tend asymptotiquement vers 1
ln x premiers, vous v ́erifierez qu’il l’est effectivement 2 et l’afficherez `a l’ ́ecran
si tel n’est pas le cas
**/

void find_r_primes_fermat(int b , int t, int r){


        mpz_t rand,bord_add,base;
        gmp_randstate_t mon_generateur; 
        gmp_randinit_default(mon_generateur); 
        gmp_randseed_ui(mon_generateur, time(NULL));

        mpz_inits(rand,bord_add,base,NULL);

        while( r > 0){
            mpz_urandomb(rand,mon_generateur,b-1);
            mpz_ui_pow_ui(bord_add,2,b-1);
            mpz_add(rand,rand,bord_add);
            if (test_fermat(rand,t,base)==1) {
                // reduire r and test if it's real prime 
                r--;
               if (test_fermat_base(rand,base) == 1){
                    gmp_printf(" n %Zu est prime dans la base %Zu  ",rand,base);
                    int bit_size = mpz_sizeinbase(rand, 2);
                    printf("%u bits \n", bit_size);
               }
            }
        }

      mpz_clears(rand,bord_add,base,NULL);
}




int main(int argc,char* argv[])
{
     unsigned int n,a;
     mpz_t z_n,z_a;

    /*if (argc != 3 ){
     	printf("Usage : %s n  a  \n", argv[0]);
     	exit(-1);
     }*/

    // n= atoi(argv[1]);
     //a= atoi(argv[2]);


    mpz_inits(z_n,z_a,NULL);
    //mpz_set_ui(z_n,n);
    //mpz_set_ui(z_a,a);
/*
exo 1: 
    bool test = test_fermat(z_n,z_a);
    printf("test fermat base := %d ", test);
*/

/** exo 2 :
test_fermat(z_n,a);
**/


/**exo 3 :
    program_fermat(512,15,10);
**/  

/** exo 4 :
   find_r_primes_fermat(1024,14,10);
  **/

  
    mpz_clears(z_n,z_a,NULL);








}