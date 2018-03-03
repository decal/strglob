#include"strglob.h"

void show_usage(const char *const anarg) {
#ifdef DEBUG_STRGLOB
  fputs("Entering show_usage()\n", stderr);
#endif

  fprintf(stderr, "usage: %s STRING\n", anarg);

  exit(EX_USAGE);
}
