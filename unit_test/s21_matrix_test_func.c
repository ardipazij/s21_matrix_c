#include <check.h>

#include "../s21_matrix.h"
#define S21_SUCCESS 0
#define S21_INCORRECT 1
#define S21_ARTH_ERROR 2

START_TEST(s21_test_create1) {
  matrix_t my_matrix;
  int ret = s21_create_matrix(4, 4, &my_matrix);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&my_matrix);

  ret = s21_create_matrix(-4, 4, &my_matrix);
  ck_assert_int_eq(ret, 1);

  ret = s21_create_matrix(-4, 0, &my_matrix);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(s21_test_equal1) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2;
  A.matrix[1][0] = 2;
  A.matrix[0][1] = 2;
  A.matrix[1][1] = 2;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 2;
  B.matrix[1][0] = 2;
  B.matrix[0][1] = 2;
  B.matrix[1][1] = 2;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_test_equal2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2;
  A.matrix[1][0] = 0;
  A.matrix[0][1] = 2;
  A.matrix[1][1] = 2;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 2;
  B.matrix[1][0] = 2;
  B.matrix[0][1] = 2;
  B.matrix[1][1] = 2;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_test_equal3) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2;
  A.matrix[1][0] = 0;
  A.matrix[0][1] = 2;
  A.matrix[1][1] = 2;
  matrix_t B;
  s21_create_matrix(2, 1, &B);
  B.matrix[0][0] = 2;
  B.matrix[1][0] = 2;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_test_sum1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[1][0] = 0;
  A.matrix[0][1] = 2;
  A.matrix[1][1] = 2;
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 2;
  B.matrix[1][0] = 2;
  B.matrix[0][1] = 2;
  B.matrix[1][1] = 2;
  matrix_t result;
  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.matrix[0][0], 4);
  ck_assert_int_eq(result.matrix[1][1], 4);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * 2;
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t matrix_1, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_mult_number(&matrix_1, 5, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * (-3);
    }
  }
  ret = s21_mult_number(&matrix_1, -3, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
    }
  }
  ret = s21_mult_number(&matrix_1, 0, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t mat_1, mat_2, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = i + j + 1;
      mat_2.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(3, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(3, 2, &res_org);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(2, 7, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t mat_1, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  mat_1.matrix[0][0] = 1;
  mat_1.matrix[0][1] = 2;
  mat_1.matrix[1][0] = 3;
  mat_1.matrix[1][1] = 4;
  res_org.matrix[0][0] = 1;
  res_org.matrix[0][1] = 3;
  res_org.matrix[1][0] = 2;
  res_org.matrix[1][1] = 4;
  int ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  double matrix[2][2] = {
      {1, 2},
      {3, 4},
  };
  double res[2][2] = {{1, 3}, {2, 4}};
  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      res_org.matrix[i][j] = res[i][j];
    }
  }
  ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(s21_determinant_test) {
  int result;
  double output = 0;
  double tt = 31.000;
  matrix_t m1;

  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 3;
  m1.matrix[0][2] = 2;
  m1.matrix[1][0] = 4;
  m1.matrix[1][1] = 6;
  m1.matrix[1][2] = 7;
  m1.matrix[2][0] = 3;
  m1.matrix[2][1] = 4;
  m1.matrix[2][2] = 0;

  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_SUCCESS);
  ck_assert_double_eq(output, tt);
  s21_remove_matrix(&m1);

  s21_create_matrix(-1, 3, &m1);
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);

  s21_create_matrix(4, 3, &m1);
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  s21_create_matrix(3, 4, &m1);
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  // One more
  s21_create_matrix(2, 2, &m1);
  m1.matrix[0][0] = 3;
  m1.matrix[0][1] = 2;
  m1.matrix[1][0] = 7;
  m1.matrix[1][1] = -1;
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_SUCCESS);
  ck_assert_double_eq_tol(output, -17, 1e-7);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

Suite *suite_matrix(void) {
  Suite *suite = suite_create("matrix_suite");
  TCase *tc = tcase_create("matrix_tc");

  tcase_add_test(tc, s21_test_create1);
  tcase_add_test(tc, s21_test_equal1);
  tcase_add_test(tc, s21_test_equal2);
  tcase_add_test(tc, s21_test_equal3);
  tcase_add_test(tc, s21_test_sum1);
  tcase_add_test(tc, test_s21_sum_matrix);
  tcase_add_test(tc, test_s21_sub_matrix);
  tcase_add_test(tc, test_s21_mult_number);
  tcase_add_test(tc, test_s21_mult_matrix);
  tcase_add_test(tc, test_s21_transpose);
  tcase_add_test(tc, s21_determinant_test);
  tcase_add_test(tc, test_s21_calc_complements);
  tcase_add_test(tc, test_s21_inverse_matrix);

  suite_add_tcase(suite, tc);
  return suite;
}

void run_set(Suite *suite_matrix) {
  // Представляет собой окружение для запуска тестов. Запускает наш набор
  // тестов.
  SRunner *all_test = srunner_create(suite_matrix);

  srunner_set_fork_status(all_test, CK_NOFORK);
  srunner_run_all(all_test, CK_NORMAL);

  srunner_free(all_test);
}
void test_sets(void) { run_set(suite_matrix()); }
int main(void) {
  test_sets();
  return 0;
}
