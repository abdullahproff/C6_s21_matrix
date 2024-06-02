#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A, B, C;
  double a[3][3] = {{2., 5., 7.}, {6., 3., 4.}, {5., -2., -3.}};
  double b[3][3] = {{1., -1., 1.}, {-38., 41., -34.}, {27., -29., 24.}};
  int ret;

  ret = s21_create_matrix(3, 3, &A);
  ret += s21_create_matrix(3, 3, &B);
  if (ret == 0) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        A.matrix[i][j] = a[i][j];
        B.matrix[i][j] = b[i][j];
      }
    }
    ret = s21_inverse_matrix(&A, &C);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(C.rows, 3);
    ck_assert_int_eq(C.columns, 3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        ck_assert_double_eq_tol(C.matrix[i][j], B.matrix[i][j], 1.0e-7);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, res;

  A.rows = 20;
  A.columns = 199;
  A.matrix = NULL;
  ret = s21_inverse_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_02) {
  int ret;
  matrix_t A, res;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 1;
  A.columns = -199;
  A.matrix = tmppp;
  ret = s21_inverse_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_03) {
  int ret;
  matrix_t A, res;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = -5;
  A.columns = 199;
  A.matrix = tmppp;
  ret = s21_inverse_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_04) {
  int ret;
  matrix_t A, res;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  ret = s21_inverse_matrix(&A, &res);
  ck_assert_int_eq(ret, 2);
}
END_TEST

START_TEST(error_test_05) {
  matrix_t A, C;
  double a[2][2] = {{1, 2}, {2, 4}};
  int ret;

  ret = s21_create_matrix(2, 2, &A);
  if (ret == 0) {
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j) A.matrix[i][j] = a[i][j];

    ret = s21_inverse_matrix(&A, &C);
    ck_assert_int_eq(ret, 2);
    ck_assert_int_eq(C.rows, 0);
    ck_assert_int_eq(C.columns, 0);

    s21_remove_matrix(&A);
  }
}
END_TEST

Suite *test_inverse_matrix(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_inverse_matrix");
  tc = tcase_create("s21_inverse_matrix");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);

    tcase_add_test(tc, error_test_01);
    tcase_add_test(tc, error_test_02);
    tcase_add_test(tc, error_test_03);
    tcase_add_test(tc, error_test_04);
    tcase_add_test(tc, error_test_05);
    suite_add_tcase(s, tc);
  }

  return (s);
}
