#include"strglob.h"

/*! @fn int *enum_intseq(const size_t amax)
 *
 *  @brief create an ordered set (array) of natural numbers that ranges from 0 to the given maximum value
 * 
 *  @param [in] amax the maximum and final value of the ordered set
 *
 *  @return the array that was created containing the range from 0 to `amax`
 *
 *  @note the array is terminated with -1
 *
 */

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
