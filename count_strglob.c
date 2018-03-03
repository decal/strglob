#include"strglob.h"

size_t count_strglob(STR_GLOB *ugpnt) {
#ifdef DEBUG_STRGLOB
  fputs("Entering count_strglob()\n", stderr);
#endif

  register size_t aret = 0;

  while(ugpnt) {
    if(ugpnt->end) {
      const size_t distance = ugpnt->end - ugpnt->beg;

      aret += distance;
    } else {
      aret++;
    }

    ugpnt = ugpnt->next;
  }

  return aret;
}
