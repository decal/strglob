#include"strglob.h"

/*! 
  * @fn void cartesian_product(int **sets, int *setLengths, int *currentSet, const int numSets, const int times)
  * 
  * @brief computes the cartesian product of the given integer sets (arrays)
  *
  * @details this function is used to compute all possible combinations of array indexes to reference array members
  *   that have been generated to correspond to the given ranges and/or sets of characters/strings in glob syntax
  *
  * @param [in] sets the arrays to apply the cartesian product set operation to
  * @param [in] setLengths an array containing the lengths of the arrays passed in `sets`
  * @param [in] currentSet a variable that retains context by holding the set currently being operated on
  * @param [in] numSets the number of arrays to calculate the cartesian product of
  * @param [in] times a varable that ensures subsets aren't computed by only returning sets of the proper length
  *
  * @note `cartesian_product` doesn't return anything as its output is stored in the global `results` variable above
  */

int **cartesian_product(int **sets, int *setLengths, int *currentSet, const int numSets, const int times, int ***resultz, int *anindex) {
  int **results = *resultz;

  if(!results) {
    register size_t total_length = 1;
    register int *slp = setLengths;

    for(;*slp && *slp > 0;slp++)
      total_length *= *slp; 

#ifdef DEBUG_STRGLOB
  fprintf(stderr, "total_length (product of multiplied set lengths): %lu \t *slp (set length pointer): %d\n", total_length, *slp);
#endif

    results = malloc((1 + total_length) * (sizeof *results));

    if(!results)
      exit_verbose("malloc", __FILE__, __LINE__);

    results[total_length] = 0;
  }

#ifdef DEBUG_STRGLOB
  fprintf(stderr, "times: %d numSets (number of given sets plus one): %d\n", times, numSets);
#endif

	if(times < numSets) {
    register int j = 0;

		for(;j < setLengths[times];j++) {
#ifdef DEBUG_STRGLOB
  fprintf(stderr, "j: %d times: %d numSets: %d sets[times][j]: %d setLengths[times]: %d\n", j, times, numSets, sets[times][j], setLengths[times]);
#endif

			currentSet[times] = sets[times][j];

      cartesian_product(sets, setLengths, currentSet, numSets, times + 1, resultz, anindex);
    }
  }

  if((times + 1) != numSets) {
#ifdef DEBUG_STRGLOB
    fputs("Returning early from cartesian_product()", stderr);
#endif

    return results;
  }

  int *const r = malloc((1 + times) * (sizeof *r));

  if(!r)
    exit_verbose("malloc", __FILE__, __LINE__);

  r[times] = -1;

#pragma omp parallel for
  for(register int i = 0;i < times;i++) 
    r[i] = currentSet[i];

  results[(*anindex)++] = r;

  *resultz = results;

  return results;
}
