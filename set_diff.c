#include"strglob.h"

/*! @fn void set_diff(STR_GLOB *seta, STR_GLOB *setb)
 *
 *  @brief a C function version of the set difference operation from discrete mathematics
 *
 *  @param [in] seta the glob list element to check for characters that are in `setb`
 *  @param [in] setb the glob list element to check for characters that are not in `seta`
 *
 *  @return a string containing the characters that are in `setb`, but not in `seta`
 *
 *  @see https://wikipedia.org/wiki/Set_difference
 */ 

char *set_diff(STR_GLOB *seta, STR_GLOB *setb) {
  assert(seta);
  assert(setb);

  register char *restrict psa = seta->str, *restrict psb = setb->str;

  if(!(psa && psb))
    strglob_error("set_diff passed string glob list element without a string member!");

  const size_t alen = strlen(seta->str), blen = strlen(setb->str);
  size_t xlen = alen - blen;
  char *xbuf = malloc(++xlen);

  if(!xbuf)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char *restrict psx = xbuf;

  while(*psb)
    if(!strchr(setb->str, *psb))
      *psx++ = *psb++;
    else
      psb++;

  *psx = '\0';

  /* seta->str = xbuf; */

  return xbuf;
}
