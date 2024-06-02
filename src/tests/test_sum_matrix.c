#include <check.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t result;
  double tmp1, tmp2;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &A);
  ret += s21_create_matrix(rows, columns, &B);
  ret += s21_create_matrix(rows, columns, &C);
  if (ret == 0) {
    tmp1 = 1.0;
    tmp2 = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        A.matrix[i][j] = tmp1;
        B.matrix[i][j] = tmp2;
        C.matrix[i][j] = tmp1 + tmp2;
        tmp1 += 0.33;
        tmp1 += 0.444;
      }
    }
    ret = s21_sum_matrix(&A, &B, &result);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert_double_eq_tol(result.matrix[i][j], C.matrix[i][j], 1.0e-7);
      }
    }
    ck_assert_int_eq(ret, 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, B, result;

  s21_create_matrix(10, 11, &A);
  s21_create_matrix(10, 12, &B);
  ret = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(error_test_02) {
  int ret;
  matrix_t A, B, C;

  s21_create_matrix(9, 12, &A);
  s21_create_matrix(10, 12, &B);
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(error_test_03) {
  int ret;
  matrix_t A, B, C;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  B.matrix = NULL;
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_04) {
  int ret;
  matrix_t A, B, C;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = -1;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_05) {
  int ret;
  matrix_t A, B, C;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 1;
  A.columns = -199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_06) {
  int ret;
  matrix_t A, B, C;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = 199;
  A.matrix = NULL;
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_07) {
  int ret;
  matrix_t A, B, C;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = -5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_08) {
  int ret;
  matrix_t A, B, C;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  B.rows = 5;
  B.columns = -199;
  B.matrix = tmppp;
  ret = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *test_sum_matrix(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sum_matrix");
  tc = tcase_create("s21_sum_matrix");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
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
