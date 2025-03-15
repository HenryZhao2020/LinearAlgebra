#include "reader.h"
#include "vector.h"

#include <stdio.h>
#include <assert.h>

bool read_int(int *num) {
  assert(num);
  return read_int_range(num, -__INT_MAX__, __INT_MAX__);
}

bool read_int_range(int *num, const int low, const int high) {
  assert(num);
  assert(low <= high);

  int valid_num = 0;
  do {
    if (1 != scanf("%d", &valid_num)) {
      return false;
    } else if (valid_num < low || valid_num > high) {
      printf("Please enter a number from %d to %d: ", low, high);
    }
  } while (valid_num < low || valid_num > high);

  *num = valid_num;
  return true;
}

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
  if (!read_int_range(&n, 0, max_vec_n)) {
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
