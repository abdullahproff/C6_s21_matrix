#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A;
  double a[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {5.0, 7.0, 9.0}};
  double dt = 0.0;
  double result = 100.0;
  int ret;

  ret = s21_create_matrix(3, 3, &A);
  if (ret == 0) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    ret = s21_determinant(&A, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_double_eq_tol(dt, result, 1.0e-7);
    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(test_02) {
  double a[6][6] = {{1.1, 1.2, 1.3, 1.4, 1.5, 1.6},
                    {2.8, -2.9, -2.3, -2.4, 2.5, 2.7},
                    {3.33, 3.2, -3.87, 3.99, 3.47, -3.02},
                    {4.85, 4.23, 4.32, -4.18, 4.89, 4.23},
                    {5.12, 5.32, 5.28, 5.67, -5.73, 5.91},
                    {6.15, -6.53, 6.44, 6.32, 6.78, 6.98}};
  matrix_t A;
  double dt = -77591.0 - (269266237810933.0 / 3733527061589101.0);
  double result = -1;
  int ret;

  ret = s21_create_matrix(6, 6, &A);
  if (ret == 0) {
    for (int i = 0; i < 6; ++i) {
      for (int j = 0; j < 6; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    ret = s21_determinant(&A, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_double_eq_tol(dt, result, 1.0e-7);
    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(test_03) {
  double dt = 1183.2019381738;
  matrix_t A;
  double result = -1;
  int ret;

  ret = s21_create_matrix(1, 1, &A);
  if (ret == 0) {
    A.matrix[0][0] = dt;
    ret = s21_determinant(&A, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_double_eq_tol(dt, result, 1.0e-7);
    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(test_04) {
  double a[2][2] = {{179.38, 18.91}, {2.18821, 472.9428}};
  matrix_t A;
  double dt = 84795.1004129;
  double result = -1;
  int ret;

  ret = s21_create_matrix(2, 2, &A);
  if (ret == 0) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    ret = s21_determinant(&A, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_double_eq_tol(dt, result, 1.0e-7);
    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  double res;
  matrix_t A;

  A.rows = 20;
  A.columns = 199;
  A.matrix = NULL;
  ret = s21_determinant(&A, &res);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_02) {
  int ret;
  matrix_t A;
  double res;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 1;
  A.columns = -199;
  A.matrix = tmppp;
  ret = s21_determinant(&A, &res);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_03) {
  int ret;
  matrix_t A;
  double res;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = -5;
  A.columns = 199;
  A.matrix = tmppp;
  ret = s21_determinant(&A, &res);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_04) {
  int ret;
  matrix_t A;
  double res;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  ret = s21_determinant(&A, &res);
  ck_assert_int_eq(ret, 2);
}
END_TEST

Suite *test_determinant(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_determinant");
  tc = tcase_create("s21_determinant");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, test_02);
    tcase_add_test(tc, test_03);
    tcase_add_test(tc, test_04);
    tcase_add_test(tc, error_test_01);
    tcase_add_test(tc, error_test_02);
    tcase_add_test(tc, error_test_03);
    tcase_add_test(tc, error_test_04);
    suite_add_tcase(s, tc);
  }

  return (s);
}
