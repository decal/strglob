#include"strglob.h"

extern STR_GLOB *pugh;

void show_strglob(STR_GLOB *restrict ugpnt) {
  show_helper();

  STR_GLOB *const uglst = last_element(ugpnt);

  while(ugpnt) {
    if(ugpnt->strp) {
      (ugpnt->strp)++;

      if(!*(ugpnt->strp)) {
        ugpnt->strp = ugpnt->str;

        elem_advance(ugpnt->prev);
      } else {
      } 
      
      show_helper();
    } else if(ugpnt->outp) {
      (ugpnt->outp)++;

      if(!*(ugpnt->outp)) {
        ugpnt->outp = ugpnt->out;

        elem_advance(ugpnt->prev);
      } else {
      }

      show_helper();
    } else {
    }

    ugpnt = ugpnt->next;
  }

  return;
}
