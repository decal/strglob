#include"strglob.h"

/*! @fn STR_GLOB *init_strglob(STR_GLOB *restrict ugpnt)
 *
 *  @brief initialize the glob list prior to utilizing its output
 *
 *  @param [in] ugpnt a pointer to the head element of the glob list
 *  
 *  @return the only argument that was passed as its original type
 *
 *  @note this function invokes `imply_range` if an element's `out` member is `NULL`
 *
 *  @see imply_float_range
 *
 *  @see imply_range
 */

/* 1 = integer range
 * 2 = character range
 * 3 = set
 * 4 = character class
 * 5 = string 
 * 6 = float
 */

STR_GLOB *init_strglob(STR_GLOB *restrict ugpnt) {
  while(ugpnt) {
    if(!ugpnt->type) { 
    } else if(ugpnt->type == 4) { /* character class */
    } else if(ugpnt->type == 3) { /* set */
    } else { /* integer, character or floating-point range */
      if(!ugpnt->out) {
        if(ugpnt->type == 6) {
          if(ugpnt->runi.frng.inc == 0.0)
            ugpnt->runi.frng.inc = 1.0;

          ugpnt->out = imply_float_range(ugpnt);
        }
        else
          ugpnt->out = imply_range(ugpnt);
      }
    }

    if(ugpnt->out) {
      register char **opp = ugpnt->out;

      while(*opp++);

      ugpnt->tot = opp - ugpnt->out;
    }

    ugpnt = ugpnt->next;
  }

  return ugpnt;
}
