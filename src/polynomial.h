#include <stdlib.h>
#include <assert.h>

void print(int **P, int pr, int pc){
    for(int i = 0; i < pr; ++i){
        for(int j = 0; j < pc; ++j){

            printf("%d ", P[i][j]);
            //if ( ((i != pr-1) || (j != pc-1)) && ( P[i][j] != 0 )) printf(" (%d y^%d*x^%d) + ", P[i][j], i, j);
            // else if (((i == pr-1) && (j == pc-1)) && P[i][j] != 0) printf(" (%d y^%d*x^%d) ", P[i][j], i, j );


        }
        printf("\n");
    }
    printf("\n");
    printf("\n");

}


//data[i][j] = (y^i)(x^j)

struct Polynomial{
    int **data;
    int rows; 
    int cols;
};

struct Polynomial * makePolynomial(struct Polynomial *poly, int rows, int cols){
    ( poly) = malloc(sizeof(struct Polynomial));
    ( poly)->data= (int **) malloc(rows*sizeof(int *));
    for(int i = 0; i < rows; ++i) ( poly)->data[i] = (int * ) malloc(cols* sizeof(int));

    for(int i =0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            (poly)->data[i][j] = 0;
        }
    }


    ((poly)->rows) = rows;
    
    ((poly)->cols) = cols;
    return poly;
}

void destroyPolynomial( struct Polynomial * poly){
    for(int i = 0; i < poly->rows; ++i) {
        if (poly->data[i] != NULL) free(poly->data[i]); 
    }
    free(poly->data);
    poly->data = NULL;
    free(poly);
    poly = NULL;

}


// pass in the fields of the struct Polynomial. New dimensions first, then old dimensions.
void adjustPolynomial(int ***data, int *newrows, int *newcols, int *oldrows, int *oldcols){

    
    (*data) = (int **) realloc((*data), (*newrows) * sizeof(int *)); // could this leak memory?

    
    for(int i = 0; i <(*oldrows); ++i){
        if ( (*data)[i] != NULL) (*data)[i] = realloc((*data)[i], (*newcols) * sizeof(int) );
    }
    for(int i = *oldrows; i < *newrows; ++i){
        (*data)[i] =  malloc( (*newcols) * sizeof(int) );
    }


    for(int i = 0; i < *newrows; ++i){
        
        for(int j = 0; j < *newcols; ++j){
           
            if ( (i >= *oldrows) || (j >= *oldcols)) (*data)[i][j] = 0;
        }
    }

  
    *oldrows = *newrows;
    *oldcols = *newcols;

}

// 
void copyData(int *** copy, struct Polynomial *poly){
    for(int i = 0; i < poly->rows; ++i){
        for(int j = 0; j < poly->cols; ++j){
            (*copy)[i][j] = poly->data[i][j];
        }
    }
}


int columnsToDelete(int *** data, int* rows, int * cols){
    int colsToDelete = 0;
    int oldcol = *cols;
    int row = *rows;

    for(int j = oldcol - 1 ; j >= 0; --j){
        for(int i = 0; i < row; ++i){
            if ((*data)[i][j] != 0 ){
                return colsToDelete;
            }
        }
        // then increment 1
        ++colsToDelete;

    }
    return colsToDelete;
}

void trimPolyCols(int ***data, int * rows, int * cols){
    int oldcol = *cols;
    int row = *rows;
    int colsToDelete = columnsToDelete(data, rows, cols);
    if (oldcol - colsToDelete == 0) return;
    for(int i = 0; i < row; ++i){
        if ((*data)[i] != NULL)
            (*data)[i] = realloc((*data)[i],  (oldcol - colsToDelete)* sizeof(int));
        

    }
    *cols = oldcol -  colsToDelete;

}

int rowesToDelete(int *** data, int * rows, int * cols){
    int oldrow = *rows;
    int col = *cols;

    int rowsToDelete = 0;

    

    for(int i = oldrow-1 ; i >= 0; --i){
        for(int j = 0; j < col; ++j){
          
            if ((*data)[i][j] != 0){ // if we find a nonzero row, we need this row, and everything above.
                return rowsToDelete; 
            }
        }
        ++rowsToDelete;
    }
    return rowsToDelete;
}


void trimPolyRows(int ***data, int * rows, int * cols){

    int oldrow = *rows;

    int rowsToDelete = rowesToDelete(data, rows, cols);

    if (rowsToDelete == oldrow) return;

    for (int i = 1; i <= rowsToDelete; ++i){ // loops rowsToDelete times
        free( (*data)[oldrow - i] );
        (*data)[oldrow - i] = NULL;

    }
    if (*data != NULL) (*data) = (int **) realloc( (*data), (oldrow - rowsToDelete) * sizeof(int *) );
    *rows = oldrow - rowsToDelete;
}
  


// modifies f
// f = f*g, make sure f and g are not pointing to the same address.
// if we wish square f, create another polynomial with the same data and fields as f.
// try to reduce to keep coputations small and fast.
struct Polynomial * multiply( struct Polynomial *f, struct Polynomial *g, struct Polynomial *modulo, struct EllipticCurve E){
    assert(f != g);

    // make a new copy of f, and copy the data to temp.
    struct Polynomial * temp = NULL;
    temp = makePolynomial(temp, f->rows, f->cols);
    copyData(&(temp->data), f);
    int oldrows = temp->rows;
    int oldcols = temp->cols;


    // resize f and set f to zero polynomial
    int c1 = ((f->rows) * (g->rows));

    int newrows = (((f->rows) * (g->rows))) + 1;
    int newcols = (((f->cols) * (g->cols))) + 1;

    printf("newrows:= %d, newcols: %d \n", newrows, newcols);
  
    adjustPolynomial(&(f->data), &newrows, &newcols, &f->rows, &f->cols); // make it bigger


    int ***data = &(f->data);
    for(int i = 0; i < oldrows; ++i){
        for(int j = 0; j < oldcols; ++j){
            (*data)[i][j] = 0;
        }
    }    



    // peform the multiplication
    for( int i = 0; i < oldrows; ++i){
        for(int j = 0; j < oldcols; ++j){ // for every element in P with y^i x^j
            for(int k = 0; k < g->rows; ++k){
                for(int l = 0; l < g->cols; ++l){// for every element in Q with y^k x^l
                    // contributes to y^(i+k)x^(j+l)
                    (*data)[i+k][j+l]+= ( (temp->data[i][j]) * (g->data[k][l]) );
                    (*data)[i+k][j+l] = (*data)[i+k][j+l] % E.p;

                    
                }

            }

        }
    }
  
   destroyPolynomial(temp); 

   // trim the dimensions of any excess columns and rows.
  
   trimPolyRows(&(f->data), &(f->rows), &(f->cols));
   trimPolyCols(&(f->data), &(f->rows), &(f->cols));
   return f;
}







