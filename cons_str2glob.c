#include"strglob.h"

/**
 * @fn STR_GLOB *cons_str2glob(const char *istr)
 *
 * @brief construct glob linked list from the given string
 *
 * @param [in] istr an input string that possibly contains one or more glob patterns
 *
 * @return a glob list representing the provided string after wildcard expansion
 *
 */

STR_GLOB *cons_str2glob(const char *istr) {
  register STR_GLOB *restrict pugp = NULL, *restrict pghd = NULL;
  const char *input_ptr = NULL;

  pghd = calloc(1, sizeof *pghd);

  if(!pghd)
    exit_verbose("calloc", __FILE__, __LINE__);

  pugp = pghd;
  input_ptr = istr;

  while(input_ptr && *input_ptr) {
    char *next_group = strchr(input_ptr, '('); 

    if(next_group) {
      *next_group++ = '\0';

      input_ptr = open_paren(next_group, pugp);
    }

    char *next_syntax = strpbrk(input_ptr, "[{");

    if(!next_syntax) {
      input_ptr = next_string(input_ptr, pugp);
      
      break;
    }

    const char char_syntax = *next_syntax;
    *next_syntax = '\0';

    if(next_syntax != input_ptr) {
      input_ptr = next_string(input_ptr, pugp);
      pugp->next = calloc(1, sizeof *(pugp->next));

      if(!pugp->next)
        perror("calloc");

      pugp = pugp->next;
    }

    if(char_syntax == '[')
      input_ptr = open_bracket(next_syntax, pugp);
    else if(char_syntax == '{')
      input_ptr = open_brace(next_syntax, pugp);
    else if(char_syntax == '(')
      input_ptr = open_paren(next_syntax, pugp);

    pugp->next = calloc(1, sizeof *(pugp->next));

    if(!pugp->next)
      perror("calloc");

    pugp = pugp->next;
  }

  init_strglob(pghd);

  return pghd;
}
