#include"strglob.h"

/*! @fn size_t count_lines(const char *path)
 *
 *  @brief count the number of lines inside file at the given path name
 *
 *  @param [in] path the location of the file to count lines of
 *
 *  @return the total number of lines inside the file at path
 *
 */

size_t count_lines(const char *path) {
  register size_t l = 0;
  char b[BUFSIZ] = { 0x0 };
  FILE *f = fopen(path, "r");

  if(!f)
    exit_verbose("fopen", __FILE__, __LINE__);

  while(fgets(b, sizeof b, f))
    l++;

  return l;
}
