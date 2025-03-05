// "printer.h" extends output functionality with additional options 
//   beyond printf.

#ifndef PRINTER_H
#define PRINTER_H

// print_space(spaces) outputs num_spaces spaces.
// effects: produces output
void print_space(const int num_spaces);

// print_real(num) outputs num properly, particularly avoiding outputting 
//   -0 instead 0.
// effects: produces output
void print_real(const double num);

#endif
