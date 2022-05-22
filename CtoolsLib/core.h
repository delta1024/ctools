#ifndef  CTOOLS_CORE_LIB_H
#define  CTOOLS_CORE_LIB_H
#include <stdlib.h>
#include <dirent.h>

/* a helper function to calculate  a new array size. */
int memory_grow_size(uint old_size);

/* wrapper around malloc() */
void *memory_array_create(uint count, size_t stride);

/* Adjusts size of handle by new_size * stride. */
void *memory_array_adjust(void *handle, int new_size, size_t stride);

/* Reads the file at path to a string.

   Will leak memory if not freed befor program termination.*/
char *io_file_to_string(const char *path);

/* recursivly searches up the directory tree for a .git directory starting at base_dir.
   
   Returns NULL if no .git directory is found. */
//char *io_find_git_dir(const char *base_dir);

/* Returns 0 if the directory entry begins with '.'.  */
int io_direntry_is_hidden(const struct dirent *entry);

/* Returns - if the directory entry name is equal to '.' or '..'. */
int io_direntry_is_parent_or_self(const struct dirent *entry);


#endif
