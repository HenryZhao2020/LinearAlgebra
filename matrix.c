#include "matrix.h"
#include "real.h"
#include "printer.h"

#include <stdio.h>
#include <assert.h>

const int max_height = 100;
const int max_width = 100;
const int max_table_len = max_height * max_width;

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

void print_mat(const struct matrix *A, const bool tab) {
  assert(is_mat_valid(A));

  int lens[10000] = {0};
  const int max_len = maxlen(A->table, lens, max_table_len);

  for (int r = 0; r < A->height; ++r) {
    if (tab) {
      printf("\t");
    }

    printf("| ");
    for (int c = 0; c < A->width; ++c) {
      const int i = r * A->width + c;
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
        const int Ak = r * A->width + k;
        const int Bk = k * B->width + c;
        sum += A->table[Ak] * B->table[Bk];
      }
      prod.table[r * B->width + c] = sum;
    }
  }

  return prod;
}
