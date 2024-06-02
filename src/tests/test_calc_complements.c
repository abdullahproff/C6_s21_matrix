#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t A, B, C;
  double a[3][3] = {{1., 2., 3.}, {0., 4., 2.}, {5., 2., 1.}};
  double b[3][3] = {{0., 10., -20.}, {4., -14., 8.}, {-8., -2., 4.}};
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
    ret = s21_calc_complements(&A, &C);
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

START_TEST(test_02) {
  double a[4][4] = {{4., 5., 9., 8.},
                    {
                        4.,
                        1.,
                        2.,
                        3.,
                    },
                    {8., 7., 15., 4.},
                    {7., 6., 4., 9}};
  double b[4][4] = {{-145., -169., 109., 177.},
                    {252., -504., 72., 108.},
                    {47., 95., 25., -111.},
                    {24., 276., -132., -36.}};
  matrix_t A, C;
  int ret;

  ret = s21_create_matrix(4, 4, &A);
  if (ret == 0) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    ret = s21_calc_complements(&A, &C);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(C.rows, 4);
    ck_assert_int_eq(C.rows, 4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        ck_assert_double_eq_tol(b[i][j], C.matrix[i][j], 1.0e-7);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(test_03) {
  double a[2][2] = {{15.87, 78.98}, {47.25, -45.478}};
  double b[2][2] = {{-45.478, -47.25}, {-78.98, 15.87}};
  matrix_t A, C;
  int ret;

  ret = s21_create_matrix(2, 2, &A);
  if (ret == 0) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    ret = s21_calc_complements(&A, &C);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(C.rows, 2);
    ck_assert_int_eq(C.rows, 2);
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        ck_assert_double_eq_tol(b[i][j], C.matrix[i][j], 1.0e-7);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(test_04) {
  double a[5][5] = {{
                        78.,
                        951.,
                        147.,
                        47.,
                        52.,
                    },
                    {
                        76.,
                        98.,
                        78.,
                        753.,
                        -89.,
                    },
                    {
                        87.,
                        457.,
                        253.,
                        984.,
                        -71.,
                    },
                    {
                        47.,
                        453.,
                        786.,
                        123.,
                        357.,
                    },
                    {765., -896., 783., 478., 456}};
  double b[5][5] = {
      {
          892211883.,
          -9088259207.,
          44376427597.,
          -13166556043.,
          -81751647719.,
      },
      {
          97617917421.,
          -13672761316.,
          251606522691.,
          -104032036661.,
          -513616435766.,
      },
      {
          -71997449493.,
          10510919457.,
          -193843105045.,
          72992451018.,
          397773228858.,
      },
      {
          25486500814.,
          -1504267981.,
          29580687324.,
          -14989913303.,
          -80792756249.,
      },
      {-12212500158., 1182045334., -9293332343., 4297527901., 19088191207}};
  matrix_t A, C;
  char buf1[128], buf2[128];
  int ret;

  ret = s21_create_matrix(5, 5, &A);
  if (ret == 0) {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        A.matrix[i][j] = a[i][j];
      }
    }
    ret = s21_calc_complements(&A, &C);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(C.rows, 5);
    ck_assert_int_eq(C.rows, 5);
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        sprintf(buf1, "%e", b[i][j]);
        sprintf(buf2, "%e", C.matrix[i][j]);
        ck_assert_str_eq(buf1, buf2);
      }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(test_05) {
  double a[1][1] = {{26}};
  double b[1][1] = {{1}};
  matrix_t A, C;
  int ret;

  ret = s21_create_matrix(1, 1, &A);
  if (ret == 0) {
    A.matrix[0][0] = a[0][0];

    ret = s21_calc_complements(&A, &C);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(C.rows, 1);
    ck_assert_int_eq(C.rows, 1);
    ck_assert_double_eq_tol(b[0][0], C.matrix[0][0], 1.0e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(error_test_01) {
  int ret;
  matrix_t A, B;

  A.rows = 20;
  A.columns = 199;
  A.matrix = NULL;
  ret = s21_calc_complements(&A, &B);
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
  ret = s21_calc_complements(&A, &B);
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
  ret = s21_calc_complements(&A, &B);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test_04) {
  int ret;
  matrix_t A, B;
  double tmp = 0.0;
  double *tmpp = &tmp;
  double **tmppp = &tmpp;

  A.rows = 5;
  A.columns = 199;
  A.matrix = tmppp;
  ret = s21_calc_complements(&A, &B);
  ck_assert_int_eq(ret, 2);
}
END_TEST

Suite *test_calc_complements(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_calc_complements");
  tc = tcase_create("s21_calc_complements");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, test_02);
    tcase_add_test(tc, test_03);
    tcase_add_test(tc, test_04);
    tcase_add_test(tc, test_05);
    tcase_add_test(tc, error_test_01);
    tcase_add_test(tc, error_test_02);
    tcase_add_test(tc, error_test_03);
    tcase_add_test(tc, error_test_04);
    suite_add_tcase(s, tc);
  }

  return (s);
}
