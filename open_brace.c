#include"strglob.h"

/*! @fn char *open_brace(char *optr, STR_GLOB *pugp)
 *
 *  @brief parse string input after a left curly brace, i.e. `{`
 *
 *  @param [in] optr a pointer to the string location after the left curly brace
 *  @param [in] pugp a pointer to the glob list element currently being handled
 *
 *  @return a pointer to the string location of the matching right curly brace, i.e. `}`
 *
 *  @see open_bracket
 *  @see open_paren
 */

char *open_brace(char *optr, STR_GLOB *pugp) {
  assert(optr);
  assert(pugp);

  *optr++ = '\0';
  char *restrict close_brace = strchr(optr, '}');

  if(!close_brace)
    strglob_error("No matching close brace!");

  *close_brace++ = '\0';

  char *restrict first_comma = strchr(optr, ',');

  if(!first_comma) {
    char *restrict open_colon = strchr(optr, ':');

    if(!open_colon) {
      char *restrict dash_delim = strchr(optr, '-');

      if(!dash_delim)
        strglob_error("No comma, colon or dash inside curly braces!");

      *dash_delim++ = '\0';
    } else {
      *open_colon++ = '\0';

      char *restrict close_colon = strchr(open_colon, ':');

      if(!close_colon)
        strglob_error("No closing colon after opening colon inside curly braces!");

      *close_colon++ = '\0';

      if(string_class(open_colon, pugp))
        strglob_error("No matching string class found!");
    }

    return close_brace;
  }

  const size_t acnt = 2 + count_commas(optr);
  char **pp = malloc(acnt * sizeof(*(pugp->out)));

  if(!pp)
    exit_verbose("malloc", __FILE__, __LINE__);

  pugp->out = pp;
  pugp->type = 3; /* set */

  do {
    char *restrict next_comma = strchr(optr, ',');

    if(!next_comma) {
      *pp++ = optr;

      break;
    }

    *next_comma++ = '\0';
    *pp++ = optr;
    optr = next_comma;
  } while(1);

  *pp = '\0';

  return close_brace;
}
