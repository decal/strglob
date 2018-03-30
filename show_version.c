#include"strglob.h"

void show_version(const char *const anarg) {
#ifdef DEBUG_STRGLOB
  fputs("Entering show_version()\n", stderr);
#endif

  putc('\n', stderr);
  fputs("<== strglob 1.0 ==>\n\n", stderr);
  fputs("Written by Derek Callaway\n", stderr);
  fprintf(stderr, "Compiled Date: %s\n", __DATE__);
  fprintf(stderr, "Compiled Time: %s\n", __TIME__);
  fprintf(stderr, "Standard C Version: %ld\n", __STDC_VERSION__);
  putc('\n', stderr);

  exit(EX_OK);
}
