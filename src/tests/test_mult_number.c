#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A;
  matrix_t C;
  matrix_t result;
  double tmp;
  double number = 19.873;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &A);
  ret += s21_create_matrix(rows, columns, &C);
  if (ret == 0) {
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        A.matrix[i][j] = tmp;
        C.matrix[i][j] = tmp * number;
        tmp += 0.444;
      }
    }

    ret = s21_mult_number(&A, number, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(result.rows, rows);
    ck_assert_int_eq(result.columns, columns);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert_double_eq_tol(result.matrix[i][j], C.matrix[i][j], 1.0e-7);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = -1;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_mult_number(&A, 0.5, &B);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_02) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 1;
  A.columns = -199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_mult_number(&A, 0.5, &B);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_03) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = NULL;
  B.rows = 5;
  B.columns = -199;
  B.matrix = tmppp;
  ret = s21_mult_number(&A, 0.5, &B);
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *test_mult_number(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_mult_number");
  tc = tcase_create("s21_mult_number");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, error_test_01);
    tcase_add_test(tc, error_test_02);
    tcase_add_test(tc, error_test_03);
    suite_add_tcase(s, tc);
  }

  return (s);
}
