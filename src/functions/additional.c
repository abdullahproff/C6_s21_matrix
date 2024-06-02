#include "s21_matrix.h"

int s21_isNotCorrect(matrix_t A) {
  int res = 1;
  if (A.rows > 0 && A.columns > 0 && A.matrix) res = 0;
  return res;
}

matrix_t s21_matrixCutCopy(matrix_t A, int row, int column) {
  matrix_t result;
  s21_create_matrix(A.rows - 1, A.columns - 1, &result);

  int i_new = 0;
  int j_new = 0;

  for (int i = 0; i < A.rows; i++) {
    if (i == row) continue;
    j_new = 0;
    for (int j = 0; j < A.columns; j++) {
      if (j == column) continue;
      result.matrix[i_new][j_new++] = A.matrix[i][j];
    }
    i_new++;
  }

  return result;
}
