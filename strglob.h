/*! @file strglob.h 
 *  
 *  @brief Type definitions and function prototypes for the libstrglob shared library..
 *
 *  This header file contains various `struct` `typedef` definitions as
 *  well as function prototypes implemented by libstrglob. Any macros, 
 *  constants and global variables will also be defined here. 
 *
 *  @author Derek Callaway (@decalresponds)
 */

#ifndef _URLGLOB_H
#define _URLGLOB_H 

#define NDEBUG /* @see `assert(3)` */
#define _ISOC11_SOURCE
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#define _POSIX_C_SOURCE 200112L

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
#include<strings.h>
#include<sysexits.h>
#include<assert.h>
#include<errno.h>
#include<limits.h>

#ifndef S_SPLINT_S

/* code to be skipped over by the splint static checking tool */
#include<ctype.h>

#endif

/** Define the start and finish of a numeric or alphabetic character range */
typedef struct char_range {
  intmax_t beg; /* start value of inclusive alpha/numeric range */
  intmax_t end; /* finish value of inclusive alpha/numeric range */
  intmax_t inc; /* increment value of inclusive alpha/numeric range (defaults to +1) */
} CHAR_RANGE, *PCHAR_RANGE, **PPCHAR_RANGE;

/** Define the start, finish and optional increment of a floating point integer range */
typedef struct float_range {
  float beg; /* start value of inclusive floating point range */
  float end; /* finish value of inclusive floating point range */
  float inc; /* increment value of inclusive floating point range (defaults to +1.0) */
} FLOAT_RANGE, *PFLOAT_RANGE, **PPFLOAT_RANGE;

/** Define the start, finish and optional increment of a string range */
typedef struct string_range {
  char *beg; /* start value of inclusive string range */
  char *end; /* finish value of inclusive string range */
  char *inc; /* increment value of inclusive string range */
} STRING_RANGE, *PSTRING_RANGE, *PPSTRING_RANGE;

/** Define each sub-part of the glob string */
typedef struct str_glob {
  char *str; /* a static string if this is not a pattern */
  char **out; /* a list of possible output strings */
  size_t tot; /* total number of possible output strings (zero, if static string) */
  unsigned int type; /* 1 = integer range, 2 = character range, 3 = set, 4 = string repitition */
  size_t zlen; /* this is needed in case the range "end" is larger than the "beg", i.e. '[1-10]' */
  //intmax_t beg; /* beginning of range.. will be treated like a char for character ranges, i.e. '[a-c]' */
  //intmax_t end; /* end of range started with "beg" */
  //intmax_t inc; /* increment value */
  //float begf; /* beginning of floating point range */
  //float endf; /* end of floating point range started with "begf" */
  //float incf; /* floating-point increment value */
  //char *begs; /* beginning of string range */
  //char *ends; /* end of string range started with "begs" */
  //char *incs; /* string increment */

  union {
    struct char_range crng; /* char range */
    struct float_range frng; /* float range */
    struct string_range srng; /* string range */
  } runi; /* range union */

  struct str_glob *next; /* next piece of input string */
} STR_GLOB, *PSTR_GLOB, **PPSTR_GLOB;

/** Define data necessary to output strings generated from supplied glob pattern */
typedef struct hand_glob {
  STR_GLOB *glob; /* head of string glob linked list */
  int **carp; /* cartesian product results */
  size_t size; /* cartesian product cardinality */
} HAND_GLOB, *PHAND_GLOB, **PPHAND_GLOB;

/** Name a collection of character ranges as a character class */
typedef struct char_class {
  const char *name; /* name of character class */
  CHAR_RANGE *ranges; /* character ranges that character class consists of */
} CHAR_CLASS, *PCHAR_CLASS, **PPCHAR_CLASS;

int **cartesian_product(int **, int *, int *, const int, const int, int ***, int *);

extern int **results;

int *calc_setlens(int **);
char **imply_float_range(STR_GLOB *const);
char **imply_range(STR_GLOB *const);
size_t count_commas(const char *);
size_t count_lines(const char *);
size_t count_strglob(STR_GLOB *);
void char_class(const char *const, STR_GLOB *restrict);
void char_range(const CHAR_RANGE *const, STR_GLOB *restrict);
char *cons_char2str(const char);
char *cons_float2str(const float);
int **cons_glob2ints(STR_GLOB *);
char ***cons_glob2astras(STR_GLOB *);
STR_GLOB *cons_str2glob(const char *);
char **cons_str2strs(const char *);
char **copy_strglob(const HAND_GLOB *);
int *enum_intseq(const size_t);
void exit_verbose(const char *, const char *, const long);
void float_range(const FLOAT_RANGE *const, STR_GLOB *restrict);
int fputs_strglob(const HAND_GLOB *, FILE *);
HAND_GLOB *handle_strglob(const char *);
size_t measure_float(const float);
size_t measure_integer(intmax_t);
void show_usage(const char *const);
void strglob_error(const char *);
void string_range(const STRING_RANGE *const, STR_GLOB *restrict);
STR_GLOB *init_strglob(STR_GLOB *restrict);
char *open_bracket(char *, STR_GLOB *);
char *open_brace(char *, STR_GLOB *);
char *open_paren(char *, STR_GLOB *);
char *next_string(const char *, STR_GLOB *);
int string_class(const char *, STR_GLOB *);

/* prototypes of functions for actions performed by binary operators */
char *set_diff(STR_GLOB *, STR_GLOB *);
char *set_union(STR_GLOB *, STR_GLOB *);

#endif
