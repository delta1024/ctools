#ifndef  CTOOLS_CORE_LIB_H
#define  CTOOLS_CORE_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>

//-------------------MEMORY---------------------------//

/* a helper function to calculate  a new array size. */
int memory_grow_size(uint old_size);

/* wrapper around malloc() */
void *memory_array_create(uint count, size_t stride);

/* Adjusts size of handle by new_size * stride. */
void *memory_array_adjust(void *handle, int new_size, size_t stride);


//---------------------IO-----------------------------//

/* Reads the file at path to a string.

   Will leak memory if not freed befor program termination.*/
char *io_file_to_string(const char *path);

/* Recursivly searches up the directory tree for a .git directory starting at *cur_dir.
   Resulting string must be freed as it is allocated by malloc.
   
   Returns NULL if no .git directory is found. */
char *io_find_git_dir(const char *cur_dir);

/* Returns 0 if the directory entry begins with '.'.  */
int io_direntry_is_hidden(const struct dirent *entry);

/* Returns 0 if the directory entry name is equal to '.' or '..'. */
int io_direntry_is_parent_or_self(const struct dirent *entry);

/* Collects entires in path into dest; malloc is used to allocate each dirent.
   If filter_hidden is ture omits hidden directories.

   Returns -1 if no directories are found.*/
int io_filter_dirs(const char *path, struct dirent ***dest, bool filter_hidden);

/* Returns the absolute path of entry reletive to path.

   Resulting string must be freed as it is allocated with malloc.*/
char *io_canonicalize_file(const char *path, const struct dirent *entry);

#endif
