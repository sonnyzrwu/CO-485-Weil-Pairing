#include <stdio.h>
#include "miller.h"




int main(){
	printf("Okay here we go... \n");
	struct Point generator = {11, 9, 0};
	struct EllipticCurve toy = {12, 1, 2, 2, generator}; 
	struct Point t = {2, 1, 0};

	struct Point * P = &t;

	printf("Working millers algorithm... \n ");

	struct RationalFunction *f = miller(5, P, toy);

	int ** arr = f->P->data;

	int row = f->P->rows;

	int col = f->P->cols;

	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j){
			printf("%d ",arr[i][j]);

		}
		printf("\n");
	}

	destroy_rational_function(f);

	return 0;
}

