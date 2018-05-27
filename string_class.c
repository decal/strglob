#include"strglob.h"
#include"string_class.h"

int string_class(const char *sclnm, STR_GLOB *urglb) {
  int invalid_class = 1;

  for(register char **snp = stype_strs;*snp;++snp) {
    if(!strcmp(*snp, sclnm)) {
      invalid_class = 0;

      break;
    }
  }

  if(invalid_class)
    return 1;

  urglb->type = 5;

  register STRING_GROUP *sgp = String_Groups; 

  while(sgp && sgp->name) {
    if(!strcmp(sgp->name, sclnm)) {
      urglb->out = malloc(8 * sizeof *(urglb->out));

      if(!urglb->out)
        exit_verbose("malloc", __FILE__, __LINE__);

      register char **pp = urglb->out;
      register char **wp = sgp->strs;

      while(*wp)
        *pp++ = *wp++;

      pp[7] = NULL;
    } 

    sgp++;
  }

  return 0; 
}
