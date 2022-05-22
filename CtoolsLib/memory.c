#include <stdlib.h>

#include "core.h"

int memory_grow_size(uint old_size) {
  return old_size < 8 ? 8 : old_size * 2;
}

void *memory_array_create(uint count, size_t stride) {
 return malloc(count * stride);
}

void *memory_array_adjust(void *handle, int new_size, size_t stride) {
  if (new_size == 0) {
    free(handle);
    return NULL;
  }

  return realloc(handle, new_size * stride);
  
}
