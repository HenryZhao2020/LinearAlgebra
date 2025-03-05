#include "command.h"
#include "reader.h"
#include "vector.h"
#include "proj.h"

#include <stdio.h>

bool exec_vadd(void) {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to evaluate %s + %s\n\n", u.name, v.name);  

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  const struct vector sum = vec_add(&u, &v);
  printf("Adding each component of %s and %s:\n", u.name, v.name);
  for (int i = 0; i < v.n; ++i) {
    printf("\t%s%d + %s%d = %g\n", 
           u.name, (i + 1), v.name, (i + 1), sum.comp[i]);
  }

  printf("\nTherefore, %s + %s =\n", u.name, v.name);
  print_vec(&sum, true);

  return true;
}

bool exec_vsmult(void) {
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

  const struct vector prod = vec_scalar_mult(&v, c);
  printf("Multiplying each component of %s by c:\n", v.name);
  for (int i = 0; i < v.n; ++i) {
    printf("\tc(%s%d) = %g\n", v.name, (i + 1), prod.comp[i]);
  }
  
  printf("\nTherefore, c%s =\n", v.name);
  print_vec(&prod, true);
  
  return true;
}

bool exec_dot(void) {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to evaluate the dot product %s · %s\n\n", u.name, v.name);  

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  const double dot = dot_product(&u, &v);
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

bool exec_cross(void) {
  struct vector u = {3, {0}, "u"};
  struct vector v = {3, {0}, "v"};

  printf("Let %s and %s be vectors in R3.\n", u.name, v.name);
  printf("We want to evaluate %s x %s\n\n", u.name, v.name);  

  read_vec_comp(&u, 3);
  printf("\n");
  read_vec_comp(&v, 3);
  printf("\n");

  printf("Evaluating components of the cross product:\n");

  const struct vector cross = cross_product(&u, &v);
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

bool exec_vlen(void) {
  struct vector v = {0, {0}, "v"};

  printf("Let %s be a vector in Rn.\n", v.name);
  printf("We want to determine the length (norm) of v.\n\n");

  struct vector *v_arr[] = {&v};
  if (!read_vec(v_arr, 1)) {
    return false;
  }
  
  const double len = vec_len(&v);
  printf("||%s|| = √(%s · %s) = %g\n\n", v.name, v.name, v.name, len);
  printf("Therefore, the length (norm) of %s is: %g\n", v.name, len);

  return true;
}

bool exec_vang(void) {
  struct vector u = {0, {0}, "u"};
  struct vector v = {0, {0}, "v"};

  printf("Let %s and %s be vectors in Rn.\n", u.name, v.name);
  printf("We want to determine the angle (θ) between %s and %s, "
         "where θ is in radians.\n\n", u.name, v.name);  

  struct vector *v_arr[] = {&u, &v};
  if (!read_vec(v_arr, 2)) {
    return false;
  }

  const double ang = vec_angle(&u, &v);
  printf("θ = arccos((%s · %s) / (||%s|| ||%s||)) = %g\n\n", 
         u.name, v.name, u.name, v.name, ang);

  printf("Therefore, the angle (θ) between %s and %s in radians is %g\n", 
         u.name, v.name, ang);

  return true;
}

bool exec_projv(void) {
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

  const struct vector proj = projv(&u, &v);
  printf("Therefore, the projection of %s onto %s is:\n", u.name, v.name);
  print_vec(&proj, true);

  return true;
}

bool exec_perpv(void) {
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

  const struct vector perp = perpv(&u, &v);
  printf("Therefore, the perpendicular of %s onto %s is:\n", u.name, v.name);
  print_vec(&perp, true);

  return true;
}

bool exec_projp(void) {
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

  const struct vector proj = projp(&x, &n);
  printf("The projection of x onto the plane is:\n");
  print_vec(&proj, true);

  return true;
}

bool exec_perpp(void) {
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

  const struct vector perp = perpp(&x, &n);
  printf("The perpendicular of x onto the plane is:\n");
  print_vec(&perp, true);

  return true;
}
