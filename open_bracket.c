#include"strglob.h"

char *open_bracket(char *aptr, STR_GLOB *uglo) {
#ifdef DEBUG_STRGLOB
  fputs("Entering open_bracket()\n", stderr);
#endif

  assert(aptr);
  assert(uglo);

  *aptr++ = '\0';
  char *close_bracket = strchr(aptr, ']');

  if(!close_bracket)
    strglob_error("No matching close bracket!");

  *close_bracket++ = '\0';
  char *dash_delim = strchr(aptr, '-');

  if(!dash_delim) {
    char *first_colon = strchr(aptr, ':');

    if(!first_colon)
      strglob_error("No dash delimiter for range values or colons for character class!");

    if(first_colon) {
      *first_colon++ = '\0';

      char *last_colon = strchr(first_colon, ':');

      if(!last_colon)
        strglob_error("No dash delimiter for range values or colons for character class!");

      *last_colon++ = '\0';

      char_class(first_colon, uglo);

      return close_bracket;
    }

    strglob_error("No dash delimiter between range values!");
  }

  *dash_delim++ = '\0';

  if(isdigit(*aptr)) {
    const size_t relen = strlen(aptr); /* length of range end, in case end is longer, ie. [1-03] */

    if(*aptr == '0' && relen > 1)
      uglo->zlen = relen;

    uglo->type = 1; /* integer range */
    uglo->beg = strtol(aptr, NULL, 0xA);

    if(errno == ERANGE)
      strglob_error("Error parsing integer range start value!");

    uglo->end = strtol(dash_delim, NULL, 0xA);

    if(errno == ERANGE)
      strglob_error("Error parsing integer range end value!");
  } else {
    uglo->type = 2; /* character range */
    uglo->beg = *aptr;
    uglo->end = *dash_delim;
  }

  if(uglo->beg && (uglo->beg > uglo->end))
    strglob_error("Range start must be less than or equal to end value!");

  return close_bracket;
}
