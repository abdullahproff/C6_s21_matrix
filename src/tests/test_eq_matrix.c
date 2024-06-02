#include <check.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A;
  matrix_t B;
  double tmp;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &A);
  ret += s21_create_matrix(rows, columns, &B);
  if (ret == 0) {
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        A.matrix[i][j] = tmp;
        B.matrix[i][j] = tmp;
        tmp += 0.33;
      }
    }
    ret = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(ret, 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}
END_TEST

START_TEST(test_02) {
  matrix_t A;
  matrix_t B;
  double tmp;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &A);
  ret += s21_create_matrix(rows, columns, &B);
  if (ret == 0) {
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        A.matrix[i][j] = tmp;
        B.matrix[i][j] = tmp;
        tmp += 0.33;
      }
    }
    B.matrix[101][345] += 1.0e-7;
    ret = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(ret, 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}
END_TEST

START_TEST(test_03) {
  matrix_t A;
  matrix_t B;
  double tmp;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &A);
  ret += s21_create_matrix(rows, columns, &B);
  if (ret == 0) {
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        A.matrix[i][j] = tmp;
        B.matrix[i][j] = tmp;
        tmp += 0.33;
      }
    }
    A.matrix[5][10] *= -1;
    B.matrix[5][10] *= -1;
    A.matrix[5][10] -= -1.0e-7;
    ret = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(ret, 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, B;

  s21_create_matrix(10, 11, &A);
  s21_create_matrix(10, 12, &B);
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(error_test_02) {
  int ret;
  matrix_t A, B;

  s21_create_matrix(9, 12, &A);
  s21_create_matrix(10, 12, &B);
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
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
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  B.matrix = NULL;
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(error_test_04) {
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
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(error_test_05) {
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
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(error_test_06) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  A.matrix = NULL;
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(error_test_07) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = -5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(error_test_08) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = -199;
  B.matrix = tmppp;
  ret = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(ret, 0);
}
END_TEST

Suite *test_eq_matrix(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_eq_matrix");
  tc = tcase_create("s21_eq_matrix");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, test_02);
    tcase_add_test(tc, test_03);
    tcase_add_test(tc, error_test_01);
    tcase_add_test(tc, error_test_02);
    tcase_add_test(tc, error_test_03);
    tcase_add_test(tc, error_test_04);
    tcase_add_test(tc, error_test_05);
    tcase_add_test(tc, error_test_06);
    tcase_add_test(tc, error_test_07);
    tcase_add_test(tc, error_test_08);
    suite_add_tcase(s, tc);
  }

  return (s);
}
