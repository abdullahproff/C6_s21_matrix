#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include <check.h>

Suite *test_create_and_remove_matrix(void);
Suite *test_eq_matrix(void);
Suite *test_sum_matrix(void);
Suite *test_sub_matrix(void);
Suite *test_mult_number(void);
Suite *test_mult_matrix(void);
Suite *test_transpose(void);
Suite *test_calc_complements(void);
Suite *test_determinant(void);
Suite *test_inverse_matrix(void);

#endif
