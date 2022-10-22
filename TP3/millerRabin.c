#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "gmp.h"


/**
 * 
 *  let 'n' be  an odd composite integer n-1 = 2^s*r with r odd 
 * 
 *  and a base 'a'  1 <= a <= n-1
 * 
 *  the Miller-Rabin criterion  is verified if :
 *          => a^r =1 mod n 
 * 
 *          or if exist 0 <= j <= s-1  such that a^2jr = -1 mod n 
 * 
 *  
 * **/

bool miller_rabin_base(mpz_t n , mpz_t base){

    mpz_t x,s,r,resmod,z_gcd,test;     
    mpz_inits(x,s,r,resmod,z_gcd,test,NULL);
    mpz_sub_ui(x,n,1);
    mpz_set_ui(s,0);
    mpz_set(r,x);
    mpz_mod_ui(resmod,r,2);

    while (mpz_cmp_ui(resmod,0)== 0) 
    {
        mpz_add_ui(s,s,1);            
        mpz_tdiv_q_ui(r,r,2);         
        mpz_mod_ui(resmod,r,2);

    }

     mpz_gcd(z_gcd,n,base);
     if(mpz_cmp_ui(z_gcd,1)==0){

            mpz_powm(test,base,r,n);
            if(mpz_cmp_ui(test,1)==0){  // criterion 1 
                return true;
            }
            //criterion 2
            mpz_sub_ui(s,s,1);
             uint64_t taille = mpz_get_ui(s);
             mpz_t expo;
             mpz_init_set_ui(expo,1);
            for(int j=0 ; j < taille; j++){
                mpz_mul_ui(expo,expo,2*j);
                mpz_mul(expo,expo,r);
                mpz_powm(test,base,expo,n);

                if(mpz_cmp_ui(test,1)==0){
                    return true;
                }
            } 

     }
    mpz_clears(x,s,r,resmod,z_gcd,test,NULL);
    return false;

} 


bool  miller_rabin(mpz_t n , __uint64_t t,mpz_t base_output,gmp_randstate_t mon_generateur){

    mpz_t x,s,r,resmod,z_gcd,test,base,rand_base,n_1,n_3,j;     


    bool  res=false;

    mpz_inits(x,s,r,resmod,z_gcd,test,n_1,n_3,rand_base,j,NULL);
    mpz_sub_ui(x,n,1);
    
    mpz_sub_ui(n_1,n,1);
    
    mpz_sub_ui(n_3,n,3);

    mpz_set_ui(s,0);
    mpz_set(r,x);
    mpz_mod_ui(resmod,r,2);



    if(mpz_odd_p(n)!=0){

     while (mpz_cmp_ui(resmod,0)== 0) 
    {
        mpz_add_ui(s,s,1);            
        mpz_tdiv_q_ui(r,r,2);         
        mpz_mod_ui(resmod,r,2);
    }

    for(int i=0 ; i< t; i++){
        mpz_urandomm(rand_base, mon_generateur, n_3);    
        mpz_add_ui(rand_base, rand_base, 2);  
        mpz_powm(test,rand_base,r,n);
      
      if(mpz_cmp_ui(test,1)== 0 ) continue;
            mpz_set_ui(j,0);
      while( mpz_cmp(j,s) < 0){
        if(mpz_cmp(test,n_1)==0) break;
         mpz_powm_ui(test, test, 2, n);
         mpz_add_ui(j,j,1);
      }
        if(mpz_cmp(test,n_1)== 0) continue;
     }

       mpz_set(base_output,rand_base);
       res=true;
    }
    
   mpz_clears(x,s,r,resmod,z_gcd,test,n_1,n_3,rand_base,j,NULL);
  return res;
}


void find_r_primes_miller_rabin(__uint64_t b , __uint64_t t, __uint64_t r,gmp_randstate_t mon_generateur){


        mpz_t rand,bord_add,base;
        int isprime;


  

        mpz_inits(rand,bord_add,base,NULL);

        while( r > 0){
            mpz_urandomb(rand,mon_generateur,b-1);
            mpz_ui_pow_ui(bord_add,2,b-1);
            mpz_add(rand,rand,bord_add);
            if (miller_rabin(rand,t,base,mon_generateur)==1) {
               
               /*if (miller_rabin_base(rand,base) == 1){
                   // reduire r and test if it's real prime 
                    r--;
                    gmp_printf(" n %Zu est prime dans la base %Zu  ",rand,base);
                    int bit_size = mpz_sizeinbase(rand, 2);
                    printf("%u bits \n", bit_size);
               }*/

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
        
    find_r_primes_miller_rabin(b,t,r,mon_generateur);
  

          gmp_randclear(mon_generateur); 
 
     
}
