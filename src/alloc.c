#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "alloc.h"

size_t __number_of_unfreed_allocations = 0;

void* __xmalloc(
  size_t number_of_bytes, 
  const char* source_file, 
  size_t line_number
) {
  void* buffer = malloc(number_of_bytes);
  #ifdef DEBUG
  if (buffer == NULL) {
    printf(
      "malloc failed (line %zi, file: \"%s\")\n", 
      line_number, 
      source_file
    );
    exit(EXIT_FAILURE);
  }
  __number_of_unfreed_allocations++;
  #endif
  return buffer;
}

void* __xcalloc(
  size_t number_of_elements, 
  size_t size_of_each_element, 
  const char* source_file, 
  size_t line_number
) {
  char* buffer = calloc(number_of_elements, size_of_each_element);
  #ifdef DEBUG
  if (buffer == NULL) {
    printf(
      "calloc failed (line %zi, file: \"%s\")\n", 
      line_number, 
      source_file
    );
    exit(EXIT_FAILURE);
  }
  __number_of_unfreed_allocations++;
  #endif
  return buffer;
}

void* __xrealloc(
  void* old_memory, 
  size_t new_size,
  const char* source_file, 
  size_t line_number
) {
  char* buffer = realloc(old_memory, new_size);
  #ifdef DEBUG
  if (buffer == NULL) {
    printf(
      "realloc failed (line %zi, file: \"%s\")\n", 
      line_number, 
      source_file
    );
    exit(EXIT_FAILURE);
  }
  __number_of_unfreed_allocations++;
  #endif
  return buffer;
}

void watch_memory() {
  #ifdef DEBUG
  if (__number_of_unfreed_allocations > 0) {
    printf("%zi leak(s)\n", __number_of_unfreed_allocations);
  }
  else {
    printf("NO detected leaks\n");
  }

  #else
  printf("Please insert \"#define DEBUG\" before you include 'alloc.c'\n");
  exit(EXIT_FAILURE);
  #endif
}

#define xmalloc(nbytes) __xmalloc(nbytes, __FILE__, __LINE__)
#define xcalloc(elem_count, elem_size) __xcalloc(elem_count, elem_size, __FILE__, __LINE__)
#define xrealloc(old_mem, new_size) __xrealloc(old_mem, new_size, __FILE__, __LINE__)
#define xfree(memory) free(memory); __number_of_unfreed_allocations--;