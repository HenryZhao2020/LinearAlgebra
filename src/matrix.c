#include "matrix.h"
#include "vector.h"
#include "real.h"
#include "printer.h"

#include <stdio.h>
#include <assert.h>

const int max_mat_m = 100;
const int max_mat_n = 100;
const int max_mat_len = max_mat_m * max_mat_n;

bool is_mat_valid(const struct matrix *A) {
  return A && 
         (A->m >= 0 && A->m <= max_mat_m) &&
         (A->n >= 0 && A->n <= max_mat_n);
}

bool is_mat_zero(const struct matrix *A) {
  assert(is_mat_valid(A));

  for (int i = 0; i < A->m * A->n; ++i) {
    if (A->table[i] != 0) {
      return false;
    }
  }
  return true;
}

void print_mat(const struct matrix *A, const bool tab) {
  assert(is_mat_valid(A));

  int lens[10000] = {0};
  const int max_len = maxlen(A->table, lens, max_mat_len);

  for (int r = 0; r < A->m; ++r) {
    if (tab) {
      printf("\t");
    }

    printf("| ");
    for (int c = 0; c < A->n; ++c) {
      const int i = r * A->n + c;
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

  if (A->n != B->n || A->m != B->m) {
    return false;
  }

  const int len = A->m * A->n;
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
  assert(A->m == B->m);
  assert(A->n == B->n);

  struct matrix sum = {A->m, A->n, {0}};
  const int len = A->m * A->n;
  for (int i = 0; i < len; ++i) {
    sum.table[i] = A->table[i] + B->table[i];
  }
  return sum;
}

struct matrix mat_smult(const struct matrix *A, const double c) {
  assert(is_mat_valid(A));

  struct matrix prod = {A->m, A->n, {0}};
  const int len = A->m * A->n;
  for (int i = 0; i < len; ++i) {
    prod.table[i] = c * A->table[i];
  }
  return prod;
}

struct matrix mat_vec_mult(const struct matrix *A, const struct vector *v) {
  assert(is_mat_valid(A));
  assert(is_vec_valid(v));
  assert(A->n == v->n);

  struct matrix v_mat = {v->n, 1, {0}};
  for (int i = 0; i < v->n; ++i) {
    v_mat.table[i] = v->comp[i];
  }

  return mat_mult(A, &v_mat);
}

struct matrix mat_mult(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));
  assert(A->n == B->m);

  struct matrix prod = {A->m, B->n, {0}};
  for (int r = 0; r < A->m; ++r) {
    for (int c = 0; c < B->n; ++c) {
      int sum = 0;
      for (int k = 0; k < A->n; ++k) {
        const int Ak = r * A->n + k;
        const int Bk = k * B->n + c;
        sum += A->table[Ak] * B->table[Bk];
      }
      prod.table[r * B->n + c] = sum;
    }
  }
  return prod;
}
