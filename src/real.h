// "real.h" provides utilities for real number operations.

#ifndef REAL_H
#define REAL_H

// numlen(num) produces the length of num, including the negative sign 
//   and decimal places.
int numlen(const double num);

// maxlen(nums, lens, len) stores the length of each number in nums to lens 
//   and produces the maximum length among the numbers in nums.
// requires: nums and lens are not NULL.
//           len is the length of nums and lens, len > 0
// effects: mutates lens
int maxlen(const double *nums, int *lens, const int len);

#endif
