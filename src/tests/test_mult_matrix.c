#include <check.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  double a[3][3] = {{-1.0, 2.0, 5.0}, {3.0, 4.0, 6.0}, {-8.0, 2.0, 12.0}};
  matrix_t A;
  double b[3][3] = {{-2.0, 2.0, 19.1}, {5.0, 7.0, 17.7}, {-1.0, 4.0, -13.56}};
  ;
  matrix_t B;
  double c[3][3] = {
      {7.0, 32.0, -51.5}, {8.0, 58.0, 46.74}, {14.0, 46.0, -280.12}};
  matrix_t C;
  matrix_t result;
  int ret;

  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      A.matrix[i][j] = a[i][j];
    }
  }
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      B.matrix[i][j] = b[i][j];
    }
  }
  s21_create_matrix(3, 3, &C);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      C.matrix[i][j] = c[i][j];
    }
  }

  ret = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ck_assert_double_eq_tol(result.matrix[i][j], C.matrix[i][j], 1.0e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_02) {
  double a[3][4] = {
      {-1.0, 2.0, 5.0, 78.45}, {3.0, 4.0, 6.0, 19.01}, {-8.0, 2.0, 12.0, 0.43}};
  matrix_t A;
  double b[4][5] = {{-2.0, 2.0, 19.1, 0.5, 0.001},
                    {5.0, 7.0, 17.7, -0.9, -18.78},
                    {-1.0, 4.0, -13.56, 189.1, 19.43},
                    {18.1, 0.3, -17.1, 1983.14, 0.93}};
  matrix_t B;
  double c[3][5] = {{1426.945, 55.535, -1392.995, 156520.533, 132.5475},
                    {352.081, 63.703, -278.331, 38831.9914, 59.1423},
                    {21.783, 46.129, -287.473, 3116.1502, 195.9919}};
  matrix_t C;
  matrix_t result;
  int ret;

  s21_create_matrix(3, 4, &A);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      A.matrix[i][j] = a[i][j];
    }
  }
  s21_create_matrix(4, 5, &B);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      B.matrix[i][j] = b[i][j];
    }
  }
  s21_create_matrix(3, 5, &C);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      C.matrix[i][j] = c[i][j];
    }
  }

  ret = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 5);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      ck_assert_double_eq_tol(result.matrix[i][j], C.matrix[i][j], 1.0e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, B, result;

  s21_create_matrix(10, 1, &A);
  s21_create_matrix(10, 12, &B);
  ret = s21_mult_matrix(&A, &B, &result);
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
  ret = s21_mult_matrix(&A, &B, &C);
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
  A.matrix = NULL;
  B.rows = 5;
  B.columns = 199;
  B.matrix = tmppp;
  ret = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_04) {
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
  ret = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_05) {
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
  ret = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_06) {
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
  ret = s21_mult_matrix(&A, &B, &C);
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
  ret = s21_mult_matrix(&A, &B, &C);
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
  ret = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *test_mult_matrix(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_mult_matrix");
  tc = tcase_create("s21_mult_matrix");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, test_02);
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
