#include "eea.h"


struct Point{
    int x;
    int y;
    int isInf;

};

struct EllipticCurve{
    const int p;
    const int k; // Operations in the GF(p^k)
    const int a;
    const int b;
    struct Point generator; 
};


struct Point pointWiseAddition( struct Point *P, struct Point *Q, struct EllipticCurve E );