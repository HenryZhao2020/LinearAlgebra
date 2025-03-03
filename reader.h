// "reader.h" handles input related to linear algebra types
//   and provides error-checking to ensure valid data.

#ifndef READER_H
#define READER_H

#include <stdbool.h>

struct vector;

// read_vec_comp(v, n) prompts the components of v in Rn.
//   The function updates v and produces true if all inputs were valid.
//   Otherwise, v remains unchanged, and the function produces false.  
// requires: v is not NULL
//           0 <= n <= max_n
// effects: reads input, produces output
//          may mutate v
bool read_vec_comp(struct vector *v, int n);

// read_vec(v_arr, num_v) prompts num_v vectors from v_arr.  
//   The function updates the vectors in v_arr and produces true if 
//   all inputs were valid.
//   Otherwise, v remains unchanged, and the function produces false.  
//   var is the name of vec.  
// requires: v_arr is not NULL
//           num_v is the length of v_arr
// effects: reads input, produces output
//          may mutate v_arr
bool read_vec(struct vector *v_arr[], int num_v);

#endif
