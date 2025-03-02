#include "vector.h"
#include "real.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

const int max_n = 100;

bool is_vec_valid(const struct vector *v) {
  return v && 
         (v->n >= 0 && v->n <= max_n);
}

bool is_vec_zero(const struct vector *v) {
  assert(is_vec_valid(v));

  for (int i = 0; i < v->n; ++i) {
    if (v->comp[i] != 0) {
      return false;
    }
  }
  return true;
}

int print_vec(const struct vector *v, bool tab) {
  assert(is_vec_valid(v));

  int max_len = 0;
  for (int i = 0; i < v->n; ++i) {
    int len = numlen(v->comp[i]);
    if (len > max_len) {
      max_len = len;
    }
  }

  for (int i = 0; i < v->n; ++i) {
    if (tab) {
      printf("\t");
    }

    int space = max_len - numlen(v->comp[i]);
    printf("|");
    for (int j = 0; j < space / 2; ++j) {
      printf(" ");
    }
    printf("%g", v->comp[i]);
    for (int j = space / 2; j < space; ++j) {
      printf(" ");
    }
    printf("|\n");
  }

  return max_len;
}

bool equal_vec(const struct vector *u, const struct vector *v) {
  assert(is_vec_valid(u));
  assert(is_vec_valid(v));

  if (u->n != v->n) {
    return false;
  }

  for (int i = 0; i < u->n; ++i) {
    if (u->comp[i] != v->comp[i]) {
      return false;
    }
  }
  return true;
}

double vec_at(const struct vector *v, int i) {
  assert(is_vec_valid(v));
  assert(i >= 1 && i <= v->n);

  return v->comp[i - 1];
}

struct vector vec_add(const struct vector *u, const struct vector *v) {
  assert(is_vec_valid(u));
  assert(is_vec_valid(v));
  assert(u->n == v->n);

  struct vector sum = {u->n, {0}};
  for (int i = 0; i < u->n; ++i) {
    sum.comp[i] = u->comp[i] + v->comp[i];
    // Avoid printing -0 instead of 0
    if (sum.comp[i] == -0.0) {
      sum.comp[i] = 0;
    }
  }
  return sum;
}

struct vector vec_scalar_mult(const struct vector *v, double c) {
  assert(is_vec_valid(v));

  struct vector prod = {v->n, {0}};
  for (int i = 0; i < prod.n; ++i) {
    prod.comp[i] = c * v->comp[i];
    // Avoid printing -0 instead of 0
    if (prod.comp[i] == -0.0) {
      prod.comp[i] = 0;
    }
  }
  return prod;
}

double dot_product(const struct vector *u, const struct vector *v) {
  assert(is_vec_valid(u));
  assert(is_vec_valid(v));
  assert(u->n == v->n);

  double dp = 0;
  for (int i = 0; i < u->n; ++i) {
    dp += u->comp[i] * v->comp[i];
  }
  return dp;
}

struct vector cross_product(const struct vector *u, const struct vector *v) {
  assert(is_vec_valid(u));
  assert(is_vec_valid(v));
  assert(u->n == 3 && v->n == 3);

  struct vector cp = {3, {
    vec_at(u, 2) * vec_at(v, 3) - vec_at(u, 3) * vec_at(v, 2),
    vec_at(u, 3) * vec_at(v, 1) - vec_at(u, 1) * vec_at(v, 3),
    vec_at(u, 1) * vec_at(v, 2) - vec_at(u, 2) * vec_at(v, 1),
  }};
  return cp;
}

double vec_len(const struct vector *v) {
  assert(is_vec_valid(v));

  return sqrt(dot_product(v, v));
}

double vec_angle(const struct vector *u, const struct vector *v) {
  assert(is_vec_valid(u) && !is_vec_zero(u));
  assert(is_vec_valid(v) && !is_vec_zero(v));
  assert(u->n == v->n);

  return acos(dot_product(u, v) / (vec_len(u) * vec_len(v)));
}
