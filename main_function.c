#include"strglob.h"

STR_GLOB *pugh = NULL;

int main(int argc, char *argv[]) {
  if(argc < 2)
    show_usage(*argv);

  pugh = calloc(1, sizeof *pugh);

  if(!pugh)
    perror("calloc");

  register STR_GLOB *pugp = pugh;
  char *restrict input_ptr = argv[1];

  while(input_ptr && *input_ptr) {
    char *next_group = strchr(input_ptr, '(');

    if(next_group) {
#ifdef DEBUG_STRGLOB
      fputs("Handling next group\n", stderr);
#endif

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

      pugp->next->prev = pugp;
      pugp = pugp->next;
    }

    next_syntax++;

    if(char_syntax == '[')
      input_ptr = open_bracket(next_syntax, pugp);
    else if(char_syntax == '{')
      input_ptr = open_brace(next_syntax, pugp);
    else if(char_syntax == '(')
      input_ptr = open_paren(next_syntax, pugp);

    pugp->next = calloc(1, sizeof *(pugp->next));

    if(!pugp->next)
      perror("calloc");

    pugp->next->prev = pugp;
    pugp = pugp->next;
  }

  init_strglob(pugh);
  show_strglob(pugh);

  if(0) {
    const unsigned long gcnt = count_strglob(pugh);

    printf("\n%lu\n", gcnt);
  }

  exit(EXIT_SUCCESS);
}
