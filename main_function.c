#include"strglob.h"

STR_GLOB *pugh = NULL;

extern int **results;

int main(int argc, char *argv[]) {
  register STR_GLOB *pugp = NULL;
  char *input_ptr = NULL;
  int **sets = NULL;
  int *lens = NULL, *lp = NULL;

  if(argc < 2)
    show_usage(*argv);

  pugh = calloc(1, sizeof *pugh);

  if(!pugh)
    perror("calloc");

  pugp = pugh;
  input_ptr = argv[1];

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

      /* pugp->next->prev = pugp; */
      pugp = pugp->next;
    }

    /* next_syntax++; */

    if(char_syntax == '[')
      input_ptr = open_bracket(next_syntax, pugp);
    else if(char_syntax == '{')
      input_ptr = open_brace(next_syntax, pugp);
    else if(char_syntax == '(')
      input_ptr = open_paren(next_syntax, pugp);

    pugp->next = calloc(1, sizeof *(pugp->next));

    if(!pugp->next)
      perror("calloc");

    /* pugp->next->prev = pugp; */
    pugp = pugp->next;
  }

  init_strglob(pugh);

  sets = conv_gl2ias(pugh);
  lens = calc_setlens(sets);
  lp = lens;

  while(*lp != -1)
    lp++;

  size_t asiz = 1 + lp - lens;
  int *cset = malloc(asiz * sizeof*cset);

  if(!cset)
    exit_verbose("malloc", __FILE__, __LINE__);

  cartesian_product(sets, lens, cset, asiz--, 0);

  char ***kstr = conv_gl2sas(pugh);
  int **crp = results;

  for(register int c = 0;crp[c];++c) {
    register int *ind = crp[c];

    for(register int k = 0;k < asiz;++k)
      fputs(kstr[k][*ind++], stdout);

    putchar('\n');
  }

  exit(EXIT_SUCCESS);
}
