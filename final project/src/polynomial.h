#include <stdlib.h>


struct Polynomial {
    int **data;
    int rows; // rows - 1 = partial degree of Y
    int cols;  // cols - 1 = partial degree of x
};

// BEWARE: borrows from the HEAP.
struct Polynomial *make_polynomial(int r, int c) { 
    struct Polynomial *a = (struct Polynomial * ) malloc(sizeof(struct Polynomial)); // 
    a->data = (int **) malloc( r * sizeof(int *)); // y deg
    for(int i = 0; i < r; ++i){
        a->data[i] = (int *) malloc( c* sizeof(int)); // x deg
    }

    a->cols = c;
    a->rows = r;

    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j ){
            a->data[i][j] = 0;
        }
    }

   

    return a;
}


void destroy_polynomial(struct Polynomial *p) {

    for(int i = 0; i < p->rows; ++i){
        free(p->data[i]);
    }

    free(p->data);
    free(p);

}


// BEWARE: borrows from the HEAP.
struct Polynomial *multiply(struct Polynomial *P, struct Polynomial *Q){
    struct Polynomial *R = make_polynomial(P->rows + Q->rows -1, P->cols + Q->cols-1);

    int i = 0;
    for( i = 0; i < P->rows; ++i){
        for(int j = 0; j < P->cols; ++j){ // for every element in P with y^i x^j
            for(int k = 0; k < Q->rows; ++k){
                for(int l = 0; l < Q->cols; ++l){// for every element in Q with y^k x^l

                    R->data[i+k][j+l]+= (P->data[i][j]) * (Q->data[k][l]);
                    //printf("%d ", i);
                }

            }

        }
    }
   //printf("\n");
    return R;
}




