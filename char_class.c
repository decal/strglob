#include"strglob.h"

static const char *ctype_strs[] = { "alnum", "alnumupper", "alnumlower", "alpha", "alphaupper", "alphalower", "cntrl", "digit", "graph", "lower", "print", "printupper", "printlower", "punct", "space", "upper", "xdigit", "ascii", "asciiupper", "asciilower", "blank", NULL};

/*! @fn void char_class(const char *clsnm, STR_GLOB *restrict ugcls)
 *
 *  @brief create an array of strings for each byte in the desired (possibly pre-defined) character range
 *
 *  @details the `out` member of the `ugcls` structure is assigned an array of strings instead of a value being returned
 *
 *  @param [in] clsnm the character class name string
 *
 *  @param [out] ugcls the current element of the glob string's linked list that is being operated on
 *
 */

void char_class(const char *clsnm, STR_GLOB *restrict ugcls) {
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
    CHAR_RANGE ranges[] = { 
      { .sta = '0', .fin = '9', .inc = 1 }, 
      { .sta = 'a', .fin = 'z', .inc = 1 }, 
      { .sta = 'A', .fin = 'Z', .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "alpha")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 'a', .fin = 'z', .inc = 1 }, 
      { .sta = 'A', .fin = 'Z', .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "ascii")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x01, .fin = 0x7f, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "blank")) {
    const char *const blanks = "\v\f\t\r\n ";

    ugcls->out = cons_str2strs(blanks);
  }

  if(!strcmp(clsnm, "cntrl")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x01, .fin = 0x1f, .inc = 1 }, 
      { .sta = 0x7f, .fin = 0x7f, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "digit")) {
    CHAR_RANGE ranges[] = { 
      { .sta = '0', .fin = '9', .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "graph")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x21, .fin = 0x7e, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "punct")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x20, .fin = 0x20, .inc = 1 }, 
      { .sta = 0x30, .fin = 0x39, .inc = 1 }, 
      { .sta = 0x5b, .fin = 0x60, .inc = 1 }, 
      { .sta = 0x7b, .fin = 0x7e, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "lower")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x61, .fin = 0x7a, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "upper")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x41, .fin = 0x5a, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "print")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x20, .fin = 0x7e, .inc = 1 }, 
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "space")) {
    CHAR_RANGE ranges[] = { 
      { .sta = 0x09, .fin = 0x0d, .inc = 1 }, 
      { .sta = 0x20, .fin = 0x20, .inc = 1 },
      { .sta = 0, .fin = 0, .inc = 1 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "xdigit")) { 
    CHAR_RANGE ranges[] = { 
      { .sta = '0', .fin = '9', .inc = 1 }, 
      { .sta = 'a', .fin = 'f', .inc = 1 }, 
      { .sta = 'A', .fin = 'F', .inc = 1 },
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }

  if(!strcmp(clsnm, "word")) {
    CHAR_RANGE ranges[] = { 
      { .sta = '0', .fin = '9', .inc = 1 },
      { .sta = 'a', .fin = 'a', .inc = 1 },
      { .sta = 'A', .fin = 'Z', .inc = 1 },
      { .sta = '_', .fin = '_', .inc = 1 },
      { .sta = 0, .fin = 0, .inc = 0 } };

    char_ranges(ranges, ugcls);
  }
                                          
  return;
}
