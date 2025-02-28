#include "vector.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

const int min_n = 0;
const int max_n = 100;

bool is_vec_valid(const struct vector *vec) {
  return vec && (vec->n >= min_n) && (vec->n <= max_n);
}

void print_vec(const struct vector *vec) {
  assert(is_vec_valid(vec));

  for (int i = 0; i < vec->n; ++i) {
    printf("|%d|\n", vec->comp[i]);
  }
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

struct vector vec_scalar_mult(const struct vector *vec, const int k) {
  assert(is_vec_valid(vec));

  struct vector prod = *vec;
  for (int i = 0; i < prod.n; ++i) {
    prod.comp[i] *= k;
  }
  return prod;
}
