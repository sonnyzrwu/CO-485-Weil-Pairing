#include <stdio.h>
#include "ec.h"
#include "eea.h"
#include "rationalfunction.h"

#define INT_SIZE 32


void binExp(int m, int * arr){
    
    int i = 0;

    while(m > 0){
        arr[i] = (m%2 == 0) ? 0 : 1;
        m = m >> 1;
        ++i;
    }

}


// returns 1/1
struct RationalFunction * initialize(){
    struct Polynomial *P = make_polynomial(1, 1);
    P->data[0][0] = 1;

    return make_rational_function(P, P);
}

// returns h_PQ required for miller's algorithm
struct RationalFunction * h_PQ(struct Point *P, struct Point *Q, struct EllipticCurve E){
    struct Polynomial *line_PQ = make_polynomial(2, 2); // line passing through PQ

    int invdx ; 
    int j;
    int lambda; // slope of tangent or line through PQ.

    if ( (P->x == Q->x) && (P->y == Q->y) && (P->y != -Q->y)  ){
        
        int dy =((3 * P->x * P->x) + E.a);
        int dx = 2*P->y;

        int *inv = &invdx; // inverse of dx modulo p
        int * y = &j; // rubbish pointer

        //dx*inv + E.p*y = 1 => inv is inverse of dx modulo p
        gcd( dx , E.p , inv , y );

        lambda = dy* invdx; // slope of line passing through PQ.


    }else{

        int dy = (P->y - Q->y);
        int dx = (P->x - Q->x);

        int *inv = &invdx; // inverse of dx modulo p
        int * y = &j; // rubbish pointer

        //dx*inv + E.p*y = 1 => inv is inverse of dx modulo p
        gcd( dx , E.p , inv , y );

        lambda = dy* invdx; // slope of line passing through PQ.

    }

    line_PQ->data[0][0] = -P->y + (lambda * P->x);
    line_PQ->data[1][0] = 1;
    line_PQ->data[0][1] = - lambda;



    struct Polynomial * line = make_polynomial(1, 2);
    line->data[0][0] = P->x + Q->x - (lambda*lambda);
    line->data[0][1] = 1;
    printf("Here's h_TT! \n");

    return make_rational_function(line_PQ, line);
}


struct RationalFunction * miller(int m, struct Point *P, struct EllipticCurve E){
    struct RationalFunction * f = initialize(); // f = 1/1
    struct Point Tprime; // create a new instance of P
    Tprime.x = P->x;
    Tprime.y = P->y;
    struct Point * T = &Tprime; // T = P
    struct RationalFunction * h_TT = h_PQ(P, P, E); // 

    int arr[INT_SIZE];
    binExp(m,arr);

    for(int i = INT_SIZE - 1; i >= 0; --i){
        f = multiply_rf(f,f);
        f = multiply_rf(f, h_TT);
        struct Point temp;
        temp.x = Tprime.x;
        temp.y = Tprime.y;

        T = &temp;

        Tprime = pointWiseAddition(T, T, E); // doubt T on E

        T = &Tprime;
        // debugging
        printf("Now let's see what's going on with i: %d \n", i);

        printf("How big are matrix dimensions? %d, %d \n", f->P->rows, f->P->cols);
       //  printf("size of f->P->data: \n");
            

        //for(int i  =0; i < f->P->rows; ++i){
        //    for(int j = 0; j < f->P->cols; ++j){
        //            printf("%d ", f->P->data[i][j] );
//
//                }
//             
//                printf("\n");
  //      }
        // end of debugging


        if (arr[i] == 1){

            f = multiply_rf(f, h_PQ(T, P, E));




            struct Point temp;
            temp.x = Tprime.x;
            temp.y = Tprime.y;
            T = &temp;
            Tprime = pointWiseAddition(T, P, E);
            printf("Does pointwise addition even work? (%d, %d) \n", Tprime.x, Tprime.y);
            
            T = &Tprime;
        }
    }


    return f;
}