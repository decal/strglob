#include"strglob.h"

void set_difer(STR_GLOB *seta, STR_GLOB *setb) {
#ifdef DEBUG_STRGLOB
  fputs("Set difference\n", stderr);
#endif

  assert(seta);
  assert(setb);

  register char *restrict psa = seta->str, *restrict psb = setb->str;

  if(!(psa && psb))
    strglob_error("set_difer passed string glob data structure without a string!");

  const size_t alen = strlen(seta->str), blen = strlen(setb->str);
  size_t xlen = alen - blen;
  char *xbuf = malloc(++xlen);

  if(!xbuf)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char *restrict psx = xbuf;

  while(*psb)
    if(!strchr(setb->str, *psb))
      *psx++ = *psb++;
    else
      psb++;

  *psx = '\0';

  seta->str = xbuf;

  return;
}
