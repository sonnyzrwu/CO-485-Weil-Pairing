#include "polynomial.h"
struct RationalFunction{
    struct Polynomial *P;
    struct Polynomial *Q;
};



// Borrows Heap memory, relies on the user to input valid polynomials.
struct RationalFunction* make_rational_function(struct Polynomial *P, struct Polynomial *Q){
    struct RationalFunction * f = (struct RationalFunction *) malloc(sizeof(struct RationalFunction));
    f->P =P;
    f->Q =Q;

    return f;

}

struct RationalFunction* multiply_rf(struct RationalFunction * F, struct RationalFunction * G){

    struct Polynomial *P = multiply(F->P, G->P); // borrows from heap

    struct Polynomial *Q = multiply(F->Q, G->Q); // borrows from heap
    struct RationalFunction* R = make_rational_function(P, Q); // heap memory is not lost, stored in fields of R.
    return R;
}




void destroy_rational_function(struct RationalFunction *f){
    destroy_polynomial(f->P);
    destroy_polynomial(f->Q);
    free(f);
}
//int isEquivelant(struct RationalFunction *F, struct RationalFunction *G){
//   return 0;
// }

