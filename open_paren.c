#include"strglob.h"

char *open_paren(char *optr, STR_GLOB *pgpt) {
#ifdef DEBUG_STRGLOB
  fputs("Entering open_paren()\n", stderr);
#endif

  assert(optr);
  assert(pgpt);

  *optr++ = '\0';
  char *restrict close_paren = strchr(optr, ')');

  if(!close_paren)
    strglob_error("No matching close paren!");

  *close_paren++ = '\0';

  char *restrict first_group = strpbrk(optr, "{[");

  if(first_group) {
    const char more_syntax = *first_group;

    *first_group++ = '\0';

    if(more_syntax == '[')
      optr = open_bracket(first_group, pgpt);
    else if(more_syntax == '{')
      optr = open_brace(first_group, pgpt);

    char *restrict binary_oper = strpbrk(optr, "-^+");

    if(binary_oper) {
      const char binop_char = *binary_oper;

      *binary_oper++ = '\0';
      optr = binary_oper;

      char *restrict second_group = strpbrk(optr, "{[");

      if(second_group) {
        const char most_syntax = *second_group;
        STR_GLOB *aglob = calloc(1, sizeof *aglob);

        if(!aglob)
          exit_verbose("malloc", __FILE__, __LINE__);

        *second_group++ = '\0';

        if(most_syntax == '[')
          optr = open_bracket(second_group, aglob);
        else if(most_syntax == '{')
          optr = open_brace(second_group, aglob);

        switch(binop_char) {
          case '-':
            set_difer(pgpt, aglob);

            break;
          case '^':
            dis_union(pgpt, aglob);

            break;
          case '+':
            set_union(pgpt, aglob);

            break;
          default:
            strglob_error("Invalid binary operator detected!");

            break;
        } /* switch */

        if(*optr != ')')
          strglob_error("Expected closing parenthese character!");
      } /* if(second_group) */
    } /* if(binary_oper) */
  } /* if(first_group) */

  return close_paren;
}
