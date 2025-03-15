#include "matrix.h"
#include "vector.h"
#include "real.h"
#include "printer.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

const int max_mat_m = 100;
const int max_mat_n = 100;
const int max_mat_len = 10000;
const char *default_mat_name = "A";

bool is_mat_valid(const struct matrix *A) {
  return A && 
         (A->m >= 0 && A->m <= max_mat_m) &&
         (A->n >= 0 && A->n <= max_mat_n);
}

bool is_mat_zero(const struct matrix *A) {
  assert(is_mat_valid(A));

  for (int i = 0; i < A->m * A->n; ++i) {
    if (A->entries[i] != 0) {
      return false;
    }
  }
  return true;
}

void print_mat(const struct matrix *A) {
  assert(is_mat_valid(A));

  int lens[10000] = {0};
  const int max_len = maxlen(A->entries, lens, max_mat_len);

  for (int i = 0; i < A->m; ++i) {
    printf("| ");
    for (int j = 0; j < A->n; ++j) {
      const int index = i * A->n + j;
      const int space = max_len - lens[index];
      print_space(space / 2);
      print_real(A->entries[index]);
      print_space(space / 2 + (space % 2) + 1);
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
    if (A->entries[i] != B->entries[i]) {
      return false;
    }
  }
  return true;
}

double mat_entry(const struct matrix *A, const int r, const int c) {
  assert(is_mat_valid(A));
  assert(r > 0 && r <= A->m);
  assert(c > 0 && c <= A->n);

  const int index = (r - 1) * A->n + (c - 1);
  return A->entries[index];
}

void set_mat_entry(struct matrix *A, const double val, 
                   const int r, const int c) {
  assert(is_mat_valid(A));
  assert(r > 0 && r <= A->m);
  assert(c > 0 && c <= A->n);

  const int index = (r - 1) * A->n + (c - 1);
  A->entries[index] = val;
}

struct matrix mat_add(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));
  assert(A->m == B->m);
  assert(A->n == B->n);

  struct matrix sum = {A->m, A->n, {0}, default_mat_name};
  const int len = A->m * A->n;
  for (int i = 0; i < len; ++i) {
    sum.entries[i] = A->entries[i] + B->entries[i];
  }
  return sum;
}

struct matrix mat_smult(const struct matrix *A, const double c) {
  assert(is_mat_valid(A));

  struct matrix prod = {A->m, A->n, {0}, default_mat_name};
  const int len = A->m * A->n;
  for (int i = 0; i < len; ++i) {
    prod.entries[i] = c * A->entries[i];
  }
  return prod;
}

struct matrix mat_vec_mult(const struct matrix *A, const struct vector *v) {
  assert(is_mat_valid(A));
  assert(is_vec_valid(v));
  assert(A->n == v->n);

  struct matrix v_mat = {v->n, 1, {0}, default_mat_name};
  for (int i = 0; i < v->n; ++i) {
    v_mat.entries[i] = v->comp[i];
  }

  return mat_mult(A, &v_mat);
}

struct matrix mat_mult(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));
  assert(A->n == B->m);

  struct matrix prod = {A->m, B->n, {0}, default_mat_name};
  for (int i = 0; i < A->m; ++i) {
    for (int j = 0; j < B->n; ++j) {
      int sum = 0;
      for (int k = 0; k < A->n; ++k) {
        const int A_ik = i * A->n + k;
        const int B_kj = k * B->n + j;
        sum += A->entries[A_ik] * B->entries[B_kj];
      }
      prod.entries[i * B->n + j] = sum;
    }
  }
  return prod;
}

struct matrix mat_transpose(const struct matrix *A) {
  assert(A);

  char At_name[101] = {0};
  strcpy(At_name, A->name);
  strcat(At_name, "_T");

  struct matrix At = {A->m, A->n, {0}, At_name};
  for (int i = 0; i < A->m; ++i) {
    for (int j = 0; j < A->n; ++j) {
      const int A_ij = mat_entry(A, i, j);
      const int A_ji = mat_entry(A, j, i);
      set_mat_entry(&At, A_ji, i, j);
      set_mat_entry(&At, A_ij, j, i);
    }
  }

  return At;
}

struct matrix mat_identity(const int n) {
  assert(n >= 0);

  struct matrix I = {n, n, {0}, default_mat_name};
  for (int i = 1; i <= n; ++i) {
    set_mat_entry(&I, 1, i, i);
  }
  return I;
}
