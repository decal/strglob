#include"strglob.h"

/*! @fn size_t count_commas(const char *capt
 *
 *  @brief count the number of commas in the provided string
 *
 *  @param [in] capt 
 *
 *  @return the total number of commas in the provided string 
 *
 */

size_t count_commas(const char *capt) {
  register size_t r = 1;

  do {
    char *const acomma = strchr(capt, ',');

    if(!acomma)
      break;

    r++;

    capt = 1 + acomma;
  } while(1);

  return r;
}
