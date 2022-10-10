#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
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
 
 

 fin 2^127
 max 127 octets
 * */


#define BLOCK  127


void encrypt_rsa( mpz_t c, mpz_t m,mpz_t  n,mpz_t  e) 
{
        mpz_powm (c,m,e,n);
}

void decrypt_rsa( mpz_t m, mpz_t c,mpz_t  n,mpz_t  d) 
{
    mpz_powm (m,c,d,n);
}

char hexToInt(char c){ 
 if(c<58) return c-48;   
 return 9+(c-96); 
 
}

void writte_the_cypher(mpz_t c)
{
    FILE *out;
    //printf(" taille %d \n", (int)mpz_size);
   // char res[(int)mpz_size];
   /*char str[128];
   mpz_t tab[128];
   mpz_t r,q,base;
   mpz_inits(r,q,base,NULL);
    printf(" [ ");
   for(int i =0 ; i< 128 ; i++){

        mpz_ui_pow_ui(base,256,i);
        mpz_cdiv_qr(q,r,c,base);
        if(mpz_cmp_ui(q,0)!=0){
             mpz_set(c,r);
             //tab[i]=q;
             gmp_printf("q= %Zx ",q);
             gmp_printf("r= %Zx ",r); 
             gmp_printf("base= %Zx ",base); 
        }

   }
    printf(" ]\n"); */

    //gmp_sprintf(res, "%Zd", c);
   out = fopen( "output.txt" , "a" );
   //fwrite(res , 1 , sizeof(res), out );
   mpz_out_str(out, 10, c);
   fwrite("\n" , 1 , sizeof(char), out );
   fclose(out);
 
   //mpz_clears(r,q,base,NULL);

}


int main(int argc,char* argv[])
{
   
     mpz_t z_e,z_n,z_d,z_c,z_m,base,z_q;

     char buffer_plain[BLOCK+1];
     int num;

     FILE *fp_cipher;
     FILE *fp_plain;
     FILE *fp_keys;
     

   /*  if (argc != 4 ){
     	printf("Usage : %s  <-d/e> <file> <RSA keys>  \n", argv[0]);
     	exit(-1);
     }*/

    char mode= argv[1][0];

   // inits 
    mpz_inits(z_e,z_n,z_d,z_c,z_m,z_q,base,NULL);


    //mpz_set_str(z_n, "1848917392784198379327149238139743214", 0);
    //char  res[37] ;// = mpz_get_str(NULL,10,z_n);
    //gmp_printf(" %Zd ",z_n);
    
    
    switch (mode)
    {
        case 'e' :
           
            fp_keys = fopen(argv[3],"r"); // retrieve the RSA keys 
            gmp_fscanf(fp_keys, "%*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx",z_e, z_n , z_d);
            // retrieve the file to encrypt 
            fp_plain = fopen(argv[2], "r"); 
            fseek(fp_plain, 0L, SEEK_END);
            long int taille_file = ftell(fp_plain);
            rewind(fp_plain);
           fp_plain = fopen(argv[2], "r");
            while(1)
            {
                memset(buffer_plain, 0, sizeof(buffer_plain));
                num = fread( buffer_plain, sizeof( char ), BLOCK, fp_plain);
                if ( num ) {  
                    mpz_set_ui(z_m,0);
                    for(int i=0 ; i <BLOCK; i++){
                        mpz_ui_pow_ui(base,256,i);
                        mpz_mul_ui(base,base,(int)buffer_plain[i]);
                        mpz_add(z_m,z_m,base);
                    }
                      encrypt_rsa(z_c, z_m,z_n,z_e); 
                      writte_the_cypher(z_c);
                      gmp_printf("[ %Zu ]\n ",z_c); //write that into file 
                    
                    }
                taille_file -= BLOCK;
                if(taille_file==0) break;
                else if (taille_file<0) taille_file= BLOCK - taille_file + taille_file;

              }
        
              fclose( fp_plain );
              fclose(fp_keys);
            //gmp_printf("c = %Zx\n",z_c);
           // gmp_printf("e= %Zx\n",z_e);
            //gmp_printf("n= %Zx\n",z_n);
            //gmp_printf("d= %Zx\n",z_d);

        break;

        case 'd':

             // retrieve the RSA keys 
            fp_keys = fopen(argv[3],"r");
            gmp_fscanf(fp_keys, "%*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx %*c%*c%*c%*c%Zx",z_e, z_n , z_d);
            
            // retrieve the file to decrypt 
            fp_cipher = fopen(argv[2],"r");
            if(!fp_cipher){
            printf("\n Unable to open : %s ", argv[2]);
            return -1;
            }
            
            char line[128];
            while (fgets(line, sizeof(line), fp_cipher)) 
            {
                //memset(line, 0, sizeof(line));
                 mpz_set_ui(z_c,0);
                 for(int i=0 ; i <128; i++){

                        mpz_set_ui(z_q,(int)line[i]);
                        mpz_ui_pow_ui(base,256,i);
                        mpz_divexact(z_q, z_q,base );
                       //mpz_div_ui(base,base,(int)line[i]);
                        //mpz_cdiv_qr_ui(mpz_t q, mpz_t r, mpz_t n, (int) line[i]);
                        mpz_add(z_c,z_c,z_q);
                       // printf("=> %d \n",(int)line[i]);
                    }
              
                  //printf("%s  => %d \n", line,i); 
                  //gmp_printf(" %Zd => %d\n", z_c,i);
                  decrypt_rsa(z_m, z_c,z_n,z_d);
                  gmp_printf("m = %Zx\n",z_m);
   
            
            }
  

            //decrypt_rsa(z_m, z_c,z_n,z_d);
            //gmp_printf("m = %Zx\n",z_m);
            //gmp_printf("e= %Zx\n",z_e);
            //gmp_printf("n= %Zx\n",z_n);
            //gmp_printf("d= %Zx\n",z_d);
            fclose(fp_cipher);
            fclose(fp_keys);
 
        break;
    }

 
     mpz_clears(z_e,z_n,z_d,z_c,z_m,base,z_q,NULL);

}

//2^1023 to 2^1024 - 1