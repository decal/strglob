#include"strglob.h"

/* if the string class ends in a 'z', then don't include the weekend days */
static char *stype_strs[] = { "wdays", "Wdays", "WDAYS", "weekdays", "Weekdays", "WEEKDAYS", "wdayz", "Wdayz", "WDAYZ", "weekdayz", "Weekdayz", "WEEKDAYZ" };
static char *wdays_strs[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL };
static char *Wdays_strs[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL };

int string_class(const char *sclnm, STR_GLOB *urglb) {
  int invalid_class = 1;

  for(register char **snp = stype_strs;*snp;++snp) {
    if(!strcmp(*snp, sclnm)) {
      invalid_class = 0;

      break;
    }
  }

  if(invalid_class)
    return 1;

  urglb->type = 5;

  if(!strcmp(sclnm, "wdays")) {
    urglb->out = malloc(8 * sizeof *(urglb->out));

    if(!urglb->out)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char **pp = urglb->out;
    register char **wp = wdays_strs;

    while(*wp)
      *pp++ = *wp++;

    pp[7] = NULL;
  } else if(!strcmp(sclnm, "Wdays")) {
    urglb->out = malloc(8 * sizeof *(urglb->out));

    if(!urglb->out)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char **pp = urglb->out;
    register char **wp = Wdays_strs;

    while(*wp)
      *pp++ = *wp++;

    pp[7] = NULL;
  }

  return 0; 
}
