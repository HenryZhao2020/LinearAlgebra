#include "reader.h"
#include "vector.h"

#include <stdio.h>
#include <assert.h>

bool read_int(const char *prompt, int *num, int min, int max) {
  assert(prompt);
  assert(num);

  int valid_num = 0;
  while (true) {
    printf("%s", prompt);
    if (1 != scanf("%d", &valid_num)) {
      return false;
    } else if (valid_num >= min && valid_num <= max) {
      *num = valid_num;
      return true;
    } else {
      printf("Please enter an integer from %d to %d!\n", min, max);
    }
  }
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
  if (!read_int("Enter the vector dimension (n): ", &n, 0, max_vec_n)) {
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
