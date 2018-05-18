#include"strglob.h"

/*! @fn size_t count_commas(const char *cstr)
 *
 *  @brief count the number of commas in the provided string
 *
 *  @param [in] cstr a C-style string containing the comma characters to be counted
 *
 *  @return the total number of commas in the provided string 
 *
 */

size_t count_commas(const char *cstr) {
  register size_t r = 1;

  do {
    char *const acomma = strchr(cstr, ',');

    if(!acomma)
      break;

    r++;

    cstr = 1 + acomma;
  } while(1);

  return r;
}
