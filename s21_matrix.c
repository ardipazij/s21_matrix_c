#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 1 || columns < 1) return INCORRECT_MATRIX;
  int flag_error = OK;
  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    flag_error = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }
  return flag_error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int non_exist(matrix_t *strange_matrix) {
  if (strange_matrix == NULL || strange_matrix->rows < 1 ||
      strange_matrix->columns < 1 || strange_matrix->matrix == NULL)
    return SUCCESS;
  else
    return FAILURE;
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (non_exist(A) || non_exist(B) || A->rows != B->rows ||
      A->columns != B->columns)
    result = FAILURE;
  else {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < B->columns && result; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}
int s21_ariphetic(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
  if (non_exist(A) || non_exist(B)) return INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERROR;
  int flag_error = OK;
  if (!s21_create_matrix(A->rows, A->columns, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + sign * B->matrix[i][j];
      }
    }
  } else {
    flag_error = INCORRECT_MATRIX;
  }
  return flag_error;
}
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return (s21_ariphetic(A, B, result, 1));
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return (s21_ariphetic(A, B, result, -1));
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (non_exist(A)) return INCORRECT_MATRIX;
  if(s21_create_matrix(A->rows, A->columns, result)) return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (non_exist(A) || non_exist(B)) return INCORRECT_MATRIX;
  if (A->columns != B->rows) return CALC_ERROR;
  if(s21_create_matrix(A->rows, B->columns, result)) return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (non_exist(A)) return INCORRECT_MATRIX;
  if(s21_create_matrix(A->columns, A->rows, result)) return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}
void s21_get_minor(matrix_t *mat, matrix_t *temp, int ex_row, int ex_col) {
  int i = 0, j = 0;
  for (int row = 0; row < mat->rows; row++) {
    for (int col = 0; col < mat->columns; col++) {
      if (row != ex_row && col != ex_col) {
        temp->matrix[i][j] = mat->matrix[row][col];
        j++;
        if (j == mat->columns - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}
int s21_determinant(matrix_t *A, double *result) {
  if (non_exist(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else {
    matrix_t temp;
    double det__ = 0;
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      if(s21_create_matrix(A->rows - 1, A->columns - 1, &temp)) return INCORRECT_MATRIX;
      s21_get_minor(A, &temp, i, 0);
      double res;
      s21_determinant(&temp, &res);
      det__ += sign * A->matrix[i][0] * res;
      ;
      sign *= -1;
      s21_remove_matrix(&temp);
    };
    *result = det__;
  }
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (non_exist(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;
  if(s21_create_matrix(A->rows, A->columns, result)) return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t temp;
      if(s21_create_matrix(A->rows - 1, A->columns - 1, &temp)) return INCORRECT_MATRIX;
      s21_get_minor(A, &temp, i, j);
      double det_temp;
      if(s21_determinant(&temp, &det_temp)) return INCORRECT_MATRIX;
      result->matrix[i][j] = pow(-1, i + j) * det_temp;
      s21_remove_matrix(&temp);
    }
  }
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag_error = OK;
  if (non_exist(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;
  double det;
  if(s21_determinant(A, &det)) return INCORRECT_MATRIX;
  if (det == 0) return CALC_ERROR;
  matrix_t transpouse, alg_d;
  int is_exist_transpouse, is_exist_alg_g;
  is_exist_alg_g = s21_calc_complements(A, &alg_d);
  if (!is_exist_alg_g && !non_exist(&alg_d)) {
    is_exist_transpouse = s21_transpose(&alg_d, &transpouse);
    if (!is_exist_transpouse && !non_exist(&transpouse)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = transpouse.matrix[i][j] / det;
        }
      }
    } else {
      flag_error = CALC_ERROR;
    }
    if (!flag_error) s21_remove_matrix(&transpouse);
  } else {
    flag_error = CALC_ERROR;
  }
  if (!flag_error) s21_remove_matrix(&alg_d);
  return flag_error;
}
