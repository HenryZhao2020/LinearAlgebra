#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR '\\'
#else
#include <libgen.h>
#define PATH_SEPARATOR '/'
#endif

int main(int argc, char *argv[]) {
  char executablePath[PATH_MAX];
  char dir[PATH_MAX];
  char filePath[PATH_MAX];
  FILE *file;
  char buffer[1024];

#ifdef _WIN32
  if (GetModuleFileName(NULL, executablePath, sizeof(executablePath)) == 0) {
    perror("GetModuleFileName");
    return 1;
  }
  char *lastSlash = strrchr(executablePath, PATH_SEPARATOR);
  if (lastSlash != NULL) {
    *lastSlash = '\0'; // Null-terminate to get the directory
    strncpy(dir, executablePath, sizeof(dir));
    dir[sizeof(dir) - 1] = '\0'; // Ensure null termination
  } else {
    fprintf(stderr, "Error: Could not find directory.\n");
    return 1;
  }
#else
  if (realpath(argv[0], executablePath) == NULL) {
    perror("realpath");
    return 1;
  }
  char *dir_ptr = dirname(executablePath);
  if (dir_ptr == NULL) {
    fprintf(stderr, "Error: Could not find directory.\n");
    return 1;
  }
  strncpy(dir, dir_ptr, sizeof(dir));
  dir[sizeof(dir) - 1] = '\0'; // Ensure null termination
#endif

  if (chdir(dir) != 0) {
    perror("chdir");
    return 1;
  }

  snprintf(filePath, sizeof(filePath), "help.txt");

  file = fopen(filePath, "r");

  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
  }

  fclose(file);
  return 0;
}
