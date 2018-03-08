#include"strglob.h"

extern STR_GLOB *pugh;

void show_helper(void) {
  register STR_GLOB *restrict sghad = pugh;

  while(sghad) {
    if(sghad->strp && *(sghad->strp)) {
      fputc(*(sghad->strp), stdout); 
    } else if(sghad->outp && *(sghad->outp)) {
      fputs(*(sghad->outp), stdout);
    } else {
      if(sghad->str)
        fputs(sghad->str, stdout); 
    }

    sghad = sghad->next;
  }

  putchar('\n');

  return;
}
