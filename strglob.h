#ifndef _URLGLOB_H
#define _URLGLOB_H 1

#define NDEBUG 1 /* see assert(3) */
#define _GNU_SOURCE 1 /* see program_invocation_short_name(3) */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sysexits.h>
#include<assert.h>
#include<errno.h>
#include<error.h>
#include<limits.h>

#ifndef S_SPLINT_S
#include<ctype.h>
#endif

/* str = val, glob = null, next = null (STRING ONLY) */
/* str = val, glob = val, next = null (STRING, GLOB) */
/* str = val, glob = val, next = val (STRING, GLOB, NEXT) */
/* str = val, glob = null, next = val (INVALID) */
/* str = null, glob = val, next = val (GLOB, NEXT) */
/* str = null, glob = val, next = null (GLOB) */
/* str = null, glob = null, next = null (INVALID) */

typedef struct str_glob {
  char *str; /* a static string if this is not a pattern */
  char **out; /* a list of possible output strings */
  size_t tot; /* total number of possible output strings (zero, if static string) */
  unsigned int type; /* 1 = integer range, 2 = character range, 3 = set, 4 = string repitition */
  size_t zlen; /* this is needed in case the range end is larger that the beg, i.e. '[1-10]' */
  long beg; /* beginning of range.. will be treated like a char for character ranges, i.e. '[a-c]' */
  long end; /* end of range started with beg */
  /* struct str_glob *prev; */
  struct str_glob *next; /* next piece of input string */
} STR_GLOB, *PSTR_GLOB, **PPSTR_GLOB;

typedef struct char_range {
  int sta;
  int fin;
} CHAR_RANGE, *PCHAR_RANGE, *PPCHAR_RANGE;

void cartesian_product(int **, int *, int *, const int, const int);
int *calc_setlens(int **);
char **imply_range(STR_GLOB *const);
size_t count_commas(const char *);
size_t count_strglob(STR_GLOB *);
void char_class(const char *const, STR_GLOB *);
int **conv_gl2ias(STR_GLOB *);
char ***conv_gl2sas(STR_GLOB *);
int *enum_intseq(const size_t);
void exit_verbose(const char *, const char *, const long);
size_t measure_integer(long int);
void show_usage(const char *const);
void strglob_error(const char *);
void strglob_errorat(const char *, const unsigned long, const char *);
void showall_strglob(STR_GLOB *);
void init_strglob(STR_GLOB *restrict);
void show_strglob(STR_GLOB *restrict);
void show_helper(void);
char *open_bracket(char *, STR_GLOB *const);
char *open_brace(char *, STR_GLOB *);
char *open_paren(char *, STR_GLOB *);
char *next_string(char *, STR_GLOB *);
int string_class(const char *, STR_GLOB *);
int elem_advance(STR_GLOB *const);
int **getcp_results(void);

/* prototypes of functions for actions performed by binary operators */
void set_difer(STR_GLOB *, STR_GLOB *);
void set_union(STR_GLOB *, STR_GLOB *);
void dis_union(STR_GLOB *, STR_GLOB *);

#endif
