#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b)) ? (a) : (b) // Macro to find the maximum of two values

void transpose(int *matrix, int m, int n, int ld) {
    for (int i = 0; i < ld; i++) { // Loop over the rows
        for (int j = i + 1; j < ld; j++) { // Loop over the columns, j starts from i+1,the upper triangular part
            int temp = matrix[i * ld + j]; // swap the corresponding elements,store the upper triangular part,(i,j)to(j,i)
            matrix[i * ld + j] = matrix[j * ld + i];//
            matrix[j * ld + i] = temp;
        }
    }
}

// only the upper triangular part is transposed,or they will be switched for two times,back to the origin

