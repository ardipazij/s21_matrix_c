#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPS 0.0000001
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);
/// @brief сложение
/// @param A
/// @param B
/// @param result
/// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
/// (несовпадающие размеры матриц; матрица, для которой нельзя провести
/// вычисления и т.д.)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// /// @brief вычитание
// /// @param A
// /// @param B
// /// @param result
// /// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
// /// (несовпадающие размеры матриц; матрица, для которой нельзя провести
// /// вычисления и т.д.)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// /// @brief умножение на число
// /// @param A
// /// @param number
// /// @param result
// /// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
// /// (несовпадающие размеры матриц; матрица, для которой нельзя провести
// /// вычисления и т.д.)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// /// @brief умножение двух матриц
// /// @param A
// /// @param B
// /// @param result
// /// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
// /// (несовпадающие размеры матриц; матрица, для которой нельзя провести
// /// вычисления и т.д.)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// /// @brief транспонирование
// /// @param A
// /// @param result
// /// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
// /// (несовпадающие размеры матриц; матрица, для которой нельзя провести
// /// вычисления и т.д.)
int s21_transpose(matrix_t *A, matrix_t *result);
// /// @brief минор
// /// @param A
// /// @param result
// /// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
// /// (несовпадающие размеры матриц; матрица, для которой нельзя провести
// /// вычисления и т.д.)
int s21_calc_complements(matrix_t *A, matrix_t *result);
// /// @brief определитель
// /// @param A
// /// @param result
// /// @return
int s21_determinant(matrix_t *A, double *result);
// /// @brief инвертирование
// /// @param A
// /// @param result
// /// @return 0 - OK 1 - Ошибка, некорректная матрица 2 - Ошибка вычисления
// /// (несовпадающие размеры матриц; матрица, для которой нельзя провести
// /// вычисления и т.д.)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#endif