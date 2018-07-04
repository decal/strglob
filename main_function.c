#include"strglob.h"

static void show_usage(const char *const anarg) { fprintf(stderr, "usage: %s STRING\n", anarg); exit(EX_USAGE); }

int main(int argc, char *argv[]) {
  if(argc < 2) show_usage(*argv);

  const char *restrict anarg = strdup(argv[1]);

  if(!anarg) exit_verbose("strdup", __FILE__, __LINE__);

  const HAND_GLOB *hand = handle_strglob(anarg);

  if(!hand) { fputs("*** Failure!\n", stderr); exit(EXIT_FAILURE); }

  char *restrict *restrict strs = copy_strglob(hand);

  if(!strs) { fputs("*** Null string array!\n", stderr); exit(EXIT_FAILURE); } 
  else if(!*strs) { fputs("*** Empty string array!\n", stderr); exit(EXIT_FAILURE); }

  fputs_strglob(hand, stdout); 
  exit(EXIT_SUCCESS);
}
