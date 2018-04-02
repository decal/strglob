#include"strglob.h"

/*! @fn size_t measure_integer(long int x)
 * 
 *  @brief counts the number of digits in the supplied integer
 *
 *  @details this function computes the number of bytes that need to be allocated when storing
 *  the integer value as a string (without counting the terminating zero character.)
 *
 *  @param [in] x 
 *
 *  @return number of digits needed to represent the given integer
 */

size_t measure_integer(long int x) {
  register size_t l = 0;

  while(x > 0) {
    x /= 10;
    l++;

    if(!x)
      break;
  }

  return l;
}
