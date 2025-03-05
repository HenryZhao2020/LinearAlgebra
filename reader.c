#include "reader.h"
#include "vector.h"

#include <stdio.h>
#include <assert.h>

bool read_vec_comp(struct vector *v, const int n) {
  assert(v && v->name);
  assert(n >= 0 && n <= max_vec_n);

  printf("Enter components of %s\n", v->name);

  double comp[100] = {0};
  for (int i = 0; i < n; ++i) {
    printf("%s%d: ", v->name, (i + 1));
    if (1 != scanf("%lf", &comp[i])) {
      return false;
    }
  }

  for (int i = 0; i < n; ++i) {
    v->comp[i] = comp[i];
  }

  return true;
}

bool read_vec(struct vector *v_arr[], const int num_v) {
  assert(v_arr);
  assert(num_v > 0);
  for (int i = 0; i < num_v; ++i) {
    assert(v_arr[i] && v_arr[i]->name);
  }

  int n = 0;
  printf("Enter the vector dimension (n): ");  
  if (1 != scanf("%d", &n)) {
    return false;
  }
  printf("\n");

  for (int i = 0; i < num_v; ++i) {
    if (!read_vec_comp(v_arr[i], n)) {
      return false;
    }
    printf("\n");
  }

  for (int i = 0; i < num_v; ++i) {
    v_arr[i]->n = n;
  }

  return true;
}
