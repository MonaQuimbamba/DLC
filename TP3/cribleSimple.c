#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include  <sys/types.h> 
#include  <sys/resource.h>
#include "gmp.h"


unsigned long int cputime()
{
struct rusage rus;
getrusage (0, &rus);
return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}

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
        for(int i = 1 ; i < k ; i ++){
            if(mpz_cmp_ui(my_array[i],0)!=0){
                 int v = mpz_divisible_p(q,my_array[i]);
                if( v !=0){
                       // miller rabin 
                        if (miller_rabin(q,t,base)==1) 
                        {
                           res= true;
                           //gmp_printf(" q est premier = %Zu  dans la base  %Zu  \n", q , base );
                        }
                        else{
                            mpz_clears(bord_add,base,q,NULL);
                  
                         return false;
                        }
               }

            }
            
        }

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
                   gmp_printf("%Zu  %ld\n",prime,cputime());
                  int bit_size = mpz_sizeinbase(prime, 2);
                   //printf("%u bits \n", bit_size);
            }
         }
        mpz_clear(prime);

}


void cribleOpt(mpz_t* primes,uint64_t k){
    int  i, j;  
    int limit = sqrt(k);  
  
    for(i = 0; i < k; i++)  mpz_init_set_ui(primes[i],i+1);

    for(i = 1; i <= limit; i++)  
    {  
        if(mpz_cmp_ui(primes[i],0) != 0)  
        {  
            for(j = pow(num[i], 2); j <= N; j = j + num[i])  
            {  
                num[j - 1] = 0;  
            }  
        }  
  
    }  

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

    mpz_t *primes;
    primes = malloc(sizeof(mpz_t) * k-1);

    mpz_t rand,base,output,testBoucle,mult,j,minus;
    mpz_inits(rand,base,output,testBoucle,mult,j,minus,NULL);

  
   


   
    int  i;  
    for(i = 0; i < k; i++)  mpz_init_set_ui(primes[i],i+1);

    mpz_mul(mult,primes[1],primes[1]);
    mpz_set(testBoucle,mult);
    i=1;
    while( mpz_cmp_ui(testBoucle,k)<0)  
    {  
        if(mpz_cmp_ui(primes[i],0) != 0)  
        {  
            mpz_mul(mult,primes[i],primes[i]);
            mpz_set(testBoucle,mult);
            mpz_set(j,mult);
            while(mpz_cmp_ui(j,k) <0) 
            {  
                
                mpz_sub_ui(minus,j,1);
                int index=mpz_get_ui(minus);
      
                mpz_set_ui(primes[index],0);
                mpz_add(j,j,primes[i]);
            }  
        }  
        ++i;
        mpz_mul(mult,primes[i],primes[i]);
        mpz_set(testBoucle,mult);
    }  
  
    


    //for(int i =1 ; i < k; i++) gmp_printf(" %Zu ",primes[i]);
  
    //basic_sieve(b,k,t,primes,output,mon_generateur);
     find_r_primes(b,k,t,r,primes,mon_generateur);
    gmp_randclear(mon_generateur); 

    //printf(" time %ld",cputime());
    return 0;
     
}


//https://technotip.com/9436/prime-numbers-using-sieve-of-eratosthenes-c-program/