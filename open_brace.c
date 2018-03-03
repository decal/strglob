#include"strglob.h"

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

      char *restrict start_string = optr;
      char *restrict end_string = dash_delim;
    } else {
      *open_colon++ = '\0';

      char *restrict close_colon = strchr(open_colon, ':');

      if(!close_colon)
        strglob_error("No closing colon after opening colon inside curly braces!");

      *close_colon++ = '\0';

      char *restrict astr_class = open_colon;

      if(!string_class(astr_class, pugp))
        strglob_error("No matching string class found!");
    }

    return close_brace;
  }

  size_t acnt = count_commas(optr);
  char **pp = malloc(++acnt * sizeof(*(pugp->out)));

  if(!pp)
    error_at_line(1, errno, __FILE__, __LINE__, "malloc: %s", strerror(errno));

  pp[--acnt] = '\0';
  pugp->out = pp;
  pugp->type = 3; /* set */

  do {
    char *restrict next_comma = strchr(optr, ',');

    if(!next_comma) {
      *pp = optr;

      break;
    }

    *next_comma++ = '\0';
    *pp++ = optr;
    optr = next_comma;
  } while(1);

  return close_brace;
}
