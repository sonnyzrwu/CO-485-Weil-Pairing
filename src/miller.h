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



