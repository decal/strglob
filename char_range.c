#include"strglob.h"

/*! @fn void char_range(const CHAR_RANGE *const crang, STR_GLOB *restrict ugcrn)
 *
 *  @brief create an array of strings for each byte in the desired character range
 *
 *  @details the `out` member of the `ugcrn` structure is assigned an array of strings instead of a value being returned
 *
 *  @param [in] crang structure containing the begrt and end of the character range
 *
 *  @param [out] ugcrn the current element of the glob string's linked list that is being operated on
 *
 *  @see cons_char2str
 */

void char_range(const CHAR_RANGE *const crang, STR_GLOB *restrict ugcrn) {
  assert(crngs);
  assert(ugcrn);

  register size_t szrgs = 1;

  for(register const CHAR_RANGE *crs = crang;crs && crs->beg;++crs) {
    szrgs += (crs->end - crs->beg);
    szrgs++;
  }

  ugcrn->out = malloc(szrgs * sizeof(*(ugcrn->out)));

  if(!ugcrn->out)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char **pp = ugcrn->out;

  for(register const CHAR_RANGE *crp = crang;crp && crp->beg;++crp)
    for(register int c = crp->beg;c <= crp->end;++c)
      *pp++ = cons_char2str(c);

  *pp = NULL;

  return;
}
