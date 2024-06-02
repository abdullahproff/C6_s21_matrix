#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  double tmp;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &A);
  ret += s21_create_matrix(columns, rows, &B);
  if (ret == 0) {
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        A.matrix[i][j] = tmp;
        B.matrix[j][i] = tmp;
        tmp += 0.444;
      }
    }
    ret = s21_transpose(&A, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(result.rows, B.rows);
    ck_assert_int_eq(result.columns, B.columns);
    rows = B.rows;
    columns = B.columns;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert_double_eq_tol(result.matrix[i][j], B.matrix[i][j], 1.0e-7);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_02) {
  double a[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  double b[2][3] = {{1, 3, 5}, {2, 4, 6}};
  matrix_t A, B, result;
  int ret;

  ret = s21_create_matrix(3, 2, &A);
  ret += s21_create_matrix(2, 3, &B);
  if (ret == 0) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 2; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 3; ++j) {
        B.matrix[i][j] = b[i][j];
      }
    }
    ret = s21_transpose(&A, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(result.rows, B.rows);
    ck_assert_int_eq(result.columns, B.columns);
    for (int i = 0; i < B.rows; ++i) {
      for (int j = 0; j < B.columns; ++j) {
        ck_assert_double_eq_tol(result.matrix[i][j], B.matrix[i][j], 1.0e-7);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, B;

  A.rows = 20;
  A.columns = 199;
  A.matrix = NULL;
  ret = s21_transpose(&A, &B);
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
  ret = s21_transpose(&A, &B);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_03) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = -5;
  A.columns = 199;
  A.matrix = tmppp;
  ret = s21_transpose(&A, &B);
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *test_transpose(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_transpose");
  tc = tcase_create("s21_transpose");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, test_02);
    tcase_add_test(tc, error_test_01);
    tcase_add_test(tc, error_test_02);
    tcase_add_test(tc, error_test_03);
    suite_add_tcase(s, tc);
  }

  return (s);
}
