#include"strglob.h"

char **array_range(STR_GLOB *ughed) {
#ifdef DEBUG_STRGLOB
  fputs("Entering array_range()\n",    
#endif

  assert(ughed);

  register PSTR_GLOB ugptr = ughed;
  register long nm = 0;
  size_t rngln = ugptr->end - ugptr->beg;
  char **pp = malloc(++rngln * sizeof(*pp));

  if(!pp)
    perror("malloc");

  ugptr->out = pp;

/* #pragma omp parallel for */
  for(nm = ugptr->beg;nm <= ugptr->end;nm++) {
    size_t vlen = integer_length(nm);
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
