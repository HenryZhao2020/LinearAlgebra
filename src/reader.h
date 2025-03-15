// "reader.h" handles input related to linear algebra types
//   and provides error-checking to ensure valid data.

#ifndef READER_H
#define READER_H

#include <stdbool.h>

struct vector;

// read_int(num) reads an integer num.
// requires: num is not NULL
// effects: reads input, may produce output
//          may mutate num
bool read_int(int *num);

// read_int_range(num, low, high) keeps reading an integer num until
//   low <= num <= high.
// requires: num is not NULL
//           low <= high
// effects: reads input, may produce output
//          may mutate num
bool read_int_range(int *num, const int low, const int high);

// read_vec_comp(v, n) prompts the components of v in Rn.
//   The function updates v and produces true if all inputs were valid.
//   Otherwise, v remains unchanged, and the function produces false.  
// requires: v is not NULL
//           0 <= n <= max_vec_n
// effects: reads input, produces output
//          may mutate v
bool read_vec_comp(struct vector *v, const int n);

// read_vec(v_arr, num_v) prompts num_v vectors from v_arr.  
//   The function updates the vectors in v_arr and produces true if 
//   all inputs were valid.
//   Otherwise, v remains unchanged, and the function produces false.  
//   var is the name of vec.  
// requires: v_arr is not NULL
//           num_v is the length of v_arr
// effects: reads input, produces output
//          may mutate v_arr
bool read_vec(struct vector *v_arr[], const int num_v);

#endif
