# s21_matrix_c
Implementation of functions for working with matrixes.
0 - OK
1 - Error, incorrect matrix
2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)
| Operation | Description |
| ----------- | ----------- |
| `int s21_create_matrix(int rows, int columns, matrix_t *result)` | Create Matrix |
| `void s21_remove_matrix(matrix_t *A)` | Remove Matrix |
| `int s21_eq_matrix(matrix_t *A, matrix_t *B)` | Checks matrices for equality with each other |
| `int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)` | Adds the second matrix to the current one |
| `int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);` | Subtracts another matrix from the current one |
| `int s21_mult_number(matrix_t *A, double number, matrix_t *result) ` | Multiplies the current matrix by a number |
| `int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)` | Multiplies the current matrix by the second matrix |
| `int s21_transpose(matrix_t *A, matrix_t *result)` | Creates a new transposed matrix from the current one and returns it |
| `int s21_calc_complements(matrix_t *A, matrix_t *result)` | Calculates the algebraic addition matrix of the current one and returns it |
| `int s21_determinant(matrix_t *A, double *result)` | Calculates and returns the determinant of the current matrix |
| `int s21_inverse_matrix(matrix_t *A, matrix_t *result)` | Calculates and returns the inverse matrix |

A Makefile is provided for the project to build the library and tests (with targets all, clean, test, s21_matrix.a, gcov_report);
