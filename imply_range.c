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
 
char **imply_range(STR_GLOB *const ugcur) {
  assert(ugcur);

  register STR_GLOB *const ugptr = ugcur;
  register long nm = 0;
  size_t rngln = 1 + ugptr->end - ugptr->beg;
  char **pp = malloc(++rngln * sizeof(*pp));

  if(!pp)
    perror("malloc");

  ugptr->out = pp;

/* #pragma omp parallel for */
  for(nm = ugptr->beg;nm <= ugptr->end;nm++) {
    size_t vlen = measure_integer(nm);
    char *rpt = NULL;

    if(ugptr->type == 2) {
      rpt = malloc(2);

      if(!rpt)
        perror("malloc");

      rpt[0] = (char)nm;
      rpt[1] = '\0';
    } else if(ugptr->zlen > vlen) {
      rpt = malloc(1 + ugptr->zlen);

      if(!rpt)
        perror("malloc");

      memset(rpt, '0', ugptr->zlen);

      sprintf(&rpt[ugptr->zlen - vlen], "%ld", nm);
    } else {
      rpt = malloc(++vlen);

      if(!rpt)
        perror("malloc");

      sprintf(rpt, "%ld", nm);
    }

    *pp++ = rpt;
  }

  *pp = NULL;

  return ugptr->out;
}
