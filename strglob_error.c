#include"strglob.h"

void strglob_error(const char *mesg) {
  assert(mesg);

  fputs(mesg, stderr);
  fputc('\n', stderr);

  exit(EXIT_FAILURE);
}
