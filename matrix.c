#include "matrix.h"
#include "real.h"

#include <stdio.h>
#include <assert.h>

const int max_rows = 100;
const int max_cols = 100;
const int max_table_size = max_rows * max_cols;

bool is_matrix_valid(const struct matrix *mat) {
  return mat && 
         (mat->rows >= 0 && mat->rows <= max_rows) &&
         (mat->cols >= 0 && mat->cols <= max_cols);
}

void print_matrix(const struct matrix *mat) {
  assert(is_matrix_valid(mat));

  int max_len = 0;
  for (int i = 0; i < mat->rows * mat->cols; ++i) {
    int len = numlen(mat->table[i]);
    if (len > max_len) {
      max_len = len;
    }
  }

  for (int r = 0; r < mat->rows; ++r) {
    printf("| ");
    for (int c = 0; c < mat->cols; ++c) {
      int i = r * mat->cols + c;
      int space = max_len - numlen(mat->table[i]);
      for (int j = 0; j < space / 2; ++j) {
        printf(" ");
      }
      printf("%d", mat->table[i]);
      for (int j = space / 2; j <= space; ++j) {
        printf(" ");
      }
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
