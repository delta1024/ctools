#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <ctools/core.h>


#define MAX_DIRECTORY_NAME_SIZE 256
#define MAX_DIRECTORY_HEADER_CONTENTS MAX_DIRECTORY_NAME_SIZE

int is_header_file(const struct dirent *entry) {
  const char *header_sufix, *to_compare;
  int len;

  header_sufix = ".h";
  len = strlen(entry->d_name);
  len -= 2;
  
  to_compare = &entry->d_name[len];
  return !strcmp(header_sufix, to_compare); 
    
}


int main() {
  char cwd[MAX_DIRECTORY_NAME_SIZE], *full_path, **header_files;
  int i, n;
  struct dirent **header_array;
  getcwd(cwd, MAX_DIRECTORY_NAME_SIZE);

  i = scandir(".", &header_array, is_header_file, NULL);

  if (i == 0) {
    printf("No header file found in current directory\n");
    exit(1);
  }

  header_files = (char**)malloc(sizeof(char*) * i);
  n = 0;
  while (i--) {
    full_path = io_canonicalize_file(cwd, header_array[i]);
    header_files[n++] = io_file_to_string(full_path);
    free (full_path);
    free(header_array[i]);
  }

  for(i = 0; i < n; i++) {
    printf("%s\n", header_files[i]);
    free(header_files[i]);
  }

  free(header_files);
  /* char *c = "hello.h"; */
  /* int len = strlen(c); */
  /* len -= 2; */
  /* char *b = &c[len]; */
  /* printf("%s\n",b); */

  
  /* if (git_dir == NULL) { */
  /*   fprintf(stderr, "No git dir found.\n"); */
  /*   exit(1); */
  /* } */
    
  //  chdir(git_dir);
  /* i = io_filter_dirs(git_dir, &test_array, true);   */

  /* while(i--) { */
  /*   printf("%s\n", test_array[i]->d_name);     */
  /*   free(test_array[i]); */
  /* } */
  /* free(test_array); */
  /* free(git_dir); */

  exit(0);
}
