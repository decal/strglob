#include"strglob.h"

/*!
 * @fn void exit_verbose(const char *afunc, const char *afile, const long aline)
 *
 * @brief exit from the program after displaying a verbose error message via the standard error stream
 *
 * @param [in] afunc the function that the error occurred in
 * @param [in] afile the source code file that the error occurred in
 * @param [in] aline the line of `afile` that the error occurred on
 *
 * @note this has been coded as a sort of replacement for `error_at_line` from `error.h`
 *
 */

void exit_verbose(const char *afunc, const char *afile, const long aline) {
  assert(afunc);
  assert(afile);

  fprintf(stderr, "%s:%lu %s() => \"%s\"\n", afile, aline, afunc, strerror(errno));

  exit(EXIT_FAILURE);

  return;
}
