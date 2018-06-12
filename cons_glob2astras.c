#include"strglob.h"

/*! @fn char ***cons_glob2astras(STR_GLOB *sglo)
 *
 *  @brief collect each glob element's `out` member into an array 
 *
 *  @param [in] sglo a pointer to the head element of the glob list
 *
 *  @return an array of string arrays constructed from the glob list's `out` members
 */

char ***cons_glob2astras(STR_GLOB *sglo) {
  assert(sglo);

  register STR_GLOB *sglp = sglo;
  register int innk = 1; /* inner count */
  char ***aret = NULL;

  while(sglp) {
    sglp = sglp->next;

    innk++;
  }

  aret = malloc(innk * sizeof *aret);

  if(!aret)
    exit_verbose("malloc", __FILE__, __LINE__);

  aret[--innk] = NULL;
  sglp = sglo;
  innk = 0;
  
  while(sglp) {
    aret[innk++] = sglp->out;
    sglp = sglp->next;
  }

  return aret;
}
