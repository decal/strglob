#include"strglob.h"

void init_strglob(STR_GLOB *restrict ugpnt) {
  int is_init = 0;

  while(ugpnt) {
    if(!ugpnt->type) { /* outp and strp will remain NULL */
    } else if(ugpnt->type == 4) { /* character class, strp = str, outp = NULL */
      ugpnt->strp = ugpnt->str;

      if(!is_init)
        is_init = 1;
    } else if(ugpnt->type == 3) { /* set */
      ugpnt->outp = ugpnt->out;

      if(!is_init)
        is_init = 1;
    } else { /* integer or character range */
      if(!ugpnt->out)
        ugpnt->out = array_range(ugpnt);

      ugpnt->outp = ugpnt->out;

      if(!is_init)
        is_init = 1;
    }

    ugpnt = ugpnt->next;
  }

  return;
}
