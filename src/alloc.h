#pragma once

void* __xmalloc(
  size_t number_of_bytes, 
  const char* source_file, 
  size_t line_number
);

void* __xcalloc(
  size_t number_of_elements, 
  size_t size_of_each_element, 
  const char* source_file, 
  size_t line_number
);

void* __xrealloc(
  void* old_memory, 
  size_t new_size,
  const char* source_file, 
  size_t line_number
);