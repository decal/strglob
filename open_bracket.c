#include"strglob.h"

/*! @fn char *open_bracket(char *aptr, STR_GLOB *const uglo)
 *
 *  @brief parse string input after a left square brace, i.e. `[`
 *
 *  @param [in] aptr a pointer to the string location after the left square brace
 *  @param [in] uglo a pointer to the glob list element currently being handled
 *
 *  @return a pointer to the string location of the matching right square brace, i.e. `]`
 *
 *  @see open_brace
 *  @see open_paren
 */

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

  /* if(aptr == dash_delim)
    strglob_error("Dash delimiter appears to soon after open bracket! (Note: negative integers unsupported..)");  */

  if(aptr == dash_delim) {
    dash_delim = strchr(aptr + 1, '-');

    if(!dash_delim)
      strglob_error("Beginning of range is negative, but no dash delimiter!");
  }

  *dash_delim++ = '\0';

  if(*aptr == '-' || isdigit(*aptr)) {
    const size_t relen = strlen(aptr); /* length of range end, in case end is longer, ie. [1-03] */

    if(*aptr == '0' && relen > 1)
      uglo->zlen = relen;

    uglo->type = 1; /* integer range */
    uglo->beg = strtoimax(aptr, 0x0, 0xA);

    if((errno == ERANGE && (uglo->end == LONG_MAX || uglo->end == LONG_MIN)) || (errno && !uglo->beg))
      strglob_error("Error parsing integer range start value!");

    uglo->end = strtoimax(dash_delim, 0x0, 0xA);

    if((errno == ERANGE && (uglo->end == LONG_MAX || uglo->end == LONG_MIN)) || (errno && !uglo->end))
      strglob_error("Error parsing integer range end value!");
  } else {
    uglo->type = 2; /* character range */
    uglo->beg = *aptr;
    uglo->end = *dash_delim;
  }

  return close_bracket;
}
