#include"strglob.h"

size_t count_strptrs(char *restrict *restrict sptrs) {
  register char *restrict *restrict pp = sptrs;

  while(*pp++);

  return (size_t)(sptrs - pp);
}
