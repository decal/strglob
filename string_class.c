#include"strglob.h"

/* if the string class ends in a 'z', then don't include the weekend days */
static const char *stype_strs[] = { "wdays", "Wdays", "WDAYS", "weekdays", "Weekdays", "WEEKDAYS", "wdayz", "Wdayz", "WDAYZ", "weekdayz", "Weekdayz", "WEEKDAYZ" };
static const char *wdays_strs[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL };
static const char *Wdays_strs[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL };

int string_class(const char *sclnm, STR_GLOB *urglb) {
#ifdef DEBUG_STRGLOB
  fputs("Entering string_class()\n", stderr);
#endif

  int aretboo = 0;

  for(register const char *const *snp = stype_strs;*snp;++snp) {
    if(!strcmp(*snp, sclnm)) {
      aretboo = 1;

      break;
    }
  }

  if(!aretboo)
    strglob_error("Unknown string class given after opening curly brace with colon!");

  urglb->type = 5;

  if(!strcmp(sclnm, "wdays")) {
    urglb->out = malloc(8 * sizeof *(urglb->out));

    if(!urglb->out)
      error_at_line(1, errno, __FILE__, __LINE__, "malloc: %s", strerror(errno));

    register char *restrict *restrict pp = urglb->out;
    register char *restrict *restrict wp = wdays_strs;

    while(*wp)
      *pp++ = *wp++;

    pp[7] = NULL;

#ifdef DEBUG_STRGLOB
    if((wp - urglb->out) != (8 * (sizeof *(urglb->out))))
      fprintf(stderr, "Incorrect number of elements in string class: \"%s\" !\n", sclnm);
#endif
  } else if(!strcmp(sclnm, "Wdays")) {
  }

  return aretboo;
}
