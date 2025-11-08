#include <stdio.h>
#include <stdlib.h>
#include "convert.h"
#include "svd.h"

int main() {
    char input[100];
    printf("Enter filename: ");
    scanf("%s", input);

    int r, c;
    double **A = convert_img(input, &r, &c);
    int k[] = {10, 20, 50, 120}; 
    int n = sizeof(k) / sizeof(k[0]);

    for (int i = 0; i < n; i++) {
        int m = k[i];

        double **U, **S, **V;
        svd(A, r, c, m, &U, &S, &V);

        double **VT = transpose(V, c, m);
        double **US = multiplication(U, S, r, m, m);
        double **A_m = multiplication(US, VT, r, m, c);

        char output[150];
        snprintf(output, sizeof(output), "outputk%d.pgm", m);
        convert_mat(output, A_m, r, c);

        free_mat(U, r);
        free_mat(S, m);
        free_mat(V, c);
        free_mat(VT, m);
        free_mat(US, r);
        free_mat(A_m, r);
    }

    free_mat(A, r);
    return 0;
}

