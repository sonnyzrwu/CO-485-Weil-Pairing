#include "ec.h"
#include "stdio.h"

struct Point pointWiseAddition(struct Point P, struct Point Q, struct EllipticCurve E){
    struct Point result = {0, 0, 0};
    int modulus = (int) E.p;
    if ( P.isInf == 1 ){
        result = Q;
    } else if (Q.isInf == 1){
        result = P;
    } else if ((P.x== Q.x) && (P.y - modulus == -Q.y)){
        result.x = 0;
        result.y = 0;
        result.isInf = 1;

    } else if (((P.x != Q.x) || (P.y != Q.y) ) && ((P.x != Q.x) || (P.y != -Q.y) )){
            
            int inva;
            int b;
            int *x = &inva;
            int *y = &b;

            int a = (Q.x - P.x);
            while(a < 0){a = a + modulus;}
            gcd(a, modulus, x, y);
            // printf("%d \n", (inva * a)%modulus);
            
            while(inva < 0){inva = inva + modulus;}
            int i = (int) ( (inva%modulus) * ((Q.x - P.x)%modulus) )%modulus;
            
            while(i < 0){i = i+modulus;}
            
            // printf("i, a, inva: %d, %d, %d\n", i, (Q.x-P.x)%modulus, inva);
            int lambda = (Q.y - P.y)*inva;
            
            result.x = (lambda*lambda%modulus - P.x - Q.x)%modulus;
            result.y = (-P.y + (lambda*(P.x - result.x)))%modulus;

            while(result.y < 0){result.y = result.y + modulus;}
            while(result.x < 0){result.x = result.x + modulus; }
            
            
        } else if ( (P.x == Q.x) && (P.y == Q.y) && (P.y != -Q.y)  ){
        int inva;
        int b;

        int *x = &inva;
        int *y = &b;

        int a = (2*(P.y));
        while(a < 0){a = a + modulus;}
        gcd(a, modulus, x, y);
        while(inva < 0){inva = inva + modulus;}

        int i = (int) ( (inva%modulus) * (2* (P.y)%modulus) )%modulus;
        while(i < 0){i = i+modulus;}
        //printf("modulus: %d \n", modulus);
        /*
        printf("i: %d \n", i);
        printf("inva: %d\n", inva);
        */
        int lambda = (((3*(P.x)*(P.x) + E.a)%modulus) *inva)%modulus;
        result.x = (lambda*lambda)%modulus- 2*P.x%modulus ;
        result.y = (-P.y + (lambda*(P.x - result.x)))%modulus;

        while(result.y < 0){result.y = result.y + modulus;}
        while(result.x < 0){result.x = result.x + modulus; }
        
        //printf("Y^2 = %d \n" , result.y*result.y%modulus);
        //printf("X^3 + aX^2 + b = %d \n" , ((result.x * (result.x*result.x)%modulus)%modulus + (result.x)%modulus + E.b)%modulus);
        
        }
        
    return result;
}