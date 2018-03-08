#include"strglob.h"

void write_strptrs(STR_GLOB *sglb, char *restrict *restrict strs) {
#ifdef DEBUG_STRGLOB
  fputs("Entering write_strptrs()\n", stderr);
#endif

  assert(sglb);
  assert(strs);

  const size_t slen = 1 + count_strptrs(strs);

  sglb->out = malloc(slen);

  if(!sglb->out)
    error_at_line(1, errno, __FILE__, __LINE__, "malloc: %s", strerror(errno));

  register char *restrict *restrict pp = strs;
  register char *restrict *restrict sp = sglb->out;

  while(*pp)
    *sp++ = *pp++;

  return;
}
