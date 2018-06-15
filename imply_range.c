#include"strglob.h"

/*! @fn char **imply_range(STR_GLOB *const ugcur)
 *
 *  @brief create an array of strings defined by the glob list elements' `beg` and `end` members
 *
 *  @details depending upon the `type` and `zlen` members of `ugcur`, the created string array can consist of
 *  alphabetic, numeric or padded numeric strings. For example, if `type` is equal to `2` then alphabetic 
 *  (i.e. single character) strings will be created.  If `zlen` is non-zero then numeric strings which are
 *  padded with the number of zeroes defined by `zlen` are created (like `0001` if `zlen` is `3`.) Otherwise,
 *  an array of unpadded numeric strings is created.
 *
 *  @param [in] ugcur the element of the glob list to operate on
 *
 *  @return an array of strings containing a range of characters or numbers
 */

static inline int lteq(const intmax_t a, const intmax_t b) {
  return a <= b;
}

static inline int gteq(const intmax_t x, const intmax_t y) {
  return x >= y;
}
 
char **imply_range(STR_GLOB *const ugcur) {
  assert(ugcur);

  register STR_GLOB *const ugptr = ugcur;
  const intmax_t lo = ugcur->runi.crng.beg, hi = ugcur->runi.crng.end;
  register intmax_t nm = 0, in = ugcur->runi.crng.inc;
  size_t rngln = 1 + ugptr->runi.crng.end - ugptr->runi.crng.beg;
  int (*fp)(const intmax_t, const intmax_t) = lteq;
  bool nopre = true; /* no prepend */

  if(lo < 0 || hi < 0)
    nopre = false;

  if(lo > hi) { /* determine the increment direction (important for support of signed integer ranges) */
    if(in > 0)
      in = -in;

    fp = gteq;
    rngln = 1 + ugptr->runi.crng.beg - ugptr->runi.crng.end;
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

      rpt[0] = (char) nm;
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
        sprintf(&rpt[ugptr->zlen - vlen], "%ld", (long) nm);
      else
        sprintf(&rpt[ugptr->zlen - vlen], "%d", (int) nm);
#else
      sprintf(&rpt[ugptr->zlen - vlen], "%ld", (long) nm);
#endif
    } else {
      rpt = malloc(++vlen);

      if(!rpt)
        exit_verbose("malloc", __FILE__, __LINE__);

      sprintf(rpt, "%ld", (long) nm);
    }

    *pp++ = rpt;
  }

  *pp = NULL;

  return ugptr->out;
}
