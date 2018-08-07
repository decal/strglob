#include"strglob.h"

/*! 
 *  @fn char *cons_float2str(const float aflt)
 *
 *  @brief make a zero terminated string from a given floating point value
 *
 *  @param [in] aflt the floating point value to create a C-style string from
 *
 *  @return the newly created string representation of the floating point value
 *
 */

char *cons_float2str(const float aflt) {
  const size_t fsiz = measure_float(aflt);
  char *fbuf = malloc(1 + fsiz);

  if(!fbuf)
    exit_verbose("malloc", __FILE__, __LINE__);

  sprintf(fbuf, "%f", aflt);

  return fbuf;
}
