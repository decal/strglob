#include"strglob.h"

extern STR_GLOB *pugh;

void show_strglob(STR_GLOB *restrict ugpnt) {
  show_helper();

  while(ugpnt) {
    if(ugpnt->strp) {
      (ugpnt->strp)++;

      if(!*(ugpnt->strp)) {
        ugpnt->strp = ugpnt->str;

        show_helper();

        if(elem_advance(ugpnt->prev))
          return;
        else
          show_helper();
      } else {
        show_helper();
      } 
    } else if(ugpnt->outp) {
      show_helper();

      if(!*(ugpnt->outp)) {
        ugpnt->outp = ugpnt->out;

        show_helper();

        if(elem_advance(ugpnt->prev))
          return;
        else
          show_helper();
      } else {
        show_helper();

        (ugpnt->outp)++;
      }
    } else {
      show_helper();
    }

    ugpnt = ugpnt->next;
  }

  return;
}
