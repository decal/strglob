#include"strglob.h"

/*! @fn int fputs_strglob(const HAND_GLOB *phnd, FILE *fstr)
 *
 * @brief Display the strings represented by the given glob pattern
 *
 * @summary Walk the given linked list constructed from a particular glob 
 *          pattern and display the resulting strings on the given file
 *          stream. If the file stream is NULL, then default to standard
 *          output.
 *
 * @param [in] pugx a linked list representing a glob pattern
 * @param [in] size cardinality of cartesian product
 * @param [in] fstr a file stream to write strings constructed from pattern
 *
 */

int fputs_strglob(const HAND_GLOB *phnd, FILE *fstr) {
  assert(phnd);

  register int r = 0;

  STR_GLOB *pugx = phnd->glob;

  assert(pugx);

  if(!fstr)
    fstr = stdout;

  char ***const kstr = cons_glob2astras(pugx);
  int *const *crp = phnd->carp;

  if(kstr && crp)
    for(register int c = 0;crp[c];++c) {
      const int *restrict ind = crp[c];

      if(phnd->size == 1)
        r += fputs(kstr[0][*ind], fstr);
      else
        for(register int k = 0;k < phnd->size;++k, ++ind) {
          if(!kstr[k] || *ind == -1 || !kstr[k][*ind])
            break;

            r += fputs(kstr[k][*ind], fstr);
          }

      putchar('\n');
    }


  return r;
}
