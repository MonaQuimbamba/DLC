#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gmp.h"

/*
1.1 G ́en ́eration de cl ́e (mode standard)
 ́Ecrivez un programme qui prend en entr ́ee deux entiers k et e, et qui
g ́en`ere une cl ́e RSA (en mode standard) de k bits avec e comme exposant
public.
Vous devrez veillez `a ce que le module n soit le produit de deux premiers
diff ́erents p et q de tailles sensiblement  ́egales, et qu’il soit lui-mˆeme de taille
exactement k bits.
Pour permettre le stockage de la cl ́e dans un fichier par redirection de
la sortie standard, votre programme devra afficher la cl ́e en hexad ́ecimal sur
plusieurs lignes sous la forme suivante :
e = 0x......
n = 0x......
d = 0x......
Remarque 1 Pour que l’inverse de e modulo φ(n) existe, il faut que e et
φ(n) soient premiers entre eux.
 * */


int main(int argc,char* argv[])
{
     unsigned int k,e,seed;
     int isprime;
     unsigned int chiffre;
     unsigned int bit_size;
     mpz_t z_p,z_q,z_e,z_n,z_d,rand,z_gcd;
     mpz_t bord_add;
     mpz_t phi;

     if (argc != 3 ){
     	printf("Usage : %s k  e  \n", argv[0]);
     	exit(-1);
     }

     k= atoi(argv[1]);
     k=k/2;
     e= atoi(argv[2]);
   
   /********************************
    ===> 1   // generation de p et q 
   *********************************/
   
     mpz_inits(z_p,z_q,z_n,z_e,z_d,rand,z_gcd,bord_add,phi,NULL);
     mpz_set_ui(z_e,e);
     seed=time(NULL);     
   /***************************************
    generer un rand entre 0 et 2^(k-1) - 1
     et puis ajouter 2^(k)-1
   ****************************************/
   gmp_randstate_t mon_generateur; 
   gmp_randinit_default(mon_generateur); 
   gmp_randseed_ui(mon_generateur, seed);


while(1){

   int nb_primes=2;
   while (nb_primes >0)
   {
          while(1){
               mpz_urandomb(rand,mon_generateur,k-1);
               mpz_ui_pow_ui(bord_add,2,k-1);
               mpz_add(rand,rand,bord_add);
               // test primalite
               isprime = mpz_probab_prime_p(rand, 10);
               if (isprime ==1 || isprime==2)break;
          }
     if(nb_primes==2) {
          mpz_set(z_p,rand);
           nb_primes--;
     }
     if(nb_primes==1)
     {
         mpz_gcd(z_gcd,z_p,rand);
         if( mpz_cmp_ui(z_gcd,1)==0){
               mpz_set(z_q,rand);
                 nb_primes--;  // stop the first loop 
         }
     }
   }

   /***
          2 =>   Creation du modulo n et du phi de n 
   ****/
     mpz_mul(z_n,z_p,z_q);
     mpz_t tmp_p;
     mpz_t tmp_q;
     mpz_init_set(tmp_p,z_p);
     mpz_init_set(tmp_q,z_q);
     mpz_sub_ui(tmp_p,tmp_p,1);
     mpz_sub_ui(tmp_q,tmp_q,1);
     mpz_mul(phi,tmp_p,tmp_q);
     mpz_clears(tmp_p,tmp_q,NULL);

     mpz_gcd(z_gcd,z_e,phi);
     if( mpz_cmp_ui(z_gcd,1)==0) break;
}
  

     /*****
               3 => calculer le d l'inverse de e 
     ******/
     int inver;
     inver=   mpz_invert(z_d,z_e,phi);
     /// print resultats 
     /*bit_size = mpz_sizeinbase(z_q, 2);
     gmp_printf("q= %Zd  %u bits, %u chiffres \n",z_q, bit_size,(unsigned int) ceil(bit_size / (log(10) / log(2))));
     printf("\n");
     bit_size = mpz_sizeinbase(z_p, 2);
     gmp_printf("p= %Zd  %u bits, %u chiffres \n",z_p,bit_size,(unsigned int) ceil(bit_size / (log(10) / log(2))));
       printf("\n");
     bit_size = mpz_sizeinbase(z_n, 2);
     gmp_printf("n= %Zd  %u bits, %u chiffres  \n",z_n,bit_size,(unsigned int) ceil(bit_size / (log(10) / log(2))));
       printf("\n");
     bit_size = mpz_sizeinbase(phi, 2);
     gmp_printf("phi= %Zd  %u bits, %u chiffres  \n",phi,bit_size,(unsigned int) ceil(bit_size / (log(10) / log(2))));
       printf("\n");
     bit_size = mpz_sizeinbase(z_d, 2);
     gmp_printf("d= %Zd  %u bits, %u chiffres  \n",z_d,bit_size,(unsigned int) ceil(bit_size / (log(10) / log(2))));
     */
     // to save the keys on fille by redirection 
   
     gmp_printf("e = %Zx  \n",z_e);
     gmp_printf("n = %Zx  \n",z_n);
     gmp_printf("d = %Zx  \n",z_d);
   
     gmp_randclear (mon_generateur);
     mpz_clears(z_p,z_q,z_n,z_e,z_d,rand,z_gcd,bord_add,phi,NULL);
     return 0;

}
