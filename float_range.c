#include"strglob.h"

/*! 
 *  @fn void float_range(const FLOAT_RANGE *const frang, STR_GLOB *restrict ugfrn)
 *
 *  @brief create a `float` array for each value in the desired floating point range
 *
 *  @details the `out` member of the `ugfrn` structure is assigned an array of strings instead of a value being returned
 *
 *  @param [in] frang structure containing the begrt and end of the floating-point range
 *  @param [out] ugfrn the current element of the glob string's linked list that is being operated on
 *
 *  @see cons_float2str
 */

void float_range(const FLOAT_RANGE *const frang, STR_GLOB *restrict ugfrn) {
  assert(frang);
  assert(ugfrn);

  register size_t szrgs = 1;

  for(register const FLOAT_RANGE *frs = frang;frs && frs->beg;++frs) {
    szrgs += (frs->end- frs->beg);
    szrgs++;
  }

  ugfrn->out = malloc(szrgs * sizeof(*(ugfrn->out)));

  if(!ugfrn->out)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char **pp = ugfrn->out;

  for(register const FLOAT_RANGE *frp = frang;frp && frp->beg;++frp)
    for(register int c = frp->beg;c <= frp->end;++c)
      *pp++ = cons_float2str(c);

  *pp = NULL;

  return;
}
