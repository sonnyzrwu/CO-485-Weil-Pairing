#include <stdio.h>
#include "miller.h"  




int main(){
	printf("Okay here we go... \n");
	struct Point generator = {9, 12, 0};
	struct EllipticCurve toy = {17, 1, 1, 1, generator}; 

	struct Polynomial * linePQ = NULL;
	linePQ = makePolynomial(linePQ, 2, 2);
	linePQ->data[1][0] = -1;
	linePQ->data[0][1] = 2; //slope 2
	linePQ->data[0][0] = 3;

	struct Polynomial * vertLine = NULL;
	vertLine = makePolynomial(vertLine, 1, 2);
	vertLine->data[0][1] = 1;
	vertLine->data[0][0] = 1;

	struct RationalFunction * F = NULL;
	F = makeRationalFunction(F, 2, 2, 1, 2);
	copyData(&F->f->data, linePQ);
	copyData(&F->g->data, vertLine);



	print(F->f->data, F->f->rows, F->f->cols);
	print(F->g->data, F->g->rows, F->g->cols);

	
	struct RationalFunction *G = NULL;
	G = makeRationalFunction(G, 2, 2, 1, 2);
	copyData(&G->f->data, linePQ);
	copyData(&G->g->data, vertLine);
	

	F = multiplyRF(F, G, toy);
	F = multiplyRF(F, G, toy);
	F = multiplyRF(F, G, toy);
	F = multiplyRF(F, G, toy);
	F = multiplyRF(F, G, toy);
	F = multiplyRF(F, G, toy);
	

	print(F->f->data, F->f->rows, F->f->cols);
	print(F->g->data, F->g->rows, F->g->cols);

	destroyPolynomial(linePQ);
	destroyPolynomial(vertLine);
	destroyRationalFunction(F);
	return 0;
}
