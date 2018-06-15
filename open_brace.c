#define _ISOC99_SOURCE 1

#include"strglob.h"

/*! @fn char *open_brace(char *optr, STR_GLOB *restrict pugp)
 *
 *  @brief parse string input after a left curly brace, i.e. `{`
 *
 *  @param [in] optr a pointer to the string location after the left curly brace
 *
 *  @param [out] pugp a pointer to the glob list element currently being handled
 *
 *  @return a pointer to the string location of the matching right curly brace, i.e. `}`
 *
 *  @see open_bracket
 *
 *  @see open_paren
 */

char *open_brace(char *optr, STR_GLOB *restrict pugp) {
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

    if(!open_colon) { /** TODO: get rid of dash delim? */
        char *restrict twodots1 = strstr(optr, "..");

        if(twodots1) {
          *twodots1 = '\0';

          twodots1 += 2;

          if(strchr(optr, '.')) {
            const float fbeg = strtof(optr, NULL), fend = strtof(twodots1, NULL);
            char *restrict twodots2 = strstr(twodots1, "..");
            float finc = 1.0;

            if(errno == ERANGE)
              strglob_error("Erroneous floating point range!");

            if(twodots2) {
              *twodots2 = '\0';

              twodots2 += 2;

              if(!*twodots2)
                strglob_error("Empty floating point increment value!");

              finc = strtof(twodots2, NULL);

              if(errno == ERANGE)
                strglob_error("Erroneous floating point increment value!");
            }

            pugp->runi.frng.beg = fbeg;
            pugp->runi.frng.end = fend;
            pugp->runi.frng.inc = finc;
            pugp->type = 6; /* float range */
          } else {
            char *restrict twodots2 = strstr(twodots1, "..");
            intmax_t ainc = 1;

            if(twodots2) {
              *twodots2 = '\0';
              twodots2 += 2;

              if(!*twodots2)
                strglob_error("Empty alphanumeric increment value!");

              ainc = strtoimax(twodots2, NULL, 0xA);

              if(errno == ERANGE)
                  strglob_error("Erroenous alphanumeric increment value!");
            }

            if(*optr == '+')
              optr++;

            if(*optr == '-' || isdigit(*optr)) {
              pugp->runi.crng.beg = strtoimax(optr, NULL, 0xA);

              if(errno == ERANGE)
                strglob_error("Erroneous integer range start value!");

              if(*twodots1 != '-' && *twodots1 != '+' && !isdigit(*twodots1))
                strglob_error("Integer range finish value must begin with a numeric digit or sign!");

              pugp->runi.crng.end = strtoimax(twodots1, NULL, 0xA);

              if(errno == ERANGE)
                strglob_error("Erroneous integer range finish value!");

              pugp->type = 1; /* integer range */
            } else {
              pugp->runi.crng.beg = *optr;
              pugp->runi.crng.end = *twodots1;
              pugp->type = 2; /* character range */
            }

            pugp->runi.crng.inc = ainc;

            return close_brace;
          }
        } else {
#ifdef STRGLOB_ENVIRON_EXPAND
          if(*optr == '$') {
            optr++;

            char *const aenv = getenv(optr);

            pugp->out = malloc(2 * sizeof(*(pugp->out)));

            if(!pugp->out)
              exit_verbose("malloc", __FILE__, __LINE__);

            if(!aenv)
              pugp->out[0] = "";
            else
              pugp->out[0] = aenv;

            pugp->out[1] = NULL;
          } else {
#endif
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
                pugp->type = 3; /* set */
                pugp->out = lptr;
              } else 
                  exit_verbose("fopen", __FILE__, __LINE__);
            } else { /* empty file, so create empty string array */
              char **const ep = malloc(sizeof(*(pugp->out)));

              if(!ep)
                exit_verbose("malloc", __FILE__, __LINE__);

              *ep = NULL;
              pugp->type = 3; /* set */
              pugp->out = ep;
            }
#else
              strglob_error("No comma, colon, dash or dot-dot inside curly braces!");
#endif

#ifdef STRGLOB_ENVIRON_EXPAND
          }
#endif
        }

      return open_colon;
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
  } while(true);

  *pp = '\0';

  return close_brace;
}
