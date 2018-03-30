#include"strglob.h"

char **imply_range(STR_GLOB *const ughed) {
  assert(ughed);

  register STR_GLOB *const ugptr = ughed;
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
