#ifndef _STRING_CLASS_H
#define _STRING_CLASS_H

typedef struct _string_group {
  char *name;
  char **strs;
  int opts;
} STRING_GROUP;

/* if the string class ends in a 'z', then don't include the weekend days */
static const char *stype_strs[] = { "wdays", "Wdays", "WDAYS", "weekdays", "Weekdays", "WEEKDAYS", "wdayz", "Wdayz", "WDAYZ", "weekdayz", "Weekdayz", "WEEKDAYZ" };
static const char *wdays_strs[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL };
static const char *wdayz_strs[] = { "mon", "tue", "wed", "thu", "fri", NULL };
static const char *Wdayz_strs[] = { NULL };  // to be 
static const char *WDAYZ_strs[] = { NULL };  // filled in
static const char *Wdays_strs[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL };
static const char *WDAYS_strs[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", NULL };
static const char *weekdays_strs[] = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", NULL };
static const char *Weekdays_strs[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", NULL };
static const char *WEEKDAYS_strs[] = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", NULL };
static const char *weekdayz_strs[] = { "monday", "tuesday", "wednesday", "thursday", "friday", NULL }; // so
static const char *Weekdayz_strs[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", NULL }; // do 
static const char *WEEKDAYZ_strs[] = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", NULL }; // these

const STRING_GROUP wdays_group = { .name = "wdays", .strs = wdays_strs, .opts = 0x0 };
const STRING_GROUP wdayz_group = { .name = "wdayz", .strs = wdayz_strs, .opts = 0x0 };
const STRING_GROUP Wdayz_group = { .name = "Wdayz", .strs = Wdayz_strs, .opts = 0x0 };
const STRING_GROUP Wdays_group = { .name = "Wdays", .strs = Wdays_strs, .opts = 0x0 };
const STRING_GROUP WDAYZ_group = { .name = "WDAYZ", .strs = WDAYZ_strs, .opts = 0x0 };
const STRING_GROUP WDAYS_group = { .name = "WDAYS", .strs = WDAYS_strs, .opts = 0x0 };
const STRING_GROUP weekdays_group = { .name = "weekdays", .strs = weekdays_strs, .opts = 0x0 };
const STRING_GROUP weekdayz_group = { .name = "weekdayz", .strs = weekdayz_strs, .opts = 0x0 };
const STRING_GROUP Weekdays_group = { .name = "Weekdays", .strs = Weekdays_strs, .opts = 0x0 };
const STRING_GROUP Weekdayz_group = { .name = "Weekdayz", .strs = Weekdayz_strs, .opts = 0x0 };
const STRING_GROUP WEEKDAYS_group = { .name = "WEEKDAYS", .strs = WEEKDAYS_strs, .opts = 0x0 };
const STRING_GROUP WEEKDAYZ_group = { .name = "WEEKDAYZ", .strs = WEEKDAYZ_strs, .opts = 0x0 };

// const STRING_GROUP String_Groups[] = { wdays_group, wdayz_group, Wdayz_group, WDAYZ_group, Wdays_group, NULL };

STRING_GROUP String_Groups[] = { { .name = "wdays", .strs = wdays_strs, .opts = 0x0 }, 
                                 { .name = "wdayz", .strs = wdayz_strs, .opts = 0x0 },
                                 { .name = "Wdayz", .strs = Wdayz_strs, .opts = 0x0 },
                                 { .name = "Wdays", .strs = Wdays_strs, .opts = 0x0 },
                                 { .name = "WDAYZ", .strs = WDAYZ_strs, .opts = 0x0 },
                                 { .name = "WDAYS", .strs = WDAYS_strs, .opts = 0x0 },
                                 { .name = "weekdays", .strs = weekdays_strs, .opts = 0x0 },
                                 { .name = "weekdayz", .strs = weekdayz_strs, .opts = 0x0 },
                                 { .name = "Weekdays", .strs = Weekdays_strs, .opts = 0x0 },
                                 { .name = "Weekdayz", .strs = Weekdayz_strs, .opts = 0x0 },
                                 { .name = "WEEKDAYS", .strs = WEEKDAYS_strs, .opts = 0x0 },
                                 { .name = "WEEKDAYZ", .strs = WEEKDAYZ_strs, .opts = 0x0 },
                                 { .name = NULL, .strs = NULL, .opts = 0x0, }, NULL };

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
