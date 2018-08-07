#include"strglob.h"

/*! @fn int **cons_glob2ints(STR_GLOB *stgl)
 *
 *  @param [in] stgl the head element of the glob list 
 *
 *  @return an array of integer arrays containing whole number sequences from 1 to that element's `tot` member
 *
 *  @brief compute an integer array corresponding to each glob list element
 *
 *  @details create an array based on the tot element of each glob list element
 *
 *  @see enum_intseq
 */

int **cons_glob2ints(STR_GLOB *stgl) {
  register STR_GLOB *restrict stgp = stgl;
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
