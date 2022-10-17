#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "gmp.h"

bool miller_rabin_base(mpz_t n , mpz_t base){ // this function computes s and r in n-1 = 2^s * r

    mpz_t x,s,r,resmod,z_gcd,test;     
    mpz_inits(x,s,r,resmod,z_gcd,test,NULL);
    mpz_sub_ui(x,n,1);
    mpz_set_ui(s,0);
    mpz_set(r,x);
    mpz_mod_ui(resmod,r,2);

    while (mpz_cmp_ui(resmod,0)== 0) 
    {
        mpz_add_ui(s,s,1);             // increment the value of s
        mpz_tdiv_q_ui(r,r,2);          // half r in every iteration
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


bool  miller_rabin(mpz_t n , __uint64_t t,mpz_t base_output){

    mpz_t x,s,r,resmod,z_gcd,test,base,rand_base,n_1,n_3,j;     
    gmp_randstate_t mon_generateur; 

    bool  res=false;
    // initilize variables 
    mpz_inits(x,s,r,resmod,z_gcd,test,n_1,n_3,rand_base,j,NULL);
    mpz_sub_ui(x,n,1);
    
    mpz_sub_ui(n_1,n,1);
    
    mpz_sub_ui(n_3,n,3);

    mpz_set_ui(s,0);
    mpz_set(r,x);
    mpz_mod_ui(resmod,r,2);

    gmp_randinit_default(mon_generateur); 
    gmp_randseed_ui(mon_generateur, time(NULL));

    if(mpz_odd_p(n)!=0){

     while (mpz_cmp_ui(resmod,0)== 0) 
    {
        mpz_add_ui(s,s,1);             // increment the value of s
        mpz_tdiv_q_ui(r,r,2);          // half r in every iteration
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



bool basic_sieve(uint16_t b , uint16_t k , uint16_t t,mpz_t *my_array,mpz_t output, gmp_randstate_t mon_generateur ){



 
        mpz_t bord_add,base,q;
           bool res = false;
        mpz_inits(bord_add,base,q,NULL);
        mpz_urandomb(q,mon_generateur,b-1);
        mpz_ui_pow_ui(bord_add,2,b-1);
        mpz_add(q,q,bord_add);

 
       int j;
     
       /* for(int i = 0 ; i < k ; i ++){
                int v = mpz_divisible_p(my_array[i],q);
                if( v !=0){
                    // miller rabin 
                        /*if (miller_rabin(q,t,base)==1) 
                        {
                        res= true;
                        //gmp_printf(" q est premier = %Zu  dans la base  %Zu  \n", q , base );
                        }
                        else{
                            mpz_clears(bord_add,base,q,NULL);
                  
                         return false;
                        }*/
           //     }
       // }

        mpz_set(output,q);
        mpz_clears(bord_add,base,q,NULL);

    return res;
}



void find_r_primes(int b , int k , int t, int r,mpz_t *my_array,gmp_randstate_t mon_generateur ){

        mpz_t prime;
        mpz_init(prime);
         while( r > 0){
            if(basic_sieve(b,k,t,my_array,prime,mon_generateur)==1)
            {

                r--;
                   gmp_printf(" n %Zu est prime   ",prime);
                  int bit_size = mpz_sizeinbase(prime, 2);
                   printf("%u bits \n", bit_size);
            }
         }
        mpz_clear(prime);

}

int main(int argc,char* argv[])
{

    gmp_randstate_t mon_generateur; 
    gmp_randinit_default(mon_generateur); 
    gmp_randseed_ui(mon_generateur, time(NULL));



    if (argc != 5 ){
     	printf("Usage : %s b  k  t  r   \n", argv[0]);
     	exit(-1);
     }

    uint16_t b= atoi(argv[1]);
    uint16_t k= atoi(argv[2]);
    uint16_t t= atoi(argv[3]);
    uint16_t r= atoi(argv[4]);

    mpz_t *my_array;
    my_array = malloc(sizeof(mpz_t) * k-1);

    mpz_t rand,base;
    mpz_inits(rand,base,NULL);

    mpz_t output;
    mpz_init(output);
   
    mpz_set_ui(rand,2);
    mpz_init_set(my_array[0],rand);
   // mpz_set_ui(rand,3);
    //mpz_init_set(my_array[1],rand);
    int i=2;
    int p=4;
    int isprime;
    // the list of all primes small than k 
    for(int j=3 ; j < k-1; j++)
    {
        mpz_set_ui(rand,j);
        isprime = mpz_probab_prime_p(rand, 10);
        if (isprime ==1 || isprime==2){
           // mpz_init_set(my_array[j-2],rand);
                i++;  
        }
        //else       mpz_init_set_ui(my_array[j-2],0);
       // if(p==k) break;
        //else p+=1;
    }


    for(int i =0 ; i < k-1; i++) gmp_printf(" %Zu ",my_array[i]);
  
    //basic_sieve(b,k,t,my_array);
   // find_r_primes(b,k,t,r,my_array,mon_generateur);
            gmp_randclear(mon_generateur); 
    return 1;
     
}