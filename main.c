#include "vector.h"
#include "matrix.h"
#include "basis.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

const char *cmd_chart[] = {
  "exit",     "Terminate the program",
  "help",     "View program manual",
  // ------------vector------------
  "vadd",     "Perform addition of two vectors",
  "vsmult",   "Perform scalar multiplication of a vector",
  "dot",      "Compute the dot product of two vectors in Rn",
  "cross",    "Compute the cross product of two vectors in R3",
  "vlen",     "Determine the length (norm) of a vector",
  "vang",     "Determine the angle between two vectors in radians",
  // ------------matrix------------
  "stdbas",   "Determine the standard basis of Rn",
};

// read_vec_comp(vec, n, var) reads the components of vec in Rn.
//   If the input is valid, it updates vec and returns true.  
//   Otherwise, vec remains unchanged, and the function returns false.  
//   var is the name of vec.
// requires: vec and var are not NULL
//           min_n <= n <= max_n
// effects: reads input, produces output
//          may mutate vec
bool read_vec_comp(struct vector *vec, int n, const char *var) {
  assert(vec);
  assert(n >= min_n && n <= max_n);
  assert(var);

  int comp[100] = {0};
  printf("Defining components of the vector %s\n", var);
  for (int i = 0; i < n; ++i) {
    printf("x%d: ", (i + 1));
    if (1 != scanf("%d", &comp[i])) {
      return false;
    }
  }

  for (int i = 0; i < n; ++i) {
    vec->comp[i] = comp[i];
  }

  return true;
}

// read_vec(vec, var) reads the dimension and the components of a vector.  
//   If the input is valid, it updates vec and returns true.  
//   Otherwise, vec remains unchanged, and the function returns false.  
//   var is the name of vec.  
// requires: vec and var are not NULL
// effects: reads input, produces output
//          may mutate vec
bool read_vec(struct vector *vec, const char *var) {
  assert(vec);
  assert(var);

  int n = 0;
  printf("Defining vector %s\n", var);
  printf("Dimension: ");
  if (1 != scanf("%d", &n)) {
    return false;
  }

  read_vec_comp(vec, n, var);
  vec->n = n;

  return true;
}

// exec_vadd() performs addition of two vectors.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vadd() {
  struct vector v1 = {0, {0}};
  struct vector v2 = {0, {0}};

  if (!read_vec(&v1, "v1")) {
    return false;
  }
  printf("\n");
  if (!read_vec(&v2, "v2")) {
    return false;
  }
  printf("\n");

  struct vector sum = vec_add(&v1, &v2);
  printf("Vector addition:\n");
  print_vec(&v1);
  printf("+\n");
  print_vec(&v2);
  printf("=\n");
  print_vec(&sum);
  printf("\n");

  return true;
}

// exec_vsmult() performs scalar multiplication of a vector.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vsmult() {
  struct vector vec = {0, {0}};
  if (!read_vec(&vec, "v")) {
    return false;
  }
  printf("\n");

  int c = 0;
  printf("c: ");
  if (1 != scanf("%d", &c)) {
    return false;
  }
  printf("\n");

  struct vector prod = vec_scalar_mult(&vec, c);
  printf("Vector scalar multiplication:\n");
  printf("%d\n", c);
  printf("*\n");
  print_vec(&vec);
  printf("=\n");
  print_vec(&prod);
  printf("\n");

  return true;
}

// exec_dot() computes the dot product of two vectors in Rn.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_dot() {
  struct vector v1 = {0, {0}};
  struct vector v2 = {0, {0}};

  if (!read_vec(&v1, "v1")) {
    return false;
  }
  printf("\n");
  if (!read_vec(&v2, "v2")) {
    return false;
  }
  printf("\n");

  int dp = dot_product(&v1, &v2);
  printf("Dot product of v1 and v2 is: %d\n", dp);

  return true;
}

// exec_cross() computes the cross product of two vectors in R3.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_cross() {
  struct vector v1 = {3, {0}};
  struct vector v2 = {3, {0}};

  if (!read_vec_comp(&v1, 3, "v1 in R3")) {
    return false;
  }
  printf("\n");
  if (!read_vec_comp(&v2, 3, "v2 in R3")) {
    return false;
  }
  printf("\n");

  struct vector cross = cross_product(&v1, &v2);
  printf("Cross product of v1 and v2 is:\n");
  print_vec(&cross);

  return true;
}

// exec_vlen() determines the length (norm) of a vector.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vlen() {
  struct vector vec = {0, {0}};
  if (!read_vec(&vec, "v")) {
    return false;
  }
  printf("\n");

  double len = vec_len(&vec);
  printf("Length (norm) of v is: %g\n", len);

  return true;
}

// exec_vang() determines the angle between two vectors in radians.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vang() {
  struct vector v1 = {0, {0}};
  struct vector v2 = {0, {0}};

  if (!read_vec(&v1, "v1")) {
    return false;
  }
  printf("\n");
  if (!read_vec(&v2, "v2")) {
    return false;
  }
  printf("\n");

  double ang = vec_angle(&v1, &v2);
  printf("Angle between v1 and v2 in radians is: %g\n", ang);

  return true;
}

// exec_stdbas() determines the standard basis for Rn.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_stdbas() {
  int n = 0;
  printf("Dimension: ");
  if (1 != scanf("%d", &n)) {
    return false;
  }

  struct matrix basis = std_basis(n);
  printf("Standard basis for R%d\n", n);
  print_matrix(&basis);

  return true;
}

// help() outputs program mannual and developer info.
// effects: produces output
void help() {
  const int dashes = 35;

  printf("Command\t\tOperation\n");
  for (int i = 0; i < dashes; ++i) printf("-");
  printf("\n");

  const char **chart = cmd_chart;
  while (*(chart + 1)) {
    printf("%s\t\t%s\n", *chart, *(chart + 1));
    chart += 2;
  }

  printf("\nProgram Information\n");
  for (int i = 0; i < dashes; ++i) printf("-");
  printf("\n");
  printf("Developer:\tHenry Zhao\n");
  printf("Version:\tv1.0\n");
  printf("Reference:\tD. Wolczuk, MATH 136 Course Notes Edition 2024.1\n");
}

int main(void) {
  const int cmd_max_len = 10;

  printf("Welcome to the Centre for Linear Algebra!\n");
  printf("Please enter 'help' to get started.\n\n\n");
  
  while (true) {
    char cmd[11];
    printf("Enter command (e.g. va, dot): ");
    if (1 != scanf("%10s", cmd)) {
      break;
    }
    printf("\n");
    
    if (!strcmp(cmd, "exit")) {
      break;
    } else if (!strcmp(cmd, "help")) {
      help();
    } else if (!strcmp(cmd, "vadd")) {
      exec_vadd();
    } else if (!strcmp(cmd, "vsmult")) {
      exec_vsmult();
    } else if (!strcmp(cmd, "dot")) {
      exec_dot();
    } else if (!strcmp(cmd, "cross")) {
      exec_cross();
    } else if (!strcmp(cmd, "vlen")) {
      exec_vlen();
    } else if (!strcmp(cmd, "vang")) {
      exec_vang();
    } else if (!strcmp(cmd, "stdbas")) {
      exec_stdbas();
    } else {
      printf("Invalid command! Please enter 'help' to see the program manual.\n");
    }

    printf("\n");
  }

  printf("\nHope you enjoy linear algebra! See you next time.\n");
}
