#include"main_function.h"

int main(int argc, char *argv[]) {
  int **sets = NULL;
  int *lens = NULL, *lp = NULL;

  if(argc < 2)
    show_usage(*argv);

  pugh = cons_str2glob(argv[1]);
  sets = cons_glob2ints(pugh);
  lens = calc_setlens(sets);
  lp = lens;

  while(*lp != -1)
    lp++;

  size_t asiz = 1 + lp - lens;
  int *cset = malloc(asiz * sizeof *cset);

  if(!cset)
    exit_verbose("malloc", __FILE__, __LINE__);

  cartesian_product(sets, lens, cset, asiz--, 0);

  fputs_strglob(pugh, asiz, stdout);

  exit(EXIT_SUCCESS);
}
