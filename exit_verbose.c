#include"strglob.h"

void exit_verbose(const char *afunc, const char *afile, const long aline) {
  assert(afunc);
  assert(afile);

  fprintf(stderr, "%s: %s[%lu] %s() => \"%s\"\n", program_invocation_short_name, afile, aline, afunc, strerror(errno));

  exit(EXIT_FAILURE);

  return;
}
