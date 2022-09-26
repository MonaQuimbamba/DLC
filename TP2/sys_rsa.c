#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gmp.h"

/*
crivez une fonction de chiffrement encrypt rsa(c, m, n, e) qui prend en
entr ́ee les deux  ́el ́ements n et e d’une cl ́e publique RSA ainsi qu’un message
m ∈ Zn, et qui calcule la valeur du chiffr ́e de m, soit c = me mod n.
 
 Ecrivez une fonction de d ́echiffrement decrypt rsa(m, c, n, d) qui prend
en entr ́ee le module public n, l’exposant priv ́e d ainsi qu’un chiffr ́e c ∈ Zn,
et qui calcule la valeur du d ́echiffr ́e de c, soit m = cd mod n.
 ́Ecrivez un programme qui prend en entr ́ee le nom d’un fichier `a chiffrer et
le nom d’un fichier de cl ́e RSA, et qui chiffre le contenu du fichier plutˆot qu’un
entier n’ayant pas de signification  ́evidente. Pour r ́ealiser ce chiffrement, le
contenu du fichier devra ˆetre trait ́e par blocs d’octets, et chacun de ces blocs
sera encod ́e en un entier mi ∈ Zn en consid ́erant sa s ́equence d’octets comme
la repr ́esentation de mi en base 256.
 ́Ecrivez le programme qui r ́ealise l’op ́eration inverse, c’est `a dire qui
d ́echiffre un fichier chiffr ́e.
 
 
 * */


void encrypt_rsa( mpz_t c, mpz_t m,mpz_t  n,mpz_t  e) 
{
        mpz_powm (mpz_t c, mpz_t m, mpz_t e, mpz_t n);
}

void decrypt_rsa( mpz_t m, mpz_t c,mpz_t  n,mpz_t  d) 
{
    mpz_powm (mpz_t m, mpz_t c, mpz_t d, mpz_t n);
}


int main(int argc,char* argv[])
{
   
     mpz_t z_e,z_n,z_d,z_c,z_m;
     mpz_inits(z_e,z_n,z_d,z_c,z_m;NULL);
  


     if (argc != 4 ){
     	printf("Usage : %s <file> <RSA keys> <d/e>  \n", argv[0]);
     	exit(-1);
     }

 
     mpz_clears(z_e,z_n,z_d,z_c,z_m,NULL);

}