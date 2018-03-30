#include"strglob.h"

size_t measure_integer(long int x) {
#ifdef DEBUG_FUNCS
  fprintf(stderr, "integer_length(%ld) ", x);
  fflush(stderr);
#endif

  register size_t l = 0;

  while(x > 0) {
    x /= 10;
    l++;

    if(!x)
      break;
  }

#ifdef DEBUG_FUNCS
  fprintf(stderr, " = %u\n", l);
#endif

  return l;
}
