#include "vector.h"

#include <stdio.h>
#include <assert.h>

const int min_n = 0;
const int max_n = 100;

bool is_vec_valid(const struct vector *vec) {
  return vec && 
         (vec->n >= min_n && vec->n <= max_n);
}

int print_vec(const struct vector *vec) {
  assert(is_vec_valid(vec));

  int num_lens[100] = {0};
  int max_len = 0;
  for (int i = 0; i < vec->n; ++i) {
    num_lens[i] = snprintf(NULL, 0, "%d", vec->comp[i]);
    if (num_lens[i] > max_len) {
      max_len = num_lens[i];
    }
  }

  for (int i = 0; i < vec->n; ++i) {
    int space = max_len - num_lens[i];
    printf("|");
    for (int j = 0; j < space / 2; ++j) printf(" ");
    printf("%d", vec->comp[i]);
    for (int j = space / 2; j < space; ++j) printf(" ");
    printf("|\n");
  }

  return max_len;
}

bool equal_vec(const struct vector *v1, const struct vector *v2) {
  assert(is_vec_valid(v1));
  assert(is_vec_valid(v2));

  if (v1->n != v2->n) {
    return false;
  }

  for (int i = 0; i < v1->n; ++i) {
    if (v1->comp[i] != v2->comp[i]) {
      return false;
    }
  }
  return true;
}

int vec_at(const struct vector *vec, int i) {
  assert(is_vec_valid(vec));
  assert(i >= 0 && i <= vec->n);

  return vec->comp[i];
}

struct vector vec_add(const struct vector *v1, const struct vector *v2) {
  assert(is_vec_valid(v1));
  assert(is_vec_valid(v2));
  assert(v1->n == v2->n);

  struct vector sum = *v1;
  for (int i = 0; i < sum.n; ++i) {
    sum.comp[i] += v2->comp[i];
  }
  return sum;
}

struct vector vec_scalar_mult(const struct vector *vec, int c) {
  assert(is_vec_valid(vec));

  struct vector prod = *vec;
  for (int i = 0; i < prod.n; ++i) {
    prod.comp[i] *= c;
  }
  return prod;
}
