#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <mylib.h>

#define MAX_DIRECTORY_NAME_SIZE 2048	/* Maximum directory name size */

int main() {
  int dir_result;
  DIR *cur_dir;
  struct dirent **names;
  char initial_directory[MAX_DIRECTORY_NAME_SIZE];
  
  dir_result = scandir("./", &names, io_direntry_is_parent_or_self, alphasort);
  int i = 0;
  while(dir_result--) {
    printf("%s\n", names[i]->d_name);
    free(names[i++]);
  }
  free(names);
  exit(0);
}
