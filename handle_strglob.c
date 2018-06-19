#include"strglob.h"

HAND_GLOB *handle_strglob(const char *apat) {
  STR_GLOB *pugh = cons_str2glob(apat);
  int **const sets = cons_glob2ints(pugh);
  int *const lens = calc_setlens(sets);
  int *lp = lens;
  size_t asiz = 1;

  if(lp) {
    while(*lp != -1)
      lp++;

    asiz += (lp - lens);
  }

  int *cset = malloc(asiz * sizeof *cset);

  if(!cset)
    exit_verbose("malloc", __FILE__, __LINE__);

  HAND_GLOB *ahnd = malloc(sizeof *ahnd);

  if(!ahnd)
    exit_verbose("malloc", __FILE__, __LINE__);

  auto signed int anindex = 0;
  auto signed int **results = 0;

  ahnd->carp = cartesian_product(sets, lens, cset, asiz--, 0, &results, &anindex);
  ahnd->carp = results;
  ahnd->glob = pugh;
  ahnd->size = asiz;

  return ahnd;
}
