#include"strglob.h"

/*! 
 *  @fn char **imply_float_range(STR_GLOB *const ugcur)
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
  register float lo = ugcur->runi.frng.beg, hi = ugcur->runi.frng.end, nm = 0, in = ugcur->runi.frng.inc;
  size_t rngln = 2 + ugptr->runi.frng.end - ugptr->runi.frng.beg;
  int (*fp)(const float, const float) = lteq;
  bool nopre = true; /* no prepend */

  if(lo < 0.0 || hi < 0.0)
    nopre = false;

  if(lo > hi) { /* determine the increment direction (important for support of signed float ranges) */
    if(in > 0.0)
      in = -in;

    fp = gteq;
    rngln = 2 + ugptr->runi.frng.beg - ugptr->runi.frng.end;
  } 

  char **pp = malloc(rngln * sizeof*pp);

  if(!pp)
    exit_verbose("malloc", __FILE__, __LINE__);

  ugptr->out = pp;

/* #pragma omp parallel for */
  for(nm = lo;fp(nm, hi);nm += in) {
    size_t vlen = measure_float(nm);
    char *rpt = NULL;

    if(!ugptr->zlen) {
      rpt = malloc(1 + vlen);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      sprintf(rpt, "%f", nm);
    } else if(nopre && ugptr->zlen > vlen) {
      const int places = 2;
      char *rpt = malloc(1 + ugptr->zlen);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      if(nm == 0.0)
        vlen++;

      memset(rpt, '0', ugptr->zlen - vlen);
      sprintf(&rpt[ugptr->zlen - vlen], "%0.*f", places, nm);
    } else {
      const int places = 2;

      rpt = malloc(++vlen);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      sprintf(rpt, "%0.*f", places, nm);
    }

    *pp++ = rpt;
  }

  *pp = NULL;

  return ugptr->out;
}
