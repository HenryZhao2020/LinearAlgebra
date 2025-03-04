#include "matrix.h"
#include "real.h"

#include <stdio.h>
#include <assert.h>

const int max_height = 100;
const int max_width = 100;
const int max_table_size = max_height * max_width;

bool is_mat_valid(const struct matrix *A) {
  return A && 
         (A->height >= 0 && A->height <= max_height) &&
         (A->width >= 0 && A->width <= max_width);
}

bool is_mat_zero(const struct matrix *A) {
  assert(is_mat_valid(A));

  for (int i = 0; i < A->height * A->width; ++i) {
    if (A->table[i] != 0) {
      return false;
    }
  }
  return true;
}

void print_mat(const struct matrix *A) {
  assert(is_mat_valid(A));

  int max_len = 0;
  for (int i = 0; i < A->height * A->width; ++i) {
    int len = numlen(A->table[i]);
    if (len > max_len) {
      max_len = len;
    }
  }

  for (int r = 0; r < A->height; ++r) {
    printf("| ");
    for (int c = 0; c < A->width; ++c) {
      int i = r * A->width + c;
      int space = max_len - numlen(A->table[i]);
      for (int j = 0; j < space / 2; ++j) {
        printf(" ");
      }
      printf("%d", A->table[i]);
      for (int j = space / 2; j <= space; ++j) {
        printf(" ");
      }
    }
    printf("|\n");
  }
}

bool equal_mat(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));

  if (A->width != B->width || A->height != B->height) {
    return false;
  }

  for (int i = 0; i < A->width * A->height; ++i) {
    if (A->table[i] != B->table[i]) {
      return false;
    }
  }
  return true;
}

struct matrix mat_mult(const struct matrix *A, const struct matrix *B) {
  assert(is_mat_valid(A));
  assert(is_mat_valid(B));
  assert(A->width == B->height);

  struct matrix prod = {A->height, B->width, {0}};
  for (int r = 0; r < A->height; ++r) {
    for (int c = 0; c < B->width; ++c) {
      int sum = 0;
      for (int k = 0; k < A->width; ++k) {
        int Ak = r * A->width + k;
        int Bk = k * B->width + c;
        sum += A->table[Ak] * B->table[Bk];
      }
      prod.table[r * B->width + c] = sum;
    }
  }

  return prod;
}
