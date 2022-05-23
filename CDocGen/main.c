#include <stdio.h>
#include <stdlib.h>
#include <ctools/core.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_DIRECTORY_NAME_SIZE 256	
#define MAX_DIR_CONTENTS_SIZE 256

int main() {
  char *git_dir, entries[MAX_DIRECTORY_NAME_SIZE];
  int i;

  getcwd(entries, MAX_DIRECTORY_NAME_SIZE);
  git_dir = io_find_git_dir(entries);

  if (git_dir == NULL) {
    fprintf(stderr, "No git dir found.\n");
    exit(1);
  }

  chdir(git_dir);
  
  free(git_dir);

  exit(0);
}
