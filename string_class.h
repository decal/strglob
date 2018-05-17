#ifndef _STRING_CLASS_H
#define _STRING_CLASS_H

// HACK: that 64 down there in char *strs[64].
// not sure of the best way to get rid of it right now.
// it will use up more space than needed... or I could make the string class config uglier.
// will try to think of a better way.
// this way at least prevents having to copy a list of class names between two different spots by hand.

#define MAX_STRINGS_PER_CLASS 16 //this can be tuned to lowest needed.

typedef struct _string_groups {
  const char *name;
  int opts;
  char *strs[MAX_STRINGS_PER_CLASS];//if this isn't flexible it works a lot nicer. but it also takes up at least this much space for each structure.
} STRING_GROUPS;

/* if the string class ends in a 'z', then don't include the weekend days */
STRING_GROUPS derp[] = {
 { .name="wdays", .opts=0, .strs = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL }},
 { .name="wdayz", .opts=0, .strs = { "mon", "tue", "wed", "thu", "fri", NULL }},
 { .name="Wdayz", .opts=0, .strs = { "Mon", "Tue", "Wed", "Thu", "Fri", NULL }},
 { .name="WDAYZ", .opts=0, .strs = { "MON", "TUE", "WED", "THU", "FRI", NULL }},
 { .name="Wdays", .opts=0, .strs = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL }},
 { .name="WDAYS", .opts=0, .strs = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", NULL }},
 { .name="weekdays", .opts=0, .strs = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", NULL }},
 { .name="Weekdays", .opts=0, .strs = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", NULL }},
 { .name="WEEKDAYS", .opts=0, .strs = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", NULL }},
 { .name="weekdayz", .opts=0, .strs = { "monday", "tuesday", "wednesday", "thursday", "friday", NULL }},
 { .name="Weekdayz", .opts=0, .strs = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", NULL }},
 { .name="WEEKDAYZ", .opts=0, .strs = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", NULL }},
 { .name=NULL, .opts=0, .strs={NULL}} //end marker
};

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
