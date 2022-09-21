#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "gmp.h"


/*
 *
 Le fichier private key.txt contient les valeurs du module "n" et de l’exposant
      prive "d" d’une ce RSA de 1024 bits.

  Ecrivez un programme qui utilise cette cle pour dechiffrer le chiffre "c"

  contenu dans le fichier "ciphertext.txt" par la methode du "square and multiply" de gauche `a droite.
  Votre programme devra comparer la valeur obtenue avec la valeur du clair  "m" se trouvant
  dans le fichier "plaintext.txt"


  Variante de votre programme : utilisez la methode d’exponentiation “square
  and multiply” de droite `a gauche.
 *
 *
 **
 */

int main(int argc, char* argv[]){

        mpz_t z_n;
        mpz_t z_d;
        mpz_t z_m;
        mpz_t z_c;
        unsigned int  bit_size;
        mpz_t z_result;
        mpz_t z_r;
        int mode;

        mpz_inits(z_n,z_d,z_m,z_c,z_result,z_r,NULL);
        FILE *fp_cipher;
        FILE *fp_plain;
        FILE *fp_keys;
     
        fp_cipher = fopen("Ressources/ciphertext.txt","r");
        gmp_fscanf(fp_cipher, "%*c%*c%*c%*c%Zx", z_c);
     



        fp_plain = fopen("Ressources/plaintext.txt","r");
        gmp_fscanf(fp_plain, "%*c%*c%*c%*c%Zx", z_m);



        fp_keys = fopen("Ressources/private_key.txt","r");
        gmp_fscanf(fp_keys, "%*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx", z_n , z_d);



   if (argc < 2){
      printf("Use : %s h to see the usage  \n", argv[0]);
      exit(-1);
     }
    

    if(argc == 2){

       if( strcmp(argv[1],"h") ==0 )
       {
          printf("Usage : %s  mode   \n", argv[0]);
          printf(" mode <1> :  Exponentiation binaire Gauche-Droite ou L2R \n");
          printf(" mode <2> :  Exponentiation binaire Droite-Gauche ou R2L  \n");
          exit(-1);
      }
      else if (atoi(argv[1])==1 || atoi(argv[1])==2  ){

            mode = atoi(argv[1]);
            bit_size =  mpz_sizeinbase(z_d, 2);

              mpz_set_ui(z_result, 1);
              mpz_set(z_r, z_c);


              switch (mode)
               {
                    case 1 :
                          printf("Exponentiation binaire Gauche-Droite ou L2R \n");
                          for (int i = bit_size - 1; i >= 0; i--)
                          {
                              // result <-- result^2 mod modulus
                              mpz_mul(z_result, z_result, z_result);
                              mpz_mod(z_result, z_result, z_n);

                              if (mpz_tstbit(z_d, i) == 1)
                              {
                              // result <-- result * base mod modulus
                              mpz_mul(z_result, z_result, z_c);
                              mpz_mod(z_result, z_result, z_n);
                              }
                          }
                    break;

                    case 2:
                        printf(" Exponentiation binaire Droite-Gauche ou R2L \n");
                        for(int i=0 ; i <= bit_size-1 ;i++){
                          if (mpz_tstbit(z_d, i) == 1){
                            mpz_mul(z_result, z_result, z_r);
                            mpz_mod(z_result, z_result, z_n);
                          }
                           mpz_mul(z_r, z_r, z_r);
                           mpz_mod(z_r, z_r, z_n);
                        }
                    break;


                  }
           


               if ( mpz_cmp(z_result,z_m)==0)
              {
                        printf("\n");
                       printf(" Good guess ");
                       printf("\n");
               }


            mpz_clears(z_n,z_d,z_m,z_c,z_result,z_r,NULL);



      }
      else{
           printf("Use : %s h to see the usage  \n", argv[0]);
      exit(-1);
      }

    }
    


 
return 0;


}
