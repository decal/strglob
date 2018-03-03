#include"strglob.h"

size_t count_strptrs(const char *restrict *restrict sptrs) {
  register const char *restrict *restrict pp = sptrs;

  while(*pp++);

  return (size_t)(sptrs - pp);
}
