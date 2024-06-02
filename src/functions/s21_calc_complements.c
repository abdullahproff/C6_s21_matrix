#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (s21_isNotCorrect(*A)) return INCORRECT_MATRIX;

  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;

  if (A->columns != A->rows) return CALCULATION_ERROR;

  s21_create_matrix(A->rows, A->columns, result);

  if (A->rows == 1)
    result->matrix[0][0] = 1;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        matrix_t copy = s21_matrixCutCopy(*A, i, j);
        result->matrix[i][j] = pow(-1, i + j) * s21_recursiveDeterminant(copy);
        s21_remove_matrix(&copy);
      }

  return OK;
}