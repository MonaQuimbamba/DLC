#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "gmp.h"

// y^2 ≡ x^3 − 3x + b (mod p)
typedef struct {
mpz_t x;
mpz_t y;
} point; 

/**
 * qui renvoie 1 si le point P appartient à la courbe elliptique definie par
les param`etres p, a et b, et 0 sinon.
*/
int sur_courbe(point P , mpz_t p,mpz_t a , mpz_t b){

        mpz_t x ,y,tmp; 
        mpz_inits(x,y,tmp,NULL);
        int res;
        mpz_set(x,P.x);
        mpz_set(y,P.y);

        mpz_pow_ui(x,x,3);
        mpz_mod(x,x,p);
       
        mpz_mul(tmp,a,P.x);
        mpz_mod(tmp,tmp,p);

        mpz_sub(tmp,x,tmp);
        mpz_mod(tmp,tmp,p);

        mpz_add(tmp,tmp,b);
        mpz_mod(tmp,tmp,p);

       
        mpz_pow_ui(y,y,2);
        mpz_mod(y,y,p);

        res = (mpz_cmp(y,tmp)==0) ? 1 : 0; 
      

        return res;


}
/**
*qui calcule le point R = P + Q. Votre fonction devra v ́erifier que les
points P et Q appartiennent `a la courbe et v ́erifient les conditions pour
pouvoir ˆetre additionn ́es. Elle renverra 0 si l’addition est possible et -1
sinon
*

λ = yQ −yP/xQ −xP
xR = λ2 − xP − xQ
yR = λ(xP − xR ) − y
*/
int addition(point *R, point P, point Q,mpz_t p, mpz_t a, mpz_t b){


        mpz_t p_x,p_y;
        mpz_inits(p_x,p_y,NULL);
        if(sur_courbe(P,p,a,b)==1 && sur_courbe(Q,p,a,b)==1 && mpz_cmpabs(P.x,Q.x)!=0 && mpz_cmpabs(P.y,Q.y)!=0  ){

            mpz_add(p_x,P.x,Q.x);
            mpz_add(p_y,P.y,Q.y);

            mpz_set(R->x,p_x);
            mpz_set(R->y,p_y);

            mpz_clears(p_x,p_y,NULL);
            return 1;

        }


        mpz_clears(p_x,p_y,NULL);
        return 0;
    

   
}



/**
 * qui calcule le point R = 2 · P . Votre fonction devra verifier que le point
P appartient `a la courbe. Elle renverra 0 si le doublement est possible
et -1 sinon


λ = 3x2/P +a
2yP (a is the curve equation parameter)
xR = λ2 − 2xP
yR = λ(xP − xR ) − y


*/
int doublement(point *R, point P,mpz_t p, mpz_t a, mpz_t b){

    if(sur_courbe(P,p,a,b)==1){

        mpz_mul_ui(R->x,P.x,2);
        mpz_mul_ui(R->y,P.x,2);

    }

    return 0;

} 
int main(int argc, char const *argv[])
{
    /* code */


    mpz_t p ,b,a;
    point P;
    point Q;
    point R;
    mpz_inits(p,a,b,P.x,P.y,Q.x,Q.y,R.x,R.y,NULL);

    mpz_set_str(P.x,"2294926173752935920088658480112003677671316813610181433467",0);
    mpz_set_str(P.y,"3657116447508532624388540380545096283657766220846374116742",0);

    mpz_set_str(Q.x,"5369744403678710563432458361254544170966096384586764429448",0);
    mpz_set_str(Q.y,"5429234379789071039750654906915254128254326554272718558123",0);

    mpz_set_str(p,"6277101735386680763835789423207666416083908700390324961279",0);
    mpz_set_str(b,"64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1",16);
    mpz_set_ui(a,3);


    int sur_c = addition(&R,P,Q,p,a,b);

    printf(" le point %d ",sur_c);

    return 0;
}
