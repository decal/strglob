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
#define _URLGLOB_H 1

#define NDEBUG 1 /* @see `assert(3)` */
#define _ISOC11_SOURCE 1
#define _POSIX_C_SOURCE 200809L

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>
#include<sysexits.h>
#include<assert.h>
#include<errno.h>
#include<limits.h>

#ifndef S_SPLINT_S

/* code to be skipped over by the splint static checking tool */
#include<ctype.h>

#endif

/** Define each sub-part of the glob string */
typedef struct str_glob {
  char *str; /* a static string if this is not a pattern */
  char **out; /* a list of possible output strings */
  size_t tot; /* total number of possible output strings (zero, if static string) */
  unsigned int type; /* 1 = integer range, 2 = character range, 3 = set, 4 = string repitition */
  size_t zlen; /* this is needed in case the range end is larger that the beg, i.e. '[1-10]' */
  intmax_t beg; /* beginning of range.. will be treated like a char for character ranges, i.e. '[a-c]' */
  intmax_t end; /* end of range started with beg */
  struct str_glob *next; /* next piece of input string */
} STR_GLOB, *PSTR_GLOB, **PPSTR_GLOB;

/** Define the start and finish of a numeric or alphabetic character range */
typedef struct char_range {
  int sta; /* start value of range (inclusive) */
  int fin; /* finish value of range (inclusive) */
} CHAR_RANGE, *PCHAR_RANGE, *PPCHAR_RANGE;

void cartesian_product(int **, int *, int *, const int, const int);

extern int **results;

int *calc_setlens(int **);
char **imply_range(STR_GLOB *const);
size_t count_commas(const char *);
size_t count_strglob(STR_GLOB *);
void char_class(const char *const, STR_GLOB *);
int **conv_gl2ias(STR_GLOB *);
char ***conv_gl2sas(STR_GLOB *);
int *enum_intseq(const size_t);
void exit_verbose(const char *, const char *, const long);
size_t measure_integer(intmax_t);
void show_usage(const char *const);
void strglob_error(const char *);
void init_strglob(STR_GLOB *restrict);
char *open_bracket(char *, STR_GLOB *const);
char *open_brace(char *, STR_GLOB *);
char *open_paren(char *, STR_GLOB *);
char *next_string(char *, STR_GLOB *);
int string_class(const char *, STR_GLOB *);
void somefunc();

/* prototypes of functions for actions performed by binary operators */
char *set_diff(STR_GLOB *, STR_GLOB *);
char *set_union(STR_GLOB *, STR_GLOB *);

#endif
