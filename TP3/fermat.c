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
bool fermat_base(mpz_t n,mpz_t a){
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


bool fermat_base_v1(mpz_t n,mpz_t a){
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
// base parameter is for output 
int fermat(mpz_t z_n,__uint64_t t, mpz_t base){

        gmp_randstate_t mon_generateur; 
        gmp_randinit_default(mon_generateur); 
        gmp_randseed_ui(mon_generateur, time(NULL));

        mpz_t rand_base,bord_max , tmp_max;
        mpz_inits(rand_base,bord_max,tmp_max,NULL);

        mpz_sub_ui(bord_max,z_n,3);

        for( int i= 0 ; i < t ; i++ ){
                mpz_urandomm(rand_base,mon_generateur,bord_max);
                mpz_add_ui(rand_base,rand_base, 2);     
            if(fermat_base_v1(z_n,rand_base) == false) {
                 mpz_clears(rand_base,bord_max,NULL);
                return 0;
            }
            // add the good base to output
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

void program_fermat(__uint64_t b , __uint64_t t, __uint64_t r,mpz_t base,gmp_randstate_t mon_generateur){


        mpz_t rand,bord_add;
        mpz_inits(rand,bord_add,NULL);

        for (int i =0 ; i < r ; i++){
            mpz_urandomb(rand,mon_generateur,b-1);
            mpz_ui_pow_ui(bord_add,2,b-1);
            mpz_add(rand,rand,bord_add);
            if(fermat(rand,t,base)==1 )  gmp_printf(" n %Zu est prime dans la base %Zu  ",rand,base);
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

void find_r_primes_fermat(__uint64_t b , __uint64_t t, __uint64_t r,gmp_randstate_t mon_generateur){


        mpz_t rand,bord_add,base;
        int isprime;
        mpz_inits(rand,bord_add,base,NULL);

        while( r > 0){
            mpz_urandomb(rand,mon_generateur,b-1);
            mpz_ui_pow_ui(bord_add,2,b-1);
            mpz_add(rand,rand,bord_add);
            if (fermat(rand,t,base)==1) {
                isprime = mpz_probab_prime_p(rand, 10);
                if (isprime ==1 || isprime==2){
                    r--;
                    gmp_printf(" n %Zu est prime dans la base %Zu  ",rand,base);
                    int bit_size = mpz_sizeinbase(rand, 2);
                    printf("%u bits \n", bit_size);

                }
            }
        }

      mpz_clears(rand,bord_add,base,NULL);
}




void main(int argc,char* argv[])
{


        gmp_randstate_t mon_generateur; 
        gmp_randinit_default(mon_generateur); 
        gmp_randseed_ui(mon_generateur, time(NULL));
     __uint64_t b,t,r;
  
    if (argc != 4 ){
     	printf("Usage : %s b  t  r   \n", argv[0]);
     	exit(-1);
     }

     b= atoi(argv[1]);
     t= atoi(argv[2]);
     r= atoi(argv[3]);


    find_r_primes_fermat(b,t,r,mon_generateur);
    gmp_randclear(mon_generateur); 



}