#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

static const int FILE_READ_FAIL = 1;

// load_help_doc() produces the content of "help.txt" if the file is loaded
//   and NULL otherwise;
// effects: allocates a heap array (caller must free)
static char *load_help_doc() {
  FILE *file = fopen("help.txt", "r");
  if (!file) {
    return NULL;
  }

  // Move file pointer to the end to get file size
  fseek(file, 0, SEEK_END);
  const long file_size = ftell(file);
  // Move back to the beginning
  rewind(file);  

  // Read entire file into memory
  char *help_doc = malloc(file_size + 1);
  fread(help_doc, 1, file_size, file);
  help_doc[file_size] = '\0';
  fclose(file);

  return help_doc;
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
  char *help_doc = load_help_doc();
  if (!help_doc) {
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
  free(help_doc);
}
