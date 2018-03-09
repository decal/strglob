#include"strglob.h"

extern STR_GLOB *pugh;

int elem_advance(STR_GLOB *const elem) {
  if(!elem)
    return 1;

  if(elem->outp) {
    (elem->outp)++;

    if(!*(elem->outp)) {
      elem->outp = elem->out;   

      elem_advance(elem->prev);
    } else {
    }
  } else if(elem->strp) {
    (elem->strp)++;

    if(!*(elem->strp)) {
      elem->strp = elem->str;

      elem_advance(elem->prev);
    } else {
    }
  }

  return 0;
}
