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
    char *next_syntax = strpbrk(input_ptr, "[{");

    if(!next_syntax) {
      input_ptr = next_string(input_ptr, pugp);

#ifdef DEBUG_STRGLOB
      fprintf(stderr, "Inside !next_syntax if block! input_ptr: %p pugp: %p\n", input_ptr, pugp);
#endif
      
      break;
    }

    const char char_syntax = *next_syntax;
    *next_syntax = '\0';

    if(next_syntax != input_ptr) {
      input_ptr = next_string(input_ptr, pugp);
      pugp->next = calloc(1, sizeof *(pugp->next));

      if(!pugp->next)
        perror("calloc");

#ifdef DEBUG_STRGLOB
      fprintf(stderr, "STR_GLOB calloc#1: pugp: %p pugp->next: %p\n", (unsigned int)pugp, (unsigned int)pugp->next);
#endif

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

#ifdef DEBUG_STRGLOB
      fprintf(stderr, "STR_GLOB calloc#2 pugp: %p pugp->next: %p\n", (unsigned int)pugp, (unsigned int)pugp->next);
#endif

    pugp = pugp->next;
  }

  init_strglob(pghd);

  return pghd;
}
