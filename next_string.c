#include"strglob.h"

char *next_string(char *sptr, STR_GLOB *uptr) {
  uptr->out = malloc(2 * sizeof(*(uptr->out)));

  if(!uptr->out)
    exit_verbose("malloc", __FILE__, __LINE__);

  uptr->out[0] = sptr;
  uptr->out[1] = NULL;

  return sptr;
}
