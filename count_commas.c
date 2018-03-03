#include"strglob.h"

size_t count_commas(const char *capt) {
#ifdef DEBUG_STRGLOB
  fputs("Entering count_commas()\n", capt);
#endif

  register size_t r = 1;

  do {
    char *const acomma = strchr(capt, ',');

    if(!acomma)
      break;

    r++;

    capt = 1 + acomma;
  } while(1);

  return r;
}
