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

      if(!dash_delim) {
        char *restrict dot_dot = strstr(optr, "..");

        if(dot_dot) {
          *dot_dot = '\0';

          dot_dot += 2;

          CHAR_RANGE ranges[] = { { .sta = optr, .fin = dot_dot }, { .sta = 0, .fin = 0 } };

          pugp->type = 3;

          char_ranges(ranges, pugp);
        } else {
#ifdef STRGLOB_FILE_INCLUDES
        size_t nlns = count_lines(optr);

        if(nlns > 0) {
          FILE *fptr = fopen(optr, "r");

          if(fptr) {
            register size_t alin = 0;
            char abuf[BUFSIZ] = { 0x0 };
            char **lptr = malloc(++nlns * sizeof(*(pugp->out)));

            if(!lptr)
              exit_verbose("malloc", __FILE__, __LINE__);

            while(fgets(abuf, sizeof abuf, fptr) && alin < nlns) {
              char *astr = strdup(abuf);

              if(!astr) 
                exit_verbose("strdup", __FILE__, __LINE__);

              char *atok = strpbrk(astr, "\r\n");

              if(atok)
                *atok = '\0'; 

              lptr[alin] = astr;
              alin++;
            }

            lptr[--nlns] = NULL;
            pugp->type = 3;
            pugp->out = lptr;
          } else 
            exit_verbose("fopen", __FILE__, __LINE__);
        } else { /* empty file, so create empty string array */
          char **ep = malloc(sizeof(*(pugp->out)));

          if(!ep)
            exit_verbose("malloc", __FILE__, __LINE__);

          *ep = NULL;

          pugp->type = 3;
          pugp->out = ep;
        }
#else
          strglob_error("No comma, colon, dash or dot-dot inside curly braces!");
#endif
        }
      } else {
        *dash_delim++ = '\0';

        return open_brace;
      }
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
