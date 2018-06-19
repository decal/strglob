#include"strglob.h"

int main(int argc, char *argv[]) {
  if(argc < 2)
    show_usage(*argv);

  const char *restrict anarg = strdup(argv[1]);

  if(!anarg)
    exit_verbose("strdup", __FILE__, __LINE__);

  const HAND_GLOB *hand = handle_strglob(anarg);

  if(!hand) {
    fputs("*** Failure!\n", stderr);

    exit(EXIT_FAILURE);
  }

  char *restrict *restrict strs = copy_strglob(hand);

  if(!strs) {
    fputs("*** Null string array!\n", stderr);

    exit(EXIT_FAILURE);
  } else if(!*strs) {
    fputs("*** Empty string array!\n", stderr);

    exit(EXIT_FAILURE);
  }

  /* register int i = 0;

  for(register char *restrict *restrict pp=strs;pp && *pp;++pp) {
    fputs(*pp, stdout);

    if(!(++i % hand->size)) {
      i = 0;

      putchar('\n');

      continue;
    }
  } */

  fputs_strglob(hand, stdout);

  exit(EXIT_SUCCESS);
}
