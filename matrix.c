#include "matrix.h"
#include "vector.h"
#include "real.h"
#include "printer.h"

#include <stdio.h>
#include <assert.h>

const int max_rows = 100;
const int max_cols = 100;
const int max_table_len = max_rows * max_cols;

bool is_mat_valid(const struct matrix *A) {
  return A && 
         (A->num_rows >= 0 && A->num_rows <= max_rows) &&
         (A->num_cols >= 0 && A->num_cols <= max_cols);
}

bool is_mat_zero(const struct matrix *A) {
  assert(is_mat_valid(A));

  for (int i = 0; i < A->num_rows * A->num_cols; ++i) {
    if (A->table[i] != 0) {
      return false;
    }
  }
  return true;
}

void print_mat(const struct matrix *A, const bool tab) {
  assert(is_mat_valid(A));

  int lens[10000] = {0};
  const int max_len = maxlen(A->table, lens, max_table_len);

  for (int r = 0; r < A->num_rows; ++r) {
    if (tab) {
      printf("\t");
    }

    printf("| ");
    for (int c = 0; c < A->num_cols; ++c) {
      const int i = r * A->num_cols + c;
      const int space = max_len - lens[i];
      print_space(space / 2);
      print_real(A->table[i]);
      print_space(space / 2 + (space % 2));
    }
    printf("|\n");
  }
}

bool equal_mat(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));

  if (A->num_cols != B->num_cols || A->num_rows != B->num_rows) {
    return false;
  }

  const int len = A->num_rows * A->num_cols;
  for (int i = 0; i < len; ++i) {
    if (A->table[i] != B->table[i]) {
      return false;
    }
  }
  return true;
}

struct matrix mat_add(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));
  assert(A->num_rows == B->num_rows);
  assert(A->num_cols == B->num_cols);

  struct matrix sum = {A->num_rows, A->num_cols, {0}};
  const int len = A->num_rows * A->num_cols;
  for (int i = 0; i < len; ++i) {
    sum.table[i] = A->table[i] + B->table[i];
  }
  return sum;
}

struct matrix mat_smult(const struct matrix *A, const double c) {
  assert(is_mat_valid(A));

  struct matrix prod = {A->num_rows, A->num_cols, {0}};
  const int len = A->num_rows * A->num_cols;
  for (int i = 0; i < len; ++i) {
    prod.table[i] = c * A->table[i];
  }
  return prod;
}

struct matrix mat_vec_mult(const struct matrix *A, const struct vector *v) {
  assert(is_mat_valid(A));
  assert(is_vec_valid(v));
  assert(A->num_cols == v->n);

  struct matrix v_mat = {v->n, 1, {0}};
  for (int i = 0; i < v->n; ++i) {
    v_mat.table[i] = v->comp[i];
  }

  return mat_mult(A, &v_mat);
}

struct matrix mat_mult(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));
  assert(A->num_cols == B->num_rows);

  struct matrix prod = {A->num_rows, B->num_cols, {0}};
  for (int r = 0; r < A->num_rows; ++r) {
    for (int c = 0; c < B->num_cols; ++c) {
      int sum = 0;
      for (int k = 0; k < A->num_cols; ++k) {
        const int Ak = r * A->num_cols + k;
        const int Bk = k * B->num_cols + c;
        sum += A->table[Ak] * B->table[Bk];
      }
      prod.table[r * B->num_cols + c] = sum;
    }
  }
  return prod;
}
