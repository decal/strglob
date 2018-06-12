#include"strglob.h"

/*! @fn char **imply_float_range(STR_GLOB *const ugcur)
 *
 *  @brief create an array of floats defined by the glob list elements' `begf` and `endf` members
 *
 *  @details depending upon the `type` and `zlen` members of `ugcur`, the created string array can consist of
 *  alphabetic, numeric or padded numeric strings. For example, if `type` is equal to `2` then alphabetic 
 *  (i.e. single character) strings will be created.  If `zlen` is non-zero then numeric strings which are
 *  padded with the number of zeroes defined by `zlen` are created (like `0001` if `zlen` is `3`.) Otherwise,
 *  an array of unpadded numeric strings is created.
 *
 *  @param [in] ugcur the element of the glob list to operate on
 *
 *  @return an array of stings representing a range of floating-point values
 */

static inline int lteq(const float a, const float b) {
  return a <= b;
}

static inline int gteq(const float x, const float y) {
  return x >= y;
}
 
char **imply_float_range(STR_GLOB *const ugcur) {
  assert(ugcur);

  register STR_GLOB *const ugptr = ugcur;
  register float lo = ugcur->begf, hi = ugcur->endf, nm = 0, in = ugcur->incf;
  size_t rngln = 1 + ugptr->endf - ugptr->begf;
  int (*fp)(const float, const float) = lteq;
  bool nopre = true; /* no prepend */

  if(lo < 0 || hi < 0)
    nopre = false;

  if(lo > hi) { /* determine the increment direction (important for support of signed float ranges) */
    // in = -1;
    in = -in;
    fp = gteq;
    rngln = 1 + ugptr->begf - ugptr->endf;
  } 

  char **pp = malloc(++rngln * sizeof*pp);

  if(!pp)
    exit_verbose("malloc", __FILE__, __LINE__);

  ugptr->out = pp;

/* #pragma omp parallel for */
  for(nm = lo;fp(nm, hi);nm += in) {
    size_t vlen = measure_integer(nm);
    char *rpt = NULL;

    if(ugptr->type == 2) {
      rpt = malloc(2);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      rpt[0] = (char)nm;
      rpt[1] = '\0';
    } else if(nopre && ugptr->zlen > vlen) {
      rpt = malloc(1 + ugptr->zlen);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      if(!nm)
        vlen++;

      memset(rpt, '0', ugptr->zlen - vlen);

#if __WORDSIZE == 64
      if(nm > UINT_MAX)
        sprintf(&rpt[ugptr->zlen - vlen], "%f", (float) nm);
      else
        sprintf(&rpt[ugptr->zlen - vlen], "%f", (float) nm);
#else
      sprintf(&rpt[ugptr->zlen - vlen], "%f", (float) nm);
#endif
    } else {
      rpt = malloc(++vlen);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      sprintf(rpt, "%f", (float) nm);
    }

    *pp++ = rpt;
  }

  *pp = NULL;

  return ugptr->out;
}
