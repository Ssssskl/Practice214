#ifndef Matrixfunctions
#define Matrixfunctions

long double **read_matrix (unsigned long long *line, unsigned long long *column);
void out_matrix(long double **matrix, unsigned long long line, unsigned long long column);
void matrix_free(long double **matrix, unsigned long long line);
long double **sum_two_matrix (long double **matrix_1, unsigned long long *line_1, unsigned long long *column_1, long double **matrix_2, unsigned long long *line_2, unsigned long long *column_2);
long double **mul_on_num (long double **matrix, unsigned long long *line, unsigned long long *column, long double num);
long double **mul_two_matrix (long double **matrix_1, unsigned long long *line_1, unsigned long long *column_1, long double **matrix_2, unsigned long long *line_2, unsigned long long *column_2);
long double matrix_det (long double **matrix, unsigned long long line, unsigned long long column);

#endif
