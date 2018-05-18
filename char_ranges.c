#include"strglob.h"

/*! @fn void char_ranges(CHAR_RANGE *crang, STR_GLOB *restrict ugcrn)
 *
 *  @brief create an array of strings for each byte in the desired (possibly pre-defined) character range
 *
 *  @details the `out` member of the `ugcrn` structure is assigned an array of strings instead of a value being returned
 *
 *  @param [in] crang structure containing the start and end of the character range
 *
 *  @param [out] ugcrn the current element of the glob string's linked list that is being operated on
 *
 */

void char_ranges(const CHAR_RANGE *const crang, STR_GLOB *restrict ugcrn) {
  assert(crngs);
  assert(ugcrn);

  register size_t szrgs = 1;

  for(register const CHAR_RANGE *crs = crang;crs && crs->sta;++crs) {
    szrgs += (crs->fin - crs->sta);
    szrgs++;
  }

  ugcrn->out = malloc(szrgs * sizeof(*(ugcrn->out)));

  if(!ugcrn->out)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char **pp = ugcrn->out;

  for(register const CHAR_RANGE *crp = crang;crp && crp->sta;++crp)
    for(register int c = crp->sta;c <= crp->fin;++c) {
      *pp++ = cons_char2str(c);
    }

  *pp = NULL;

  return;
}
