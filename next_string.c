#include"strglob.h"

/*!
 * @note this function is not being called?? 
 */

char *next_string(const char *sptr, STR_GLOB *uptr) {
  uptr->out = malloc(2 * sizeof(*(uptr->out)));

  if(!uptr->out)
    exit_verbose("malloc", __FILE__, __LINE__);


  uptr->out[0] = (char*)sptr;
  uptr->out[1] = NULL;

  return (char*)sptr;
}
