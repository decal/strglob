#ifndef _URLGLOB_H
#define _URLGLOB_H 1

#define NDEBUG 1 /* see assert(3) */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sysexits.h>
#include<assert.h>
#include<errno.h>
#include<error.h>

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
  char *strp; /* current character location in str */
  char **out; /* a list of possible output strings */
  char **outp; /* pointer to keep track of where we are in the out pointers when iterating over output */
  unsigned int type; /* 1 = integer range, 2 = character range, 3 = set, 4 = string repitition */
  size_t zlen; /* this is needed in case the range end is larger that the beg, i.e. '[1-10]' */
  long beg; /* beginning of range.. will be treated like a char for character ranges, i.e. '[a-c]' */
  long end; /* end of range started with beg */
  struct str_glob *prev;
  struct str_glob *next; /* next piece of input string */
} STR_GLOB, *PSTR_GLOB, **PPSTR_GLOB;

char **array_range(STR_GLOB *);
size_t count_commas(const char *);
size_t count_strglob(STR_GLOB *);
void char_class(const char *const, STR_GLOB *);
size_t integer_length(long);
void show_usage(const char *const);
void strglob_error(const char *);
void strglob_errorat(const char *, const unsigned long, const char *);
void showall_strglob(STR_GLOB *);
void init_strglob(STR_GLOB *restrict);
void show_strglob(STR_GLOB *restrict);
void show_helper(void);
char *open_bracket(char *restrict, STR_GLOB *);
char *open_brace(char *restrict, STR_GLOB *);
char *open_paren(char *, STR_GLOB *);
char *next_string(char *, STR_GLOB *);
int string_class(const char *, STR_GLOB *);
void write_strptrs(STR_GLOB *, char *restrict *restrict);
int elem_advance(STR_GLOB *const);

/* count_strptrs */
size_t count_strptrs(char *restrict *restrict);

/* prototypes of functions for actions performed by binary operators */
void set_difer(STR_GLOB *, STR_GLOB *);
void set_union(STR_GLOB *, STR_GLOB *);
void dis_union(STR_GLOB *, STR_GLOB *);

#endif
