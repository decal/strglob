#include"strglob.h"

/*! @fn char **cons_str2strs(const char *chrs)
 *
 *  @brief create an array of strings from the characters in the given string
 *
 *  @param [in] chrs string containing the characters to construct strings out of
 *
 *  @return the array of strings made from the provided string 
 *
 */

char **cons_str2strs(const char *chrs) {
  assert(xstr);

  size_t clen = strlen(chrs);
  char **sret = malloc(++clen * sizeof*sret);

  if(!sret)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char **ppc = sret;

  for(register const char *pc = chrs;*pc;++pc)
    *ppc++ = cons_char2str(*pc);

  *ppc = NULL;
    
  return sret;
}
