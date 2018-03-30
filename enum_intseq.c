#include"strglob.h"

int *enum_intseq(const size_t amax) {
  int *enmb = malloc((amax + 1) * sizeof *enmb);
  register int *restrict pint = enmb, xint = 0;

  if(!enmb)
    exit_verbose("calloc", __FILE__, __LINE__);

  while(xint < amax)
    *pint++ = xint++;

  *pint = -1;

  return enmb;
}
