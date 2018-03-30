#include"strglob.h"

/* convert strglob to string arrays */

char ***conv_gl2sas(STR_GLOB *sglo) {
  assert(sglo);

  register STR_GLOB *sglp = sglo;
  register int innk = 0; /* inner count */
  char ***aret = NULL;

  while(sglp) {
    sglp = sglp->next;

    innk++;
  }

  aret = malloc((innk + 1) * sizeof *aret);

  if(!aret)
    exit_verbose("malloc", __FILE__, __LINE__);

  aret[innk] = NULL;
  sglp = sglo;
  innk = 0;
  
  while(sglp) {
    aret[innk++] = sglp->out;
    sglp = sglp->next;
  }

  return aret;
}
