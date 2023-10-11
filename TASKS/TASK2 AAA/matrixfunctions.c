#include <stdio.h>
#include <stdlib.h>
#include "matrixfunctions.h"
#include <math.h>

long double **read_matrix (unsigned long long *line, unsigned long long *column)
{
    long double **matrix;
    long long n;
    printf("%s\n", "Enter a number of lines:");
    scanf("%lld", &n);
    while (n <= 0)
    {
        printf("%s\n", "Ooops, incorrect data! Please enter correct number of lines: ");
        scanf("%lld", &n);
    }
    *line = n;
    printf("%s\n", "Enter a number of columns:");
    scanf("%lld", &n);
     while (n <= 0)
    {
        printf("%s\n", "Ooops, incorrect data! Please enter correct number of columns: ");
        scanf("%lld", &n);
    }
    *column = n;
    matrix = malloc(*line*sizeof(long double*));
    for (unsigned long long i = 0; i < *line; i++)
    {
        matrix[i] = malloc(*column*sizeof(long double));
        printf("%s", "Enter elements of line ");
        printf("%lld\n", i + 1);
        for (unsigned long long j = 0; j < *column; j++)
        {
            scanf("%Lf", &matrix[i][j]);
        }
    }
    return matrix;
}

void out_matrix(long double **matrix, unsigned long long line, unsigned long long column)
{
    if (matrix == NULL)
        return;
    printf("Your matrix:\n");
    for (unsigned int i = 0; i < line; i++)
    {
        for (unsigned int j = 0; j < column; j++)
        {
            printf("%Lf", matrix[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void matrix_free(long double **matrix, unsigned long long line)
{
    for (unsigned long long i = 0; i < line; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

long double **sum_two_matrix (long double **matrix_1, unsigned long long *line_1, unsigned long long *column_1, long double **matrix_2, unsigned long long *line_2, unsigned long long *column_2)
{
    if (!matrix_1  || !matrix_2)
    {
        printf("ERROR! That's not a matrix!\n");
        return NULL;
    }
    if (*line_1 != *line_2 || *column_1 != *column_2)
    {
        printf("ERROR! The matrices have different sizes\n");
        return NULL;
    }
    long double **result = malloc(*line_1*sizeof(long double*));
    for (unsigned int i = 0; i < *line_1; i++)
    {
        result[i] = malloc(*column_1*sizeof(long double));
        for (unsigned int j = 0; j < *column_1; j++)
        {
            result[i][j] =  matrix_1[i][j] + matrix_2[i][j];
        }
    }
    return result;
}

long double **mul_on_num (long double **matrix, unsigned long long *line, unsigned long long *column, long double num)
{
    if (!matrix)
    {
        printf("ERROR! That's not a matrix!\n");
        return NULL;
    }
    long double **result = malloc(*line*sizeof(long double*));
    for (unsigned int i = 0; i < *line; i++)
    {
        result[i] = malloc(*column*sizeof(long double));
        for (unsigned int j = 0; j < *column; j++)
        {
            result[i][j] =  matrix[i][j] * num;
        }
    }
    return result;
}

long double **mul_two_matrix (long double **matrix_1, unsigned long long *line_1, unsigned long long *column_1, long double **matrix_2, unsigned long long *line_2, unsigned long long *column_2)
{
    if (!matrix_1  || !matrix_2)
    {
        printf("ERROR! That's not a matrix!\n");
        return NULL;
    }
    if (*column_1 != *line_2)
    {
        printf("ERROR! The matrices have incorrect sizes for multiplication");
        return NULL;
    }
    long double **result = malloc(*line_1*sizeof(long double*));
    for (unsigned int i = 0; i < *line_1; i++)
    {
        result[i] = malloc(*column_2*sizeof(long double));
        for (unsigned int j = 0; j < *column_2; j++)
        {
            result[i][j] = 0;
            for (unsigned int n = 0, m = 0; n < *column_1, m < *line_2; n++, m++)
            {
                result[i][j] += (matrix_1[i][n] * matrix_2[m][j]);
            }
        }
    }
    return result;
}


long double matrix_det (long double **matrix, unsigned long long line, unsigned long long column)
{
    if (!matrix)
    {
        printf("Error! Invalid type of matrix\n");
        return 0;
    }
    if (line != column)
    {
        printf("Error! Invalid type of matrix\n");
        return 0;
    }
    if (line <= 0) 
    {
        printf("Error! Invalid type of matrix\n");
        return 0;
    }
    if ( line == 1 )
    {
        return **matrix;
    }
    long double result = 0;
    for (unsigned int k = 0; k < line; k++)
    {
        long double **new_matrix = malloc((line - 1) *sizeof(long double*));
        for (unsigned int i = 0; i < line - 1; i++)
        {
            new_matrix[i] = malloc((line - 1) * sizeof(long double));
            for (unsigned int j = 0; j < line; j++)
            {
                if (j < k)
                {
                    new_matrix[i][j] = matrix[i + 1][j];
                }
                if (j > k)
                {
                    new_matrix[i][j - 1] = matrix[i + 1][j];
                }
            }
        }
        result = result + matrix_det(new_matrix, line - 1, line - 1) * (matrix[0][k]) * pow(-1,k);
        matrix_free(new_matrix, line - 1); 
    }
    return result;    
}


