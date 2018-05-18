#include"strglob.h"

/*! @fn char *set_union(STR_GLOB *seta, STR_GLOB *setb)
 *  
 *  @brief compute the set of characters that are in both of the provided sets
 *
 *  @param [in] seta 
 *  @param [in] setb
 *
 *  @return a set containing each of the characters in `seta` and `setb` 
 *
 *  @note the return value's set won't contain any repeating elements (which are
 *  characters in this case) because that is how a set is defined
 *
 *  @see https://wikipedia.org/wiki/Set_union
 *  @see https://wikipedia.org/wiki/Set_(abstract_data_type)
 */

char *set_union(STR_GLOB *seta, STR_GLOB *setb) {
  assert(seta);
  assert(setb);

  return NULL;
}
