#include "polynomial.h"

struct RationalFunction{
    struct Polynomial * f;
    struct Polynomial * g;
};



struct RationalFunction * makeRationalFunction(struct RationalFunction *F, int rowf, int colf, int rowg, int colg){

    assert(rowg > 0 && colg > 0);

    F =  malloc( sizeof(struct RationalFunction) );
    F->f = NULL;
    F->g = NULL;

    F->f = makePolynomial(F->f, rowf, colf);
    F->g = makePolynomial(F->g, rowg, colg);

    F->g->data[0][0] = 1; // we can't have division by zero

    return F;
}

void destroyRationalFunction(struct RationalFunction * F){
    destroyPolynomial(F->f);
    destroyPolynomial(F->g);
    F->f = NULL;
    F->g = NULL;
    free(F);
}




struct RationalFunction * multiplyRF(struct RationalFunction * F, struct RationalFunction *G, struct EllipticCurve E){

    struct Polynomial * mod = NULL;
    mod = makePolynomial(mod, 3, 4);
	
	mod->data[0][0] = E.b; // b
	
	mod->data[2][0] = -1;
	mod->data[0][3] = 1;
	mod->data[0][1] = E.a; // a

    F->f = multiply(F->f, G->f, mod ,E); //  F->f = modulo for now.
    F->g = multiply(F->g, G->g, mod, E);// F->f = mod for now.

    return F;
}
