#include"strglob.h"

/*! @fn int *calc_setlens(int **setz)
 *
 *  @brief calculate integer array lengths
 *
 *  @param [in] setz the array containing the arrays to count lengths of
 *
 *  @return an array of lengths
 *
 *  @note this function detects integer array termination with the value -1
 */

int *calc_setlens(int **setz) {
  register int *restrict *restrict ip = setz;

  while(*ip++);

  size_t alen = ip - setz;

  int *const r = malloc(++alen * sizeof *r);

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
