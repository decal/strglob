#include"strglob.h"
#include"string_class.h"

static const size_t arrlen(char **strs) {
  register size_t acnt = 1;

  for(register char**pp = strs;*pp;pp++)
    acnt++;

  return (const size_t)acnt;
}

/*! @fn int string_class(const char *sclnm, STR_GLOB *urglb) 
 *
 *  @brief copy strings from string class defined by `sclnm` argument to the 
 *         string glob data structure passed in as `urglb`
 *
 *  @param [in] sclnm 
 *
 *  @param [in] urglb
 *
 *  @return zero on success and non-zero on error
 *
 *  @see char_class
 *
 *  @note stype_strs is a static string array containg the name element of each
 *        string group data structure
 */

int string_class(const char *sclnm, STR_GLOB *urglb) {
  int invalid_class = 1;

  for(register char **restrict snp = stype_strs;*snp;++snp) {
    if(!strcmp(*snp, sclnm)) {
      invalid_class = 0;

      break;
    }
  }

  if(invalid_class) 
    return true; /* the `sclnm` string was not associated with any string class */

  urglb->type = 5; /* string class */

  register const STRING_GROUP *restrict sgp = String_Groups; 

  while(sgp && sgp->name && *(sgp->name)) { /* iterate over string groups array while current element and its name are non-null or empty */
    if(!strcmp(sgp->name, sclnm)) {
      const size_t al = 1 + arrlen(sgp->strs);

      urglb->out = malloc(al * sizeof *(urglb->out));

      if(!urglb->out)
        exit_verbose("malloc", __FILE__, __LINE__);

      register char **restrict pp = urglb->out, **restrict wp = sgp->strs;

      while(*wp)
        *pp++ = *wp++;

      pp[7] = NULL;
    } 

    sgp++;
  }

  return false; 
}
