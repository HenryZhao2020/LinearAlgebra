#include "proj.h"
#include "vector.h"

#include <assert.h>

// proj_assert(v1, v2) runs assertion tests to ensure that the projection
//   and perpendicular of v1 onto v2 can be computed.
void proj_assert(const struct vector *v1, const struct vector *v2) {
  assert(is_vec_valid(v1));
  assert(is_vec_valid(v2));
  assert(v1->n == v2->n);
  assert(!is_vec_zero(v2));
}

struct vector projv(const struct vector *u, const struct vector *v) {
  proj_assert(u, v);

  double len = vec_len(v);
  double coeff = (dot_product(u, v) / (len * len));

  return vec_scalar_mult(v, coeff);
}

struct vector perpv(const struct vector *u, const struct vector *v) {
  proj_assert(u, v);

  struct vector proj = projv(u, v);
  struct vector neg_proj = vec_scalar_mult(&proj, -1);

  return vec_add(u, &neg_proj);
}

struct vector projp(const struct vector *x, const struct vector *n) {
  proj_assert(x, n);

  return perpv(x, n);
}

struct vector perpp(const struct vector *x, const struct vector *n) {
  proj_assert(x, n);

  return projv(x, n);
}
