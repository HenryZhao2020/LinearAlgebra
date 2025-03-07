#include "command.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

static const int FILE_READ_FAIL = 1;

static const int cmd_max_len = 10;
static const int help_doc_len = 5000;

// load_help_doc(help_doc) produces true if the content of "help.txt" 
//   is successfully loaded to help_doc and false otherwise.
// requires: help_doc is not NULL
// effects: may mutate help_doc
static bool load_help_doc(char *help_doc) {
  assert(help_doc);

  FILE *file = fopen("help.txt", "r");
  if (!file) {
    return false;
  }

  // Move file pointer to the end to get file size
  fseek(file, 0, SEEK_END);
  const long file_size = ftell(file);
  // Move back to the beginning
  rewind(file);  

  // Read entire file into memory
  fread(help_doc, 1, file_size, file);
  help_doc[file_size] = '\0';
  fclose(file);

  return true;
}

// help(help_doc) outputs help_doc.
// requires: help_doc is not NULL
// effects: produces output
static void help(const char *help_doc) {
  assert(help_doc);

  for (const char *doc = help_doc; *doc; ++doc) {
    printf("%c", *doc);
  }
}

int main(void) {
  char help_doc[5001] = {0};
  if (!load_help_doc(help_doc)) {
    printf("Error opening 'help.txt'!\n");
    return FILE_READ_FAIL;
  }

  printf("Welcome to the Centre for Linear Algebra!\n");
  printf("Please enter 'help' to get started.\n\n\n");
  
  while (true) {
    char cmd[11] = {0};
    printf("Enter command (e.g. vadd, dot): ");
    if (1 != scanf("%10s", cmd) || !strcmp(cmd, "exit")) {
      break;
    }
    printf("\n");
    
    if (!strcmp(cmd, "help")) {
      help(help_doc);
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
      printf("Invalid command!\n");
      printf("Please enter 'help' to view the program manual.\n");
    }

    printf("\n\n");
  }

  printf("\nHope you enjoy linear algebra! See you next time.\n");
}
