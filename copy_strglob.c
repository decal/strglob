#include"strglob.h"

/*! @fn char **copy_strglob(const HAND_GLOB *phnd)
 *
 * @brief create string array representing glob pattern of given handle
 *
 * @summary Construct and walk a linked list constructed from the provided 
 *          handle's glob pattern and copy the strings into an array.  If
 *          any of the pointers referenced under the passed handle are null
 *          or empty or won't produce any string(s), then return NULL.
 *
 * @param [in] phnd pointer to the handle for a glob pattern to copy
 *
 * @return an array of strings generated from the given handle's glob pattern 
 *
 * @see fputs_strglob
 *
 */

char **copy_strglob(const HAND_GLOB *phnd) {
  char **aret = NULL;

  assert(phnd);

  STR_GLOB *const pugx = phnd->glob;
  const size_t size = phnd->size;
  int *const *const carp = phnd->carp;
  char ***kstr = cons_glob2astras(pugx);

  if(!(pugx && size && carp && kstr))
    return aret;

  register int acnt = 0, j = 0;

  for(register int c = 0;carp[c];++c)
    acnt++;

  acnt *= size;
  aret = calloc(++acnt, sizeof*aret);

  if(!aret)
    exit_verbose("calloc", __FILE__, __LINE__);

  for(register int c = 0;carp[c];++c) {
    const int *restrict aind = carp[c];

    if(phnd->size == 1) {
      aret[j++] = strdup(kstr[0][*aind]);
    } else
      for(register int k = 0;k < phnd->size;++k, ++aind) {
        if(!kstr[k] || *aind == -1 || !kstr[k][*aind])
          break;

          aret[j++] = strdup(kstr[k][*aind]);
        }
      }

  return aret;
}
