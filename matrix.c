#include "matrix.h"

#include <stdio.h>
#include <assert.h>

const int max_rows = 100;
const int max_cols = 100;
const int max_table_size = 10000;

bool is_matrix_valid(const struct matrix *mat) {
  return mat && 
         (mat->rows >= 0 && mat->rows <= max_rows) &&
         (mat->cols >= 0 && mat->cols <= max_cols);
}

void print_matrix(const struct matrix *mat) {
  assert(is_matrix_valid(mat));

  for (int r = 0; r < mat->rows; ++r) {
    printf("|\t");
    for (int c = 0; c < mat->cols; ++c) {
      int index = r * mat->cols + c;
      printf("%d\t", mat->table[index]);
    }
    printf("|\n");
  }
}

bool equal_matrix(const struct matrix *m1, const struct matrix *m2) {
  assert(is_matrix_valid(m1));
  assert(is_matrix_valid(m2));

  if (m1->rows * m1->cols != m2->rows * m2->cols) {
    return false;
  }

  for (int i = 0; i < m1->rows * m1->cols; ++i) {
    if (m1->table[i] != m2->table[i]) {
      return false;
    }
  }
  return true;
}
