#include"strglob.h"

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
