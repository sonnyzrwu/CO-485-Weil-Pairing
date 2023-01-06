#include <stdio.h>
#include "miller.h"  

int main(){
	printf("Okay here we go... \n");
	//struct Point generator = {11, 9, 0};
	// struct EllipticCurve toy = {12, 1, 1, 0, generator}; 
	//struct Point t = {2, 1, 0};

	struct Polynomial * poly = NULL;
	struct Polynomial * poly2 = NULL;
	struct Polynomial * mod = NULL;



	poly = makePolynomial(poly, 3, 3);

	poly->data[0][1] = 1;
	poly->data[1][0] = 1;
	poly2 = makePolynomial(poly2, 3, 3);

	poly2->data[0][1] = 1;
	poly2->data[1][0] = 1;

	mod = makePolynomial(mod, 3, 4);
	
	mod->data[0][0] = 1; // b
	
	mod->data[2][0] = -1;
	mod->data[0][3] = 1;
	mod->data[0][1] = 1; // a
	
	
	
	poly = multiply(poly, poly2, mod);// (x+1) (x+1)
	print(poly->data, poly->rows, poly->cols);// 1 2 1
	printf("Segfault after multiply? \n");
	
	poly = multiply(poly, poly2, mod);// (x+1)^2 * (x+1)
	print(poly->data, poly->rows, poly->cols);


	poly = multiply(poly, poly2, mod);// 
	print(poly->data, poly->rows, poly->cols);
	
	destroyPolynomial(poly);
	destroyPolynomial(poly2);
	destroyPolynomial(mod);

	return 0;
}
