#include"strglob.h"

/*! @fn char *cons_float2str(const float aflt)
 *
 *  @brief make a zero terminated string from a given floating point value
 *
 *  @param [in] aflt the floating point value to create a C-style string from
 *
 *  @return the newly created string representation of the floating point value
 *
 */

char *cons_float2str(const float aflt) {
  char *astr = malloc(2);

  if(!astr)
    exit_verbose("malloc", __FILE__, __LINE__);

  astr[0] = aflt;
  astr[1] = '\0';

  return astr;
}
