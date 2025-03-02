#include "vector.h"
#include "matrix.h"
#include "basis.h"
#include "proj.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// clear_screen() clears the console screen.
void clear_screen() {
  printf("\033[2J\033[H");
}

// dash() prints a separating line with dashes.
// effects: produces output
void dash() {
  const int dashes = 40;
  for (int i = 0; i < dashes; ++i) {
    printf("-");
  }
  printf("\n");
}

// read_vec_comp(v, n) prompts the components of v in Rn.
//   The function updates v and produces true if all inputs were valid.
//   Otherwise, v remains unchanged, and the function produces false.  
// requires: v is not NULL
//           0 <= n <= max_n
// effects: reads input, produces output
//          may mutate v
bool read_vec_comp(struct vector *v, int n) {
  assert(v && v->name);
  assert(n >= 0 && n <= max_n);

  printf("Enter components of %s\n", v->name);

  double comp[100] = {0};
  for (int i = 0; i < n; ++i) {
    printf("%s%d: ", v->name, (i + 1));
    if (1 != scanf("%lf", &comp[i])) {
      return false;
    }
  }

  for (int i = 0; i < n; ++i) {
    // Avoid printing -0 instead of 0
    if (comp[i] == -0.0) {
      comp[i] = 0;
    }
    v->comp[i] = comp[i];
  }

  return true;
}

// read_vec(v_arr, num_v) prompts num_v vectors from v_arr.  
//   The function updates the vectors in v_arr and produces true if 
//   all inputs were valid.
//   Otherwise, v remains unchanged, and the function produces false.  
//   var is the name of vec.  
// requires: v_arr is not NULL
//           num_v is the length of v_arr
// effects: reads input, produces output
//          may mutate v_arr
bool read_vec(struct vector *v_arr[], int num_v) {
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

// exec_vadd() performs addition of two vectors.
//   The function produces true if the operations succeed and false otherwise.
// effects: reads input, produces output
bool exec_vadd() {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to evaluate %s + %s\n\n", u.name, v.name);  

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  struct vector sum = vec_add(&u, &v);
  printf("Adding each component of %s and %s:\n", u.name, v.name);
  for (int i = 0; i < v.n; ++i) {
    printf("\t%s%d + %s%d = %g\n", 
           u.name, (i + 1), v.name, (i + 1), sum.comp[i]);
  }

  printf("\nTherefore, %s + %s =\n", u.name, v.name);
  print_vec(&sum, true);

  return true;
}

// exec_vsmult() performs scalar multiplication of a vector.
//   The function produces true if the operations succeed and false otherwise.
// effects: reads input, produces output
bool exec_vsmult() {
  struct vector v = {0, {0}, "v"};

  printf("Let %s be a vector in Rn.\n", v.name);
  printf("Let c be a real number.\n");
  printf("We want to evaluate c%s\n\n", v.name);

  struct vector *v_arr[] = {&v};
  if (!read_vec(v_arr, 1)) {
    return false;
  }

  double c = 0;
  printf("Enter the value of c: ");
  if (1 != scanf("%lf", &c)) {
    return false;
  }
  printf("\n");

  struct vector prod = vec_scalar_mult(&v, c);
  printf("Multiplying each component of %s by c:\n", v.name);
  for (int i = 0; i < v.n; ++i) {
    printf("\tc(%s%d) = %g\n", v.name, (i + 1), prod.comp[i]);
  }
  
  printf("\nTherefore, c%s =\n", v.name);
  print_vec(&prod, true);
  
  return true;
}

// exec_dot() evaluates the dot product of two vectors in Rn.
//   The function produces true if the operations succeed and false otherwise.
// effects: reads input, produces output
bool exec_dot() {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to evaluate the dot product %s · %s\n\n", u.name, v.name);  

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  double dot = dot_product(&u, &v);
  for (int i = 0; i < v.n; ++i) {
    if (i) {
      printf(" + ");
    }
    printf("%s%d%s%d", u.name, (i + 1), v.name, (i + 1));
  }
  printf(" = %g\n\n", dot);
  
  printf("Therefore, the dot product %s · %s is %g\n", 
         u.name, v.name, dot);

  return true;
}

// exec_cross() evaluates the cross product of two vectors in R3.
//   The function produces true if the operations succeed and false otherwise.
// effects: reads input, produces output
bool exec_cross() {
  struct vector u = {3, {0}, "u"};
  struct vector v = {3, {0}, "v"};

  printf("Let %s and %s be vectors in R3.\n", u.name, v.name);
  printf("We want to evaluate %s x %s\n\n", u.name, v.name);  

  read_vec_comp(&u, 3);
  printf("\n");
  read_vec_comp(&v, 3);
  printf("\n");

  printf("Evaluating components of the cross product:\n");
  struct vector cross = cross_product(&u, &v);
  const int indices[] = {2, 3, 3, 1, 1, 2};
  for (int i = 0; i < 3; ++i) {
    printf("\t%s%d%s%d - %s%d%s%d = %g\n", 
           u.name, indices[i * 2], v.name, indices[i * 2 + 1], 
           u.name, indices[i * 2 + 1], v.name, indices[i * 2], 
           cross.comp[i]);
  }

  printf("\nTherefore, the cross product %s x %s is:\n", u.name, v.name);
  print_vec(&cross, true);

  return true;
}

// exec_vlen() determines the length (norm) of a vector.
//   The function produces true if the operations succeed and false otherwise.
// effects: reads input, produces output
bool exec_vlen() {
  struct vector v = {0, {0}, "v"};

  printf("Let %s be a vector in Rn.\n", v.name);
  printf("We want to determine the length (norm) of v.\n\n");

  struct vector *v_arr[] = {&v};
  if (!read_vec(v_arr, 1)) {
    return false;
  }
  
  double len = vec_len(&v);
  printf("||%s|| = √(%s · %s) = %g\n\n", v.name, v.name, v.name, len);
  printf("Therefore, the length (norm) of %s is: %g\n", v.name, len);

  return true;
}

// exec_vang() determines the angle between two vectors in radians.
//   The function produces true if the operations succeed and false otherwise.
// effects: reads input, produces output
bool exec_vang() {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to determine the angle (θ) between %s and %s, "
         "where θ is in radians.\n\n", u.name, v.name);  

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  double ang = vec_angle(&u, &v);
  printf("θ = arccos((%s · %s) / (||%s|| ||%s||)) = %g\n\n", 
         u.name, v.name, u.name, v.name, ang);

  printf("Therefore, the angle (θ) between %s and %s in radians is %g\n", 
         u.name, v.name, ang);

  return true;
}

// exec_projv() finds the projection of a vector onto another vector.
// effects: reads input, produces output
bool exec_projv() {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to find the projection of %s onto %s.\n\n",
         u.name, v.name);

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  printf("proj%s(%s) = [(%s · %s) / ||%s||²] %s\n\n", 
         v.name, u.name, u.name, v.name, v.name, v.name);

  struct vector proj = projv(&u, &v);
  printf("Therefore, the projection of %s onto %s is:\n", u.name, v.name);
  print_vec(&proj, true);

  return true;
}

// exec_perpv() finds the perpendicular of a vector onto another vector.
// effects: reads input, produces output
bool exec_perpv() {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to find the perpendicular of %s onto %s.\n\n",
         u.name, v.name);

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  printf("perp%s(%s) = %s - [(%s · %s) / ||%s||²] %s\n\n", 
         v.name, u.name, u.name, u.name, v.name, v.name, v.name); 

  struct vector perp = perpv(&u, &v);
  printf("Therefore, the perpendicular of %s onto %s is:\n", u.name, v.name);
  print_vec(&perp, true);

  return true;
}

// exec_projp() finds the projection of a vector in R3 onto a plane.
// effects: reads input, produces output
bool exec_projp() {
  struct vector x = {3, {0}, "x"};
  struct vector n = {3, {0}, "n"};

  printf("Let %s and %s be vectors in R3.\n", x.name, n.name);
  printf("We want to find the projection of %s onto a plane,\n", x.name);
  printf("where the plane has a normal vector %s.\n\n", n.name);

  read_vec_comp(&x, 3);
  printf("\n");
  read_vec_comp(&n, 3);
  printf("\n");

  printf("projP(%s) = %s - [(%s · %s) / ||%s||²] %s\n\n", 
         x.name, x.name, x.name, n.name, n.name, n.name);

  struct vector proj = projp(&x, &n);
  printf("The projection of x onto the plane is:\n");
  print_vec(&proj, true);

  return true;
}

// exec_perpp() finds the perpendicular of a vector in R3 onto a plane.
// effects: reads input, produces output
bool exec_perpp() {
  struct vector x = {3, {0}, "x"};
  struct vector n = {3, {0}, "n"};

  printf("Let %s and %s be vectors in R3.\n", x.name, n.name);
  printf("We want to find the perpendicular of %s onto a plane,\n", x.name);
  printf("where the plane has a normal vector %s.\n\n", n.name);

  read_vec_comp(&x, 3);
  printf("\n");
  read_vec_comp(&n, 3);
  printf("\n");

  printf("perpP(%s) = [(%s · %s) / ||%s||²] %s\n\n", 
         x.name, x.name, n.name, n.name, n.name);

  struct vector perp = perpp(&x, &n);
  printf("The perpendicular of x onto the plane is:\n");
  print_vec(&perp, true);

  return true;
}

// help() outputs program manual and developer info.
// effects: produces output
void help() {
  printf("Program Controls\n");
  dash();
  printf("exit\t\tTerminate the program\n");
  printf("help\t\tView program manual\n");
  printf("\n");

  printf("Vector Operations\n");
  dash();
  printf("vadd\t\tPerform addition of two vectors\n");
  printf("vsmult\t\tPerform scalar multiplication of a vector\n");
  printf("dot\t\tEvaluate the dot product of two vectors\n");
  printf("cross\t\tEvaluate the cross product of two vectors in R3\n");
  printf("vlen\t\tDetermine the length (norm) of a vector\n");
  printf("vang\t\tDetermine the angle between two vectors in radians\n");
  printf("\n");

  printf("Projections\n");
  dash();
  printf("projv\t\tFind the projection of a vector onto another vector\n");
  printf("perpv\t\tFind the perpendicular of a vector onto another vector\n");
  printf("projp\t\tFind the projection of a vector in R3 onto a plane\n");
  printf("perpp\t\tFind the perpendicular of a vector in R3 onto a plane\n");
  printf("\n");

//   printf("Matrix Operations\n");
//   dash();
//   printf("madd\t\tPerform addition of two matrices\n");
//   printf("msmult\t\tPerform scalar multiplication of a matrix\n");
//   printf("\n");

//   printf("Basis\n");
//   dash();
//   printf("stdbas\t\tDetermine the basis for Rn\n");
}

int main(void) {
  const int cmd_max_len = 10;

  clear_screen();
  printf("Welcome to the Centre for Linear Algebra!\n");
  printf("Please enter 'help' to get started.\n\n\n");
  
  while (true) {
    char cmd[11];
    printf("Enter command (e.g. vadd, dot): ");
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
    } else if (!strcmp(cmd, "projv")) {
      exec_projv();
    } else if (!strcmp(cmd, "perpv")) {
      exec_perpv();
    } else if (!strcmp(cmd, "projp")) {
      exec_projp();
    } else if (!strcmp(cmd, "perpp")) {
      exec_perpp();
    } else {
      printf("Invalid command! Please enter 'help' to see the program manual.\n");
    }

    printf("\n\n");
  }

  printf("Hope you enjoy linear algebra! See you next time.\n");
}
