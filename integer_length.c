#include"strglob.h"

size_t integer_length(long x) {
#ifdef DEBUG_STRGLOB
  fputs("Entering integer_length()\n", stderr);
#endif

  register size_t l = 0;

  while(x > 0) {
    x /= 10;
    l++;

    if(!x)
      break;
  }

  return l;
}
