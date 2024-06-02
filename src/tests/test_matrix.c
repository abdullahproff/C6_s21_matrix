#include "test_matrix.h"

#include <stdlib.h>

static int run_test_suite(Suite *test_suite) {
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = srunner_create(test_suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed);
}

int main(void) {
  int number_failed = 0;
  Suite *suite_array[] = {test_create_and_remove_matrix(),
                          test_eq_matrix(),
                          test_sum_matrix(),
                          test_sub_matrix(),
                          test_mult_number(),
                          test_mult_matrix(),
                          test_transpose(),
                          test_determinant(),
                          test_calc_complements(),
                          test_inverse_matrix(),
                          NULL};

  for (size_t i = 0; suite_array[i]; ++i) {
    number_failed += run_test_suite(suite_array[i]);
  }

  return (number_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
