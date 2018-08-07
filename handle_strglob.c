#include"strglob.h"

/*! @fn HAND_GLOB *handle_strglob(const char *apat)
 *
 * @brief create new handle from provided string that contains glob pattern
 *
 * @return pointer to a newly created handle data structure
 *
 * @see fputs_strglob
 */

HAND_GLOB *handle_strglob(const char *apat) {
  STR_GLOB *const pugh = cons_str2glob(apat);
  int **const sets = cons_glob2ints(pugh);
  int *const lens = calc_setlens(sets);
  const int *lp = lens;
  size_t asiz = 1;

  if(lp) {
    while(*lp > 0)
      lp++;

    asiz += (lp - lens);
  }

  int *cset = malloc(asiz * sizeof *cset);

  if(!cset)
    exit_verbose("malloc", __FILE__, __LINE__);

  HAND_GLOB *const ahnd = malloc(sizeof *ahnd);

  if(!ahnd)
    exit_verbose("malloc", __FILE__, __LINE__);

  int *anindex = malloc(sizeof*anindex);

  if(!anindex)
    exit_verbose("malloc", __FILE__, __LINE__);

  *anindex = 0;

  int ***results = malloc(sizeof**results);

  if(!results)
    exit_verbose("malloc", __FILE__, __LINE__);

  *results = NULL;

  ahnd->carp = cartesian_product(sets, lens, cset, asiz--, 0, results, anindex);
  ahnd->carp = *results;
  ahnd->glob = pugh;

#ifdef DEBUG_STRGLOB
  fprintf(stderr, "handle_strglob done! ahnd->size: %d\n", ahnd->size);
#endif

  ahnd->size = asiz;

  return ahnd;
}
