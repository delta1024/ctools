#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "core.h"
#include <string.h>

char *io_file_to_string(const char *path) {
  FILE *file;
  char *string;
  size_t end;
  file = fopen(path, "rb");

  fseek(file, 0L, SEEK_END);
  end = ftell(file);
  rewind(file);

  string = (char*)malloc(end + 1);
  if (string == NULL) {
    fprintf(stderr, "Not enough memmory to read \"%s\".\n", path);
    exit(74);
  }

  size_t bytes_read = fread(string, sizeof(char), end, file);
  string[bytes_read] = '\0';
  fclose(file);
  
  return string;
  
}

#define TRUE 0
#define FALSE 1
int io_direntry_is_hidden(const struct dirent *entry) {
  if (entry->d_name[0] == '.' ) return TRUE;
    else return FALSE;
}

int io_direntry_is_parent_or_self(const struct dirent *entry) {
  char root;
  root = entry->d_name[0];
  if (root == '.' ){
    root = entry->d_name[1];
    if (root == '.' || root == '\0')
      return TRUE;
  }
  else
    return FALSE;
}
#undef TRUE
#undef FASLE
