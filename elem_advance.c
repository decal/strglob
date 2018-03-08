#include"strglob.h"

extern STR_GLOB *pugh;

int elem_advance(STR_GLOB *const elem) {
  if(elem->outp) {
    if(!*(elem->outp)) {
      elem->outp = elem->out;   

      elem_advance(elem->prev);
    } else {
      (elem->outp)++;

      if(!*(elem->outp)) {
        elem->outp = elem->out;

        elem_advance(elem->prev);
      }
    }
  } else if(elem->strp) {
    if(!*(elem->strp)) {
      elem->strp = elem->str;

      elem_advance(elem->prev);
    } else {
      (elem->strp)++;

      if(!*(elem->outp)) {
        elem->outp = elem->out;

        elem_advance(elem->prev);
      }
    }
  }

  return elem == pugh;
}
