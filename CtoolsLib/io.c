#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "core.h"

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

int dir_has_git(const struct dirent *entry) {
  if (strlen(entry->d_name) == 4 && memcmp(entry->d_name,".git", sizeof(char) * 4) == 0)
    return 1;
  else
    return 0;
}

char *io_find_git_dir(const char *base_dir) {
  char *cur_dir;
  int dir_result;
  struct dirent **entry;

  cur_dir = getcwd(NULL, 0);
  dir_result = scandir(cur_dir, &entry, dir_has_git, NULL);
  
  if (dir_result == -1) {
    // We've encounterd an error reading the directory
    fprintf(stderr, "Could not read directory!\n");
    free(cur_dir);
    exit(74);
  } else if (dir_result == 0) {

    if (cur_dir[1] == '\0') {
      free(cur_dir);
      return NULL;
    }
    free(cur_dir);
    chdir("..");
    cur_dir = io_find_git_dir(base_dir);
  } else {
    while(dir_result--) {
      
    }
  }
  chdir(base_dir);
  return cur_dir;
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


