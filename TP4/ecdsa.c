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


        mpz_t p_x,p_y, Y_minus,X_minus,lambda,X_r,Y_r,double_lambda,tmp;
        mpz_inits(p_x,p_y,Y_minus,X_minus,lambda,X_r,Y_r,double_lambda,tmp,NULL);
        if(sur_courbe(P,p,a,b)==1 && sur_courbe(Q,p,a,b)==1 && mpz_cmpabs(P.x,Q.x)!=0 && mpz_cmpabs(P.y,Q.y)!=0  ){

            mpz_sub(Y_minus,Q.y,P.y);
            mpz_sub(X_minus,Q.x,P.x);

            if(mpz_invert(lambda,Y_minus,X_minus)!=0){

                    mpz_pow_ui(double_lambda,lambda,2);
                    mpz_sub(X_r,double_lambda,P.x);
                    mpz_sub(X_r,X_r,Q.x);

                    mpz_sub(tmp,P.x,X_r);
                    mpz_mul(tmp,tmp,lambda);
                    mpz_sub(Y_r,tmp,P.y);

                    mpz_set(R->x,X_r);
                    mpz_set(R->y,Y_r);
                     return 0;
            }
        }
        mpz_clears(p_x,p_y,Y_minus,X_minus,lambda,X_r,Y_r,double_lambda,tmp,NULL);
        return -1;

 

   
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


     mpz_t p_x,p_y, lambda_up,lambda_down,lambda,X_r,Y_r,double_lambda,tmp,double_XP;
     mpz_inits(p_x,p_y,lambda_up,lambda_down,lambda,X_r,Y_r,double_lambda,tmp,double_XP,NULL);
    if(sur_courbe(P,p,a,b)==1){


        mpz_pow_ui(double_XP,P.x,2);
        mpz_mul_ui(lambda_up,double_XP,3);
        mpz_add(lambda,lambda_up,a);

        mpz_mul_ui(lambda_down,P.y,2);

        if(mpz_invert(lambda,lambda_up,lambda_down)!=0){

            mpz_pow_ui(double_lambda,lambda,2);
            mpz_mul_ui(X_r,P.x,2);
            mpz_sub(X_r,double_lambda,X_r);

            mpz_sub(tmp,P.x,X_r);
            mpz_mul(tmp,lambda,tmp);
            mpz_sub(Y_r,tmp,P.y);
              
        
           mpz_set(R->x,X_r);
           mpz_set(R->y,Y_r);

             mpz_clears(p_x,p_y,lambda_up,lambda_down,lambda,X_r,Y_r,double_lambda,tmp,double_XP,NULL);
            return 0;
        }
    }
    
    mpz_clears(p_x,p_y,lambda_up,lambda_down,lambda,X_r,Y_r,double_lambda,tmp,double_XP,NULL);
    return -1;

} 




/***
 *  d=|k|
 *  Q= k*P
 *   pour d-1 à 0:
 *       Q <- Q*Q // 2*Q
 *          if di==1:
 *              Q<-Q*P // Q+ P
 *   return Q
 */
void addition_scalaire(point *R, point P, mpz_t k, mpz_t p, mpz_t a, mpz_t b,mpz_t output){


    unsigned int bit_size;
    mpz_t z_Q;
    mpz_init(z_Q);

    bit_size = mpz_sizeinbase(k, 2);
    mpz_mul(z_Q,z_Q,k);
    for (int i = bit_size - 1; i >= 0; i--)
    {
        //mpz_add(z_Q,z_Q,z_Q); // 2*Q
        if(doublement(R,P,p,a,b)==0){
            if (mpz_tstbit(k, i) == 1)
            {
                //mpz_add(z_Q,z_Q,P); //  Q+ P
                 //addition(R,P,Q,p,a,b);
            }
        }
        else{
            printf(" erreur dans le doublement ");
        }
        
    }

    mpz_set(output,z_Q);
}
/**
 *   R = k · P => k · P = P + P + . . . + P
 * 
*/
int multiple(point *R, point P, mpz_t k, mpz_t p, mpz_t a, mpz_t b) {


    if(sur_courbe(P,p,a,b)==1){

        //addition_scalaire(P.x,k,R->x);
        //addition_scalaire(P.y,k,R->y);
        return 0;
    }
    return -1;
}


void testPoint(point G,mpz_t k){

    point P;
    mpz_t p,a,b;
    mpz_inits(P.x,P.y,p,a,b,NULL);
    FILE *fp;
    fp = fopen("parametres.txt","r");
    
    gmp_fscanf(fp, "%*c%*c%*c%*c%Zu\n %*c%*c%*c%*c%Zu\n %*c%*c%*c%*c%Zu\n %*c%*c%*c%*c%Zx", P.x,P.y,a,b);
    /*
    gmp_printf(" %Zu \n",P.x);
    gmp_printf(" %Zu \n",P.y);
    gmp_printf(" %Zu \n",a);
    gmp_printf(" %Zx ",b);*/

    if (mpz_odd_p(k)==0){

    }
    else{

    }

}

int main(int argc, char const *argv[])
{


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


    int addtest = addition(&R,P,Q,p,a,b);
    int doubletest = doublement(&R,P,p,a,b);

    //printf(" le point %d ",doubletest);

    testPoint(Q,a);

    return 0;
}
