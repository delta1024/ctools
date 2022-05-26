#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "core.h"

#define MAX_DIRECTORY_NAME_SIZE 256

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

int io_filter_dirs(const char *path, struct dirent ***dest, bool filter_hidden) {
  struct dirent *ip, *ep, *curp;
  DIR *dirp;
  int count, cap;
  struct stat stats;
  char comp_buffer[(MAX_DIRECTORY_NAME_SIZE * 2) + 1];

  count = 0;
  cap = 0 ;
  *dest = (struct dirent**)malloc(sizeof(struct dirent*) * cap);  
  dirp = opendir(path);
  while((curp = readdir(dirp)) != NULL) {
    if (cap < count) {
      cap = (cap < 8) ? 8 : cap * 2;
      *dest = (struct dirent**)realloc(*dest, sizeof(struct dirent*) * cap);
    }

    strcpy(comp_buffer, path);
    strcat(comp_buffer, "/");
    strcat(comp_buffer, curp->d_name);
    stat(comp_buffer, &stats);

    if (S_ISDIR(stats.st_mode)) {
      if (filter_hidden && curp->d_name[0] == '.') continue;
      struct dirent *address = (struct dirent*)malloc(sizeof(struct dirent));
      address->d_off = curp->d_off;
      address->d_reclen = curp->d_reclen;
      address->d_type = curp->d_type;
      strcpy(address->d_name, curp->d_name);

      (*dest)[count++] = address;    
    }
  

  }

  closedir(dirp);
 
  if (count == 0) {
    free(*dest);
    return -1;
  }
  else 
    return count;
}

char *io_canonicalize_file(const char *path, const struct dirent *entry) {
  int path_len, entry_len, total_len;
  char *cannonical_path;
  path_len = strlen(path);
  entry_len = strlen(entry->d_name);
  total_len = path_len + entry_len + 2;
  cannonical_path = (char*)malloc(sizeof(char) * total_len);
  strcpy(cannonical_path, path);
  strcat(cannonical_path, "/");
  strcat(cannonical_path, entry->d_name);
  return cannonical_path;
}

#undef MAX_DIRECTORY_NAME_SIZE
