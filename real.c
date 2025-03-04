#include "real.h"

#include <stdio.h>
#include <assert.h>

int numlen(double num) {
  char buffer[50];
  int length = sprintf(buffer, "%.15g", num);
  return length;
}

int maxlen(const double *nums, int *lens, int len) {
  assert(nums);
  assert(lens);
  assert(len > 0);

  int max_len = 0;
  for (int i = 0; i < len; ++i) {
    lens[i] = numlen(nums[i]);
    if (lens[i] > max_len) {
      max_len = lens[i];
    }
  }

  return max_len;
}
