#include"strglob.h"

/* convert strglob to integer arrays */

int **conv_gl2ias(STR_GLOB *stgl) {
  register STR_GLOB *stgp = stgl;
  register size_t innx = 1; /* inner count */
  int **pias = NULL;

  while(stgp) {
    innx++;
    stgp = stgp->next;

  }

  pias = malloc(innx * sizeof *pias);

  if(!pias)
    exit_verbose("malloc", __FILE__, __LINE__);

  stgp = stgl;
  innx = 0;
  
  while(stgp) {
    pias[innx++] = enum_intseq(stgp->tot);
    stgp = stgp->next;
  }

  pias[innx] = 0;

  return pias;
}
