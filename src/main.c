#define DEBUG

#include "alloc.c"
#include <stdio.h>

int main(int argc, char**argv) {
  void* mem = xmalloc(23);
  xfree(mem);
  watch_memory();
}