#include"strglob.h"

void show_element(STR_GLOB *const ugpnt) {
  show_helper();

  if(ugpnt->strp) {
      if(!*(ugpnt->strp)) {
        ugpnt->strp = ugpnt->str;

        if(elem_advance(ugpnt->prev))
          return;
      } else {
        show_helper();

        (ugpnt->strp)++:
      }
  } else if(ugpnt->outp) {
    if(!*(ugpnt->outp)) {
      ugpnt->outp = ugpnt->out;

      if(elem_advance(ugpnt->prev))
        return;
    } else {
      show_helper();

      (ugpnt->outp)++;
    }
  } else 
    show_helper();

  return;
}
