#include"strglob.h"

static const char *ctype_strs[] = { "alnum", "alnumupper", "alnumlower", "alpha", "alphaupper", "alphalower", "cntrl", "digit", "graph", "lower", "print", "printupper", "printlower", "punct", "space", "upper", "xdigit", "ascii", "asciiupper", "asciilower", "blank", NULL};

/*! @fn void char_ranges(CHAR_RANGE *crang, STR_GLOB *ugcrn)
 *
 *  @brief create an array of strings for each byte in the desired (possibly pre-defined) character range
 *
 *  @details the `out` member of the `ugcrn` structure is assigned an array of strings instead of a value being returned
 *
 *  @param [in] crang structure containing the start and end of the character range
 *
 *  @param [out] ugcrn the current element of the glob string's linked list that is being operated on
 *
 */

void char_ranges(const CHAR_RANGE *const crang, STR_GLOB *ugcrn) {
  assert(crngs);
  assert(ugcrn);

  register size_t szrgs = 1;

  for(register const CHAR_RANGE *crs = crang;crs->sta;++crs) {
    szrgs += (crs->fin - crs->sta);
    szrgs++;
  }

  ugcrn->out = malloc(szrgs * sizeof(*(ugcrn->out)));

  if(!ugcrn->out)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char **pp = ugcrn->out;

  for(register const CHAR_RANGE *crp = crang;crp->sta;++crp)
    for(register int c = crp->sta;c <= crp->fin;++c) {
      char *astr = malloc(2);
      
      if(!astr)
        exit_verbose("malloc", __FILE__, __LINE__);

      astr[0] = (char)c;
      astr[1] = '\0';

      *pp++ = astr;
    }

  *pp = NULL;

  return;
}

void char_class(const char *clsnm, STR_GLOB *ugcls) {
  unsigned char invalid_class = 1;

  for(register const char *const *cnp = ctype_strs;*cnp;++cnp) {
    if(!strcmp(*cnp, clsnm)) {
      invalid_class = 0;

      break;
    }
  }

  if(invalid_class)
    strglob_error("Unknown character class given after opening square bracket with colon!");

  ugcls->type = 4;

  if(!strcmp(clsnm, "alnum")) {
    CHAR_RANGE ranges[] = { {.sta = '0', .fin = '9' }, { .sta = 'a', .fin = 'z' }, { .sta = 'A', .fin = 'Z' }, { .sta = 0, .fin = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "alnumupper")) {
    ugcls->str = malloc(1 + ('9' - '0') + ('Z' - 'A'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp for simd  
    for(register int c = '0';c <= '9';c++)
      *ptr++ = c;

// #pragma omp for simd
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "alnumlower")) {
    ugcls->str = malloc(1 + ('9' - '0') + ('z' - 'a'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp for simd
    for(register int c = '0';c <= '9';c++)
      *ptr++ = c;

// #pragma omp for simd
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "alpha")) { 
    ugcls->str = malloc(1 + ('z' - 'a') + ('Z' - 'A'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "alphaupper")) { 
    ugcls->str = malloc(1 + 'Z' - 'A');

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

    *ptr = '\0';
  } 

  if(!strcmp(clsnm, "alphalower")) { 
    ugcls->str = malloc(1 + 'z' - 'a');

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  } 

  if(!strcmp(clsnm, "cntrl")) { 
    ugcls->str = malloc(1 + 0);

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);
  } 

  if(!strcmp(clsnm, "digit")) { 
    ugcls->str = malloc(1 + '9' - '0');

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = '0';c <= '9';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "graph")) { 
    ugcls->str = malloc(1 + 0x5f - 0x21);

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 0x21;c <= 0x5f;c++)
      *ptr++ = c;

    *ptr = '\0';
  } 

  if(!strcmp(clsnm, "lower")) { 
    ugcls->str = malloc(1 + 'z' - 'a');

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  } 

  if(!strcmp(clsnm, "print")) { 
    ugcls->str = malloc(1 + 0x5f - 0x20);

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for 
    for(register int c = 0x20;c < 0x5f;c++)
      *ptr++ = c;

    *ptr = '\0';
  } 

  if(!strcmp(clsnm, "printupper")) { 
    ugcls->str = malloc(1 + 'Z' - 'A');

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "printlower")) { 
    ugcls->str = malloc(1 + 0x5f - 0x20 - ('Z' - 'A'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "punct")) { 
    ugcls->str = malloc(1 + (0x5f - 0x21));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ =c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "space")) { 
    ugcls->str = malloc(7);

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

    *ptr++ = ' ';
    *ptr++ = '\f';
    *ptr++ = '\n';
    *ptr++ = '\r';
    *ptr++ = '\t';
    *ptr++ = '\v';
    *ptr = '\0';
  }

  if(!strcmp(clsnm, "upper")) { 
    ugcls->str = malloc(1 + ('Z' - 'A'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "xdigit")) { 
    ugcls->str = malloc(1 + ('9' - '0') + ('F' - 'A') + ('f' - 'a'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = '0';c <= '9';c++)
      *ptr++ = c;

// #pragma omp parallel for
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "xdigitupper")) { 
    ugcls->str = malloc(1 + ('9' - '0') + ('F' - 'A'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = '0';c <= '9';c++)
      *ptr++ = c;

// #pragma omp parallel for
    for(register int c = 'A';c <= 'Z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "xdigitlower")) { 
    ugcls->str = malloc(1 + ('9' - '0') + ('z' - 'a'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = '0';c <= '9';c++)
      *ptr++ = c;

// #pragma omp parallel for
    for(register int c = 'a';c <= 'z';c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "ascii")) { 
    ugcls->str = malloc(1 + 0x7f);

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 0x01;c <= 0x7f;c++)
      *ptr++ = c;

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "asciiupper")) { 
    ugcls->str = malloc(1 + 0x7f - ('z' - 'a'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__); 

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 0x01;c <= 0x7f;c++) {
      if(*ptr == 'a')
        c = 'z' + 0x01;

      *ptr++ = c;
    }

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "asciilower")) { 
    ugcls->str = malloc(1 + 0x7f - ('Z' - 'A'));

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

// #pragma omp parallel for
    for(register int c = 0x01;c <= 0x7f;c++) {
      if(*ptr == 'A')
        c = 'Z' + 0x01;

      *ptr++ = c;
    }

    *ptr = '\0';
  }

  if(!strcmp(clsnm, "blank")) { 
    ugcls->str = malloc(3);

    if(!ugcls->str)
      exit_verbose("malloc", __FILE__, __LINE__);

    register char *restrict ptr = ugcls->str;

    *ptr++ = ' ';
    *ptr++ = '\t';
    *ptr = '\0';
  }
    
  return;
}
