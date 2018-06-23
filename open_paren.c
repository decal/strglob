#include"strglob.h"

/*! @fn char *open_paren(char *optr, STR_GLOB *pgpt)
 *
 *  @param [in] optr a pointer to the string location after the left parenthese, i.e. `(`
 *  @param [in] pgpt a pointer to the glob list element currently being handled
 *
 *  @return a pointer to the string location of the matching right parenthese, i.e. `)`
 *
 *  @see open_brace
 *  @see open_bracket
 */

char *open_paren(char *optr, STR_GLOB *pgpt) {
  assert(optr);
  assert(pgpt);

  *optr++ = '\0';
  char *restrict close_paren = strchr(optr, ')');

  if(!close_paren)
    strglob_error("No matching close paren!");

  *close_paren++ = '\0';

  return close_paren;
}
