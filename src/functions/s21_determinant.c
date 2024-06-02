#include "s21_matrix.h"

double s21_recursiveDeterminant(matrix_t A) {
  if (A.rows == 1) return A.matrix[0][0];
  if (A.rows == 2)
    return A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];

  double res = 0;
  for (int i = 0; i < A.columns; i++) {
    matrix_t copy = s21_matrixCutCopy(A, 0, i);
    res += pow(-1, i) * A.matrix[0][i] * s21_recursiveDeterminant(copy);
    s21_remove_matrix(&copy);
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  if (s21_isNotCorrect(*A)) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;

  *result = s21_recursiveDeterminant(*A);

  return OK;
}