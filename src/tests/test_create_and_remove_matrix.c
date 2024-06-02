#include <check.h>

#include "s21_matrix.h"

START_TEST(test_01) {
  matrix_t m;
  double tmp;
  int ret;

  for (int rows = 1; rows < 25; ++rows) {
    for (int columns = 1; columns < 25; ++columns) {
      ret = s21_create_matrix(rows, columns, &m);
      tmp = 1.0;
      if (ret == 0) {
        ck_assert_int_eq(rows, m.rows);
        ck_assert_int_eq(columns, m.columns);
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < columns; ++j) {
            m.matrix[i][j] = tmp;
            tmp += 0.33;
          }
        }
        tmp = 1.0;
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < columns; ++j) {
            ck_assert_double_eq(tmp, m.matrix[i][j]);
            tmp += 0.33;
          }
        }
      }
      s21_remove_matrix(&m);
      ck_assert_ptr_null(m.matrix);
      ck_assert_int_eq(m.rows, 0);
      ck_assert_int_eq(m.columns, 0);
    }
  }
}
END_TEST

START_TEST(test_02) {
  matrix_t m;
  double tmp;
  int rows = 137;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &m);
  if (ret == 0) {
    ck_assert_int_eq(rows, m.rows);
    ck_assert_int_eq(columns, m.columns);
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        m.matrix[i][j] = tmp;
        tmp += 0.33;
      }
    }
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert_double_eq(tmp, m.matrix[i][j]);
        tmp += 0.33;
      }
    }
    s21_remove_matrix(&m);
    ck_assert_ptr_null(m.matrix);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
  }
}
END_TEST

START_TEST(test_03) {
  matrix_t m;
  double tmp;
  int rows = 555;
  int columns = 128;
  int ret;

  ret = s21_create_matrix(rows, columns, &m);
  if (ret == 0) {
    ck_assert_int_eq(rows, m.rows);
    ck_assert_int_eq(columns, m.columns);
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        m.matrix[i][j] = tmp;
        tmp += 0.33;
      }
    }
    tmp = 1.0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert_double_eq(tmp, m.matrix[i][j]);
        tmp += 0.33;
      }
    }
    s21_remove_matrix(&m);
    ck_assert_ptr_null(m.matrix);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
  }
}
END_TEST

START_TEST(test_04) {
  matrix_t m;
  int rows = 2568;
  int columns = 777;
  int ret;

  ret = s21_create_matrix(rows, columns, &m);
  if (ret == 0) {
    ck_assert_int_eq(rows, m.rows);
    ck_assert_int_eq(columns, m.columns);
    m.matrix[666][123] = -17.8;
    ck_assert_double_eq(-17.8, m.matrix[666][123]);
    s21_remove_matrix(&m);
    ck_assert_ptr_null(m.matrix);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
  }
}
END_TEST

START_TEST(test_05) {
  matrix_t m;
  int rows = 11;
  int columns = 13;
  int ret;

  ret = s21_create_matrix(rows, columns, &m);
  if (ret == 0) {
    ck_assert_int_eq(rows, m.rows);
    ck_assert_int_eq(columns, m.columns);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert_double_eq(m.matrix[i][j], 0.0);
      }
    }
    s21_remove_matrix(&m);
    ck_assert_ptr_null(m.matrix);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
  }
}
END_TEST

START_TEST(error_test) {
  int ret;
  matrix_t m;

  ret = s21_create_matrix(10, 0, &m);
  ck_assert_int_eq(ret, 1);
  ret = s21_create_matrix(10, -9, &m);
  ck_assert_int_eq(ret, 1);
  ret = s21_create_matrix(0, 9, &m);
  ck_assert_int_eq(ret, 1);
  ret = s21_create_matrix(-3, 9, &m);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(error_test2) {
  matrix_t m;
  m.matrix = NULL;
  m.rows = -3;
  m.columns = 4;
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(error_test3) { s21_remove_matrix(NULL); }
END_TEST

Suite *test_create_and_remove_matrix(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_create_and_remove_matrix");
  tc = tcase_create("s21_create_and_remove_matrix");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_01);
    tcase_add_test(tc, test_02);
    tcase_add_test(tc, test_03);
    tcase_add_test(tc, test_04);
    tcase_add_test(tc, test_05);
    tcase_add_test(tc, error_test);
    tcase_add_test(tc, error_test2);
    tcase_add_test(tc, error_test3);
    suite_add_tcase(s, tc);
  }

  return (s);
}
