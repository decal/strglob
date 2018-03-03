#include"strglob.h"

void strglob_errorat(const char *afile, const unsigned long aline, const char *afunc) {
#ifdef DEBUG_STRGLOB
  fputs("Entering strglob_errorat()\n", stderr);
#endif

  fprintf(stderr, "%s: %s[%u] %s() => \"%s\"\n", program_invocation_short_name, afile, aline, afunc, strerror(errno)); 

  exit(errno);
}
