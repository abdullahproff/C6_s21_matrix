#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (s21_isNotCorrect(*A)) return INCORRECT_MATRIX;

  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;

  double det = 0;
  s21_determinant(A, &det);
  if (A->columns != A->rows || det == 0) return CALCULATION_ERROR;

  s21_calc_complements(A, result);

  matrix_t trans;
  s21_transpose(result, &trans);
  s21_remove_matrix(result);
  s21_mult_number(&trans, 1 / det, result);
  s21_remove_matrix(&trans);

  return OK;
}