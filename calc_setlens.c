#include"strglob.h"

int *calc_setlens(int **setz) {
  int *r = NULL;

  register int **ip = setz;

  while(*ip++);

  size_t alen = ip - setz;

  r = malloc(++alen * sizeof *r);

  if(!r)
    exit_verbose("malloc", __FILE__, __LINE__);

  register int k = 0;
  for(;k < alen;++k) {
    register int j = 0;

    if(!setz[k])
      break;

    while(setz[k][j] != -1)
      j++;

    r[k] = --j;
  }

  r[k] = -1;

  return r;
}
