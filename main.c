#include "vector.h"
#include "matrix.h"
#include "basis.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

const int cmd_max_len = 10;

// read_vec(vec, var) reads the dimension n and the components of a vector.  
//   If the input is valid, it updates vec and returns true.  
//   Otherwise, vec remains unchanged, and the function returns false.  
//   var represents the name of vec.  
// requires: vec and var are not NULL.
// effects: reads input, produces output
//          may mutate vec.
bool read_vec(struct vector *vec, const char *var) {
  assert(vec);
  assert(var);

  int n = 0;
  int comp[100];

  printf("Defining vector %s\n", var);
  printf("Dimension: ");
  if (1 != scanf("%d", &n)) {
    return false;
  }

  printf("Defining components of the vector %s\n", var);
  for (int i = 0; i < n; ++i) {
    printf("x%d: ", (i + 1));
    if (1 != scanf("%d", &comp[i])) {
      return false;
    }
  }

  vec->n = n;
  for (int i = 0; i < n; ++i) {
    vec->comp[i] = comp[i];
  }

  return true;
}

// exec_vec_add() produces the result of adding two vectors.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vec_add() {
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

// exec_vec_scalar_mult() produces the result of scalar vector multiplication.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vec_scalar_mult() {
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

// exec_std_basis() produces the standard basis for Rn.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_std_basis() {
  int n = 0;
  printf("n: ");
  if (1 != scanf("%d", &n)) {
    return false;
  }

  struct matrix basis = std_basis(n);
  printf("Standard basis for R%d\n", n);
  print_matrix(&basis);
  return true;
}

// exec_dot_product() produces the dot product of two vectors.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_dot_product() {
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
  printf("Dot product is: %d\n", dp);
  return true;
}

// exec_cross_product() produces the cross product of two vectors.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_cross_product() {
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

  struct vector cross = cross_product(&v1, &v2);
  printf("Cross product is:\n");
  print_vec(&cross);
  return true;
}

// exec_vec_len() produces the length (norm) of a vector.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vec_len() {
  struct vector vec = {0, {0}};
  if (!read_vec(&vec, "v")) {
    return false;
  }
  printf("\n");

  int len = vec_len(&vec);
  printf("Length (norm): %d\n", len);
  return true;
}

// help() outputs program mannual and developer info.
// effects: produces output
void help() {
  const int dashes = 35;

  printf("(#)\tCommand\t\tOperation\n");
  for (int i = 0; i < dashes; ++i) printf("-");
  printf("\n");
  printf("(0)\texit\t\tTerminate the program\n");
  printf("(1)\thelp\t\tProgram manual and developer info\n");
  printf("(2)\tvadd\t\tVector addition\n");
  printf("(3)\tvsmult\t\tVector scalar multiplication\n");
  printf("(4)\tstdbas\t\tStandard basis of Rn\n");
  printf("(5)\tdot\t\tDot product of two vectors in Rn\n");
  printf("(6)\tcross\t\tCross product of two vectors in R3\n");
  printf("(7)\tvlen\t\tLength (norm) of a vector\n");

  printf("\nProgram Information\n");
  for (int i = 0; i < dashes; ++i) printf("-");
  printf("\n");
  printf("Developer:\tHenry Zhao\n");
  printf("Version:\tv1.0\n");
  printf("Reference:\tD. Wolczuk, MATH 136 Course Notes Edition 2024.1\n");
}

int main(void) {
  printf("Welcome to Linear Algebra Tutor!\n");
  printf("Please enter 'help' to get started.\n\n\n");
  
  while (true) {
    char cmd[11];
    printf("Enter number or command (e.g. 2 or va): ");
    if (1 != scanf("%10s", cmd)) {
      break;
    }
    printf("\n");
    
    if (!strcmp(cmd, "exit") || !strcmp(cmd, "0")) {
      break;
    } else if (!strcmp(cmd, "help") || !strcmp(cmd, "1")) {
      help();
    } else if (!strcmp(cmd, "vadd") || !strcmp(cmd, "2")) {
      exec_vec_add();
    } else if (!strcmp(cmd, "vsmult") || !strcmp(cmd, "3")) {
      exec_vec_scalar_mult();
    } else if (!strcmp(cmd, "stdbas") || !strcmp(cmd, "4")) {
      exec_std_basis();
    } else if (!strcmp(cmd, "dot") || !strcmp(cmd, "5")) {
      exec_dot_product();
    } else if (!strcmp(cmd, "cross") || !strcmp(cmd, "6")) {
      exec_cross_product();
    } else if (!strcmp(cmd, "vlen") || !strcmp(cmd, "7")) {
      exec_vec_len();
    } else {
      printf("Invalid command! Please enter 'help' to see the program manual.\n");
    }

    printf("\n");
  }

  printf("\nHope you ace linear algebra! See you next time.\n");
}
