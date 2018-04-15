#include"main_function.h"

static char *ansicolor_name2escape(const char *aname) {

  return "";
}

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

  char ***kstr = cons_glob2astras(pugh);
  int *const *crp = results;

  char *aclr = getenv("STRGLOB_COLOR");
  char *cstr = "";
  const char *const crst = "\033[m";
  

  if(aclr)
    cstr = ansicolor_name2escape(*aclr);

  if(kstr && crp)
    for(register int c = 0;crp[c];++c) {
      const int *restrict ind = crp[c];

      if(asiz == 1)
        fputs(kstr[0][*ind], stdout);
      else
        for(register int k = 0;k < asiz;++k, ++ind) {
          if(!kstr[k] || *ind == -1 || !kstr[k][*ind])
            break;

            fputs(cstr, stdout);
            fputs(kstr[k][*ind], stdout);
            fputs(crst, stdout);
          }

      putchar('\n');
    }

  exit(EXIT_SUCCESS);
}
