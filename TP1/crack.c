#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmp.h"


int main(int argc, char* argv[]){

	mpz_t z_base;
	mpz_t z_expo;
	mpz_t z_modulos;
  unsigned int  bit_size;
  mpz_t z_result;

	mpz_inits(z_base,z_expo,z_modulos,z_result,NULL);

  mpz_set_str(z_modulos,"3772760074234358419401418332774330681526422291347814443966653942575436264390940109637171997959891142677965081442147389915250388713280260108666644971365285446855717984799528736772256567476702653891103463417969383092883751027351762242511516581453586502762929086170906935214091108667927168338152656262689914307",0);
	mpz_ui_pow_ui( z_expo, 2, 13004887);
  // dechiffrer
  //mpz_powm (rop,z_c,z_d,z_n);


    mpz_set_ui(z_result, 1);
		mpz_set_ui(z_base,2);
    mpz_powm(z_result,z_base,z_expo,z_modulos);
   gmp_printf("%Zd\n", z_result);
	mpz_clears(z_base,z_expo,z_modulos,z_result,NULL);




}
