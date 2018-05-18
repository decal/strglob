#include"strglob.h"

/*! @fn void init_strglob(STR_GLOB *restrict ugpnt)
 *
 *  @brief initialize the glob list prior to utilizing its output
 *
 *  @param [in] ugpnt a pointer to the head element of the glob list
 *
 *  @note this function invokes `imply_range` if an element's `out` member is `NULL`
 *
 *  @see imply_range
 */

void init_strglob(STR_GLOB *restrict ugpnt) {
  while(ugpnt) {
    if(!ugpnt->type) { 
    } else if(ugpnt->type == 4) { /* character class */
    } else if(ugpnt->type == 3) { /* set */
    } else { /* integer or character range */
      if(!ugpnt->out)
        ugpnt->out = imply_range(ugpnt);
    }

    if(ugpnt->out) {
      register char **opp = ugpnt->out;

      while(*opp++);

      ugpnt->tot = opp - ugpnt->out;
    }

    ugpnt = ugpnt->next;
  }

  return;
}
