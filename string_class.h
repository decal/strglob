#ifndef _STRING_CLASS_H
#define _STRING_CLASS_H

typedef struct _string_groups {
  const char *name;
  char **strs;
  int opts;
} STRING_GROUPS;

/* if the string class ends in a 'z', then don't include the weekend days */
static char *stype_strs[] = { "wdays", "Wdays", "WDAYS", "weekdays", "Weekdays", "WEEKDAYS", "wdayz", "Wdayz", "WDAYZ", "weekdayz", "Weekdayz", "WEEKDAYZ" };
static char *wdays_strs[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL };
static char *wdayz_strs[] = { "mon", "tue", "wed", "thu", "fri", NULL };
static char *Wdayz_strs[] = { NULL };  // to be 
static char *WDAYZ_strs[] = { NULL };  // filled in
static char *Wdays_strs[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL };
static char *WDAYS_strs[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", NULL };
static char *weekdays_strs[] = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", NULL };
static char *Weekdays_strs[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", NULL };
static char *WEEKDAYS_strs[] = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", NULL };
static char *weekdayz_strs[] = { NULL }; // so
static char *Weekdayz_strs[] = { NULL }; // do 
static char *WEEKDAYZ_strs[] = { NULL }; // these

/* mons, Mons, MONS, months, Months, MONTHS */

/* decints, Decints, DECINTS */
// decints = "one", "two", ..., "nine", "zero"
// Decints = "One", "Two", ..., "Nine", "Zero"
// DECINTS = "ONE", "TWO", ..., "NINE", "ZERO"

/* co, Co, CO, country, Country, COUNTRY */ /* us, Us, US, united states, United States, UNITED STATES */
/* continent, Continent, CONTINENT */ /* i.e. north america, North America, NORTH AMERICA */
/* os, Os, OS */ /* i.e. linux, Linux, LINUX */
/* platformxx, Platformxx, platform_xx, Platform_xx PLATFORMXX, PLATFORM_XX */ /* i.e. x64, X64, x86_64, X86_64, Intel64, INTEL64 */

/* if you need ideas, check https://github.com/decal/werdlists */

/* would be nice to define flags representing formatting functions to be applied like toupper(), camelcase(), capitalize(),  etc. */

#endif
