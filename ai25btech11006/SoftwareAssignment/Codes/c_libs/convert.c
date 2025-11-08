#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

double **convert_img(const char *name, int *rows, int *cols) {
    FILE *sn = fopen(name, "rb");
    if(!sn){
        perror("Error opening file");
        return;
    }

    char format[3];
    fscanf(sn, "%2s", format);
    if(strcmp(format, "P5") != 0){
        printf("Invalid format\n");
        fclose(sn);
        return;
    }

    
    fgetc(sn);

    int maxval;
    fscanf(sn, "%d %d %d", cols, rows, &maxval);
    fgetc(sn);

    double **image = malloc((*rows) * sizeof(double *));
    for(int i = 0; i < *rows; i++){
        image[i] = malloc((*cols) * sizeof(double));
    }

    for(int i = 0; i < *rows; i++){
        unsigned char *temp = malloc(*cols);
        fread(temp, sizeof(unsigned char), *cols, sn);
        for(int j = 0; j < *cols; j++){
            image[i][j] = (double)temp[j];
        }
        free(temp);
    }

    fclose(sn);
    return image;
}

void convert_mat(const char* name, double** matrix, int r, int c) {
    FILE* sn = fopen(name, "wb");
    if(!sn){
        perror("Error opening file for writing");
        return;
    }

    
    fprintf(sn, "P5\n%d %d\n255\n", c, r);

    for(int i = 0; i < r; i++){
        unsigned char* row = malloc(c);
        for(int j = 0; j < c; j++){
            int val = (int)matrix[i][j];
            if(val < 0) val = 0;
            if(val > 255) val = 255;
            row[j] = (unsigned char)val;
        }
        fwrite(row, sizeof(unsigned char), c, sn);
        free(row);
    }

    fclose(sn);
}

