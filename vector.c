#include "vector.h"
#include "integer.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

const int min_n = 0;
const int max_n = 100;

bool is_vec_valid(const struct vector *vec) {
  return vec && 
         (vec->n >= min_n && vec->n <= max_n);
}

int print_vec(const struct vector *vec) {
  assert(is_vec_valid(vec));

  int max_len = 0;
  for (int i = 0; i < vec->n; ++i) {
    int len = numlen(vec->comp[i]);
    if (len > max_len) {
      max_len = len;
    }
  }

  for (int i = 0; i < vec->n; ++i) {
    int space = max_len - numlen(vec->comp[i]);
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

int dot_product(const struct vector *v1, const struct vector *v2) {
  assert(is_vec_valid(v1));
  assert(is_vec_valid(v2));
  assert(v1->n == v2->n);

  int dp = 0;
  for (int i = 0; i < v1->n; ++i) {
    dp += v1->comp[i] * v2->comp[i];
  }
  return dp;
}

struct vector cross_product(const struct vector *v1, const struct vector *v2) {
  assert(is_vec_valid(v1));
  assert(is_vec_valid(v2));
  assert(v1->n == 3 && v2->n == 3);

  struct vector cp = {3, {
    vec_at(v1, 2) * vec_at(v2, 3) - vec_at(v1, 3) * vec_at(v2, 2),
    vec_at(v1, 3) * vec_at(v2, 1) - vec_at(v1, 1) * vec_at(v2, 3),
    vec_at(v1, 1) * vec_at(v2, 2) - vec_at(v1, 2) * vec_at(v2, 1),
  }};
  return cp;
}

int vec_len(const struct vector *vec) {
  assert(is_vec_valid(vec));

  return sqrt(dot_product(vec, vec));
}
