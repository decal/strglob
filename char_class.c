#include"strglob.h"

static const char *ctype_strs[] = { "alnum", "alnumupper", "alnumlower", "alpha", "alphaupper", "alphalower", "cntrl", "digit", "graph", "lower", "print", "printupper", "printlower", "punct", "space", "upper", "xdigit", "ascii", "asciiupper", "asciilower", "blank", "reserved", NULL};

/*! @fn void char_class(const char *clsnm, STR_GLOB *restrict ugcls)
 *
 *  @brief create an array of strings for each byte in the desired (possibly pre-deended) character range
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
      { .beg = '0', .end = '9', .inc = 1 }, 
      { .beg = 'a', .end = 'z', .inc = 1 }, 
      { .beg = 'A', .end = 'Z', .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "alpha")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 'a', .end = 'z', .inc = 1 }, 
      { .beg = 'A', .end = 'Z', .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "ascii")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x01, .end = 0x7f, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "blank")) {
    const char *const blanks = "\v\f\t\r\n ";

    ugcls->out = cons_str2strs(blanks);
  }

  if(!strcmp(clsnm, "cntrl")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x01, .end = 0x1f, .inc = 1 }, 
      { .beg = 0x7f, .end = 0x7f, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "digit")) {
    CHAR_RANGE ranges[] = { 
      { .beg = '0', .end = '9', .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "graph")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x21, .end = 0x7e, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "punct")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x20, .end = 0x20, .inc = 1 }, 
      { .beg = 0x30, .end = 0x39, .inc = 1 }, 
      { .beg = 0x5b, .end = 0x60, .inc = 1 }, 
      { .beg = 0x7b, .end = 0x7e, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "lower")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x61, .end = 0x7a, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "upper")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x41, .end = 0x5a, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "print")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x20, .end = 0x7e, .inc = 1 }, 
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "space")) {
    CHAR_RANGE ranges[] = { 
      { .beg = 0x09, .end = 0x0d, .inc = 1 }, 
      { .beg = 0x20, .end = 0x20, .inc = 1 },
      { .beg = 0, .end = 0, .inc = 1 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "xdigit")) { 
    CHAR_RANGE ranges[] = { 
      { .beg = '0', .end = '9', .inc = 1 }, 
      { .beg = 'a', .end = 'f', .inc = 1 }, 
      { .beg = 'A', .end = 'F', .inc = 1 },
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "word")) {
    CHAR_RANGE ranges[] = { 
      { .beg = '0', .end = '9', .inc = 1 },
      { .beg = 'a', .end = 'a', .inc = 1 },
      { .beg = 'A', .end = 'Z', .inc = 1 },
      { .beg = '_', .end = '_', .inc = 1 },
      { .beg = 0, .end = 0, .inc = 0 } };

    char_range(ranges, ugcls);
  }

  if(!strcmp(clsnm, "reserved")) {
    CHAR_RANGE ranges[] = {
      { .beg = '!', .end = '!', .inc = 1 },
      { .beg = '#', .end = '$', .inc = 1 },
      { .beg = '&', .end = ',', .inc = 1 },
      { .beg = '/', .end = '/', .inc = 1 },
      { .beg = ':', .end = ';', .inc = 1 },
      { .beg = '=', .end = '=', .inc = 1 },
      { .beg = '?', .end = '@', .inc = 1 },
      { .beg = '[', .end = '[', .inc = 1 },
      { .beg = ']', .end = ']', .inc = 1 } };

    char_range(ranges, ugcls);
  }
                                          
  return;
}
