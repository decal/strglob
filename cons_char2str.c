#include"strglob.h"

/*! @fn char *cons_char2str(const char achr)
 *
 *  @brief make a zero terminated string from a given character
 *
 *  @param [in] achr the character to create a C-style string from
 *
 *  @return the newly created single character string
 *
 */

char *cons_char2str(const char achr) {
  char *astr = malloc(2);

  if(!astr)
    exit_verbose("malloc", __FILE__, __LINE__);

  astr[0] = achr;
  astr[1] = '\0';

  return astr;
}
