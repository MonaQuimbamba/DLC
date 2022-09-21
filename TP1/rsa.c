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
            mpz_inits(z_n,z_d,z_m,z_c,z_result,z_r,NULL);
            mpz_set_str(z_n,"0xae828886a1990cde8d02955ba7ca8ee6f572d6030f947aa26d4643e5f00e824bbc7b962904f04ab5bb4682f661c2b8b86bd2c0c04b4de86aac8b9f5086e253e5d1297ece80a4d5b5b3d5f82d8ba878dc031e1a19b6af1aa3ac29c5a8df46cb3743f866311e1df3be3d62d6395633c900c7ac5138d34c825b8f37fbf70842879d",0);
            mpz_set_str(z_d,"0x4c2500d55de59e4bed5357406af263703b612428a9bfabd2fbc351151fadf5047ef59e0bbfefe9696a91d5cb13d5172cc13f708377584335689c73a37b777e0b6c524c4a9ab7e4b78e67ee9ffd3acdb1d6dfda7c42db40eebb0901a74cf2508e5316d9227b1c09dd798f52fd335185e0958fb36271c13260a2650e3b074a5e31",0);
            mpz_set_str(z_m,"0x4548a949e5207233e8b1fc88e896d9da2bbf5d8948338db6dd332c0ebf01ad1d34d61d6f148ea87e8e1d7f3d97645739db6489ef22272312f155255939d92e25a9da580a16109ecc4c69d0442f68394dc9a37fe8186c574859a3048970299e12db743025802c46b8a583b8f5b9c9dd5db95c8b583cf039c34e89f206abc82775",0);
            mpz_set_str(z_c,"0x96794d4b033ad45cd2b27e199aa27de76801ab04dff67cd1afd79ebd349744ff2a0b0afa2b4fb8f556a8e52d5d0c53536481bc4daf8453c9adcd473e8d9f1a74afdc6901dbce1c7b123d41e6eaf23125ccfe07da3aa69ef25794ad8779f21d605af85571f8e0dcd7b9c43d0b9033fd2c8aa01b7846010ca6985f7491db2ee9db",0);
            // dechiffrer
            
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
