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
        mpz_powm (c,m,e,n);
}

void decrypt_rsa( mpz_t m, mpz_t c,mpz_t  n,mpz_t  d) 
{
    mpz_powm (m,c,d,n);
}


int main(int argc,char* argv[])
{
   
     mpz_t z_e,z_n,z_d,z_c,z_m;
   
  
     FILE *fp_cipher;
     FILE *fp_plain;
     FILE *fp_keys;
     

     if (argc != 4 ){
     	printf("Usage : %s  <-d/e> <file> <RSA keys>  \n", argv[0]);
     	exit(-1);
     }

    char mode= argv[1][0];

   // inits 
    mpz_inits(z_e,z_n,z_d,z_c,z_m,NULL);
   
    switch (mode)
    {
        case 'e' :
           
            fp_cipher = fopen(argv[2],"r");
            gmp_fscanf(fp_cipher, "%*c%*c%*c%*c%Zx", z_m);
            fp_keys = fopen(argv[3],"r");
            gmp_fscanf(fp_keys, "%*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx",z_e, z_n , z_d);
            
            encrypt_rsa( z_c, z_m,z_n,z_e); 
            gmp_printf("c = %Zx\n",z_c);
           /* gmp_printf("e= %Zx\n",z_e);
            gmp_printf("n= %Zx\n",z_n);
            gmp_printf("d= %Zx\n",z_d);*/
            fclose(fp_cipher);
            fclose(fp_keys);
        break;

        case 'd':

            fp_plain = fopen(argv[2],"r");
            gmp_fscanf(fp_plain, "%*c%*c%*c%*c%Zx", z_c);

            fp_keys = fopen(argv[3],"r");
            gmp_fscanf(fp_keys, "%*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx",z_e, z_n , z_d);
            
            decrypt_rsa(z_m, z_c,z_n,z_d);
            gmp_printf("m = %Zx\n",z_m);
            /*gmp_printf("e= %Zx\n",z_e);
            gmp_printf("n= %Zx\n",z_n);
            gmp_printf("d= %Zx\n",z_d);*/
            fclose(fp_plain);
            fclose(fp_keys);
 
        break;
    }

 
     mpz_clears(z_e,z_n,z_d,z_c,z_m,NULL);

}