#include <stdio.h>
#include <stdlib.h>
#include "matrixfunctions.h"
#include <math.h>


int main()
{
    //Две матрицы и их размеры
    long double **matrix_1;
    long double **matrix_2;
    unsigned long long line_1, column_1, line_2, column_2;

    //Ввод двух матриц
    matrix_1 = read_matrix(&line_1, &column_1);
    out_matrix(matrix_1, line_1, column_1);
    matrix_2 = read_matrix(&line_2, &column_2);
    out_matrix(matrix_2, line_2, column_2);
    

    //Умножение на константу
    long double **matrixMULonC;
    matrixMULonC = mul_on_num (matrix_1, &line_1, &column_1, 10);
    printf("multiplying on number, wait...\n");
    out_matrix(matrixMULonC, line_1, column_1);
    matrix_free(matrixMULonC, line_1);
        
    //Сложение двух матриц
    long double **matrixSUM;
    printf("taking a sum of two matrices, wait...\n");
    matrixSUM = sum_two_matrix (matrix_1, &line_1, &column_1, matrix_2, &line_2, &column_2);
    out_matrix(matrixSUM, line_1, column_1);
    if (matrixSUM != NULL) matrix_free(matrixSUM, line_1);
    
    //Умножение двух матриц
    long double **matrix2MUL;
    printf("taking a multiply of two matrices, wait...\n");
    matrix2MUL = mul_two_matrix (matrix_1, &line_1, &column_1, matrix_2, &line_2, &column_2);
    out_matrix(matrix2MUL, line_1, column_2);
    if (matrix2MUL != NULL) matrix_free(matrix2MUL, line_1);

    //Вычисление определителя
    long double matrixDET;
    matrixDET = matrix_det (matrix_1, line_1, column_1);
    printf("Determinant is: %Lf\n", matrixDET);


    //Освобождение памяти из-под двух матриц
    matrix_free(matrix_1, line_1);
    matrix_free(matrix_2, line_2);
    return 0;
}
