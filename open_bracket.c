#include"strglob.h"

char *open_bracket(char *aptr, STR_GLOB *const uglo) {
  assert(aptr);
  assert(uglo);

  *aptr++ = '\0';
  char *close_bracket = strchr(aptr, ']');

  if(!close_bracket)
    strglob_error("No matching close bracket!");

  *close_bracket++ = '\0';

  char *restrict dash_delim = strchr(aptr, '-');

  if(!dash_delim) {
    char *restrict first_colon = strchr(aptr, ':');

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

  if(aptr == dash_delim)
    strglob_error("Dash delimiter appears to soon after open bracket! (Note: negative integers unsupported..)");

  *dash_delim++ = '\0';

  if(*aptr == '-' || isdigit(*aptr)) {
    const size_t relen = strlen(aptr); /* length of range end, in case end is longer, ie. [1-03] */

    if(*aptr == '0' && relen > 1)
      uglo->zlen = relen;

    uglo->type = 1; /* integer range */
    uglo->beg = strtol(aptr, 0x0, 0xA);

    if((errno == ERANGE && (uglo->end == LONG_MAX || uglo->end == LONG_MIN)) || (errno && !uglo->beg))
      strglob_error("Error parsing integer range start value!");

    uglo->end = strtol(dash_delim, 0x0, 0xA);

    if((errno == ERANGE && (uglo->end == LONG_MAX || uglo->end == LONG_MIN)) || (errno && !uglo->end))
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
