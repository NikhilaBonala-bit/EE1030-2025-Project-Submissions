#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "svd.h"

double **transpose(double **A, int r, int c){
    double **AT = malloc(c * sizeof(double *));
    for(int i=0; i<c; i++) AT[i] = malloc(r * sizeof(double));
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            AT[j][i] = A[i][j];
    return AT;
}

double **multiplication(double **A, double **B, int m, int n, int p){
    double **C = malloc(m * sizeof(double *));
    for(int i=0; i<m; i++){
        C[i] = malloc(p * sizeof(double));
        for(int j=0; j<p; j++) C[i][j] = 0.0;
    }
    for(int i=0; i<m; i++)
        for(int j=0; j<p; j++)
            for(int k=0; k<n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

double error_norm(double **A, double **B, int r, int c){
    double sum = 0.0;
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            sum += (A[i][j]-B[i][j])*(A[i][j]-B[i][j]);
    return sqrt(sum);
}

double **createMatrix(int r, int c){
    double **M = malloc(r * sizeof(double *));
    for(int i=0; i<r; i++){
        M[i] = malloc(c * sizeof(double));
        for(int j=0; j<c; j++) M[i][j] = 0.0;
    }
    return M;
}

void free_mat(double **A, int r){
    for(int i=0; i<r; i++) free(A[i]);
    free(A);
}

double *power_iter(double **M, int n){
    double *X = malloc(n * sizeof(double));
    double *NX = malloc(n * sizeof(double));
    double l = 0.0;

    for(int i=0; i<n; i++) X[i] = 1.0/n;

    for(int k=0; k<1000; k++){
        for(int i=0; i<n; i++){
            NX[i] = 0.0;
            for(int j=0; j<n; j++) NX[i] += M[i][j] * X[j];
        }

        //normalising the vector
        double norm = 0.0;
        for(int i=0; i<n; i++) norm += NX[i]*NX[i];
        norm = sqrt(norm);
        for(int i=0; i<n; i++) NX[i] /= norm;

        double nl = 0.0;
        for(int i=0; i<n; i++){
            double temp = 0.0;
            for(int j=0; j<n; j++) temp += M[i][j] * NX[j];
            nl += temp * NX[i];
        }

        if(fabs(nl - l) < 1e-6) break;
        l = nl;
        double *y = X; X = NX; NX = y;
    }

    double *res = malloc((n+1)*sizeof(double));
    res[0] = l;
    for(int i=0; i<n; i++) res[i+1] = X[i];
    free(X); free(NX);
    return res;
}

void svd(double **A, int r, int c, int k, double ***OU, double ***OS, double ***OV){
    double **AT = transpose(A, r, c);
    double **ATA = multiplication(AT, A, c, r, c);

    double **U = createMatrix(r, k);
    double **S = createMatrix(k, k);
    double **V = createMatrix(c, k);

    for(int i=0; i<k; i++){
        double *res = power_iter(ATA, c);
        double l = res[0], s = sqrt(l);
        double *v = &res[1];

        for(int j=0; j<c; j++) V[j][i] = v[j];
        S[i][i] = s;

        for(int j=0; j<r; j++){
            double sum = 0.0;
            for(int t=0; t<c; t++) sum += A[j][t] * v[t];
            U[j][i] = sum/s;
        }

        for(int x=0; x<c; x++)
            for(int y=0; y<c; y++)
                ATA[x][y] -= l * v[x] * v[y];

        free(res);
    }

    free_mat(AT, c);
    free_mat(ATA, c);
    *OU = U; *OS = S; *OV = V;
}

