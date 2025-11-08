#ifndef SVD_H
#define SVD_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **transpose(double **A, int r, int c);
double **multiplication(double **A, double **B, int m, int n, int p);
double error_norm(double **A, double **B, int r, int c);
double **createMatrix(int r, int c);
void free_mat(double **A, int r);
double *power_iter(double **M, int n);
void svd(double **A, int r, int c, int k,
         double ***OU, double ***OS, double ***OV);

#endif

