#include"strglob.h"

STR_GLOB *last_element(STR_GLOB *const ugpnt) {
  STR_GLOB *restrict ugptr = ugpnt;
  STR_GLOB *restrict ugsav = ugptr;

  while(ugptr) {
    ugsav = ugptr;
    ugptr = ugptr->next;
  }

  return ugsav;
}
