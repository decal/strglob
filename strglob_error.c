#include"strglob.h"

/*! @fn void strglob_error(const char *mesg)
 *
 *  @brief show a message on the standard error stream and exit with a failure code
 *
 *  @param [in] mesg the message to be displayed
 *
 */
void strglob_error(const char *mesg) {
  assert(mesg);

  fputs(mesg, stderr);
  fputc('\n', stderr);

  exit(EXIT_FAILURE);
}
