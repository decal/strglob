#ifndef _STRING_CLASS_H
#define _STRING_CLASS_H

// HACK: that 64 down there in char *strs[64].
// not sure of the best way to get rid of it right now.
// it will use up more space than needed... or I could make the string class config uglier.
// will try to think of a better way.
// this way at least prevents having to copy a list of class names between two different spots by hand.

#define MAX_STRINGS_PER_CLASS 16 //this can be tuned to lowest needed.. looks like it will need to be at least 200 or so because of countries.

typedef struct _string_groups {
  const char *name;
  int opts;
  char *strs[MAX_STRINGS_PER_CLASS];//if this isn't flexible it works a lot nicer. but it also takes up at least this much space for each structure.
} STRING_GROUPS;

/* if the string class ends in a 'z', then don't include the weekend days */
STRING_GROUPS strgrp[] = {

 { .name="wdayz", .opts=0, .strs = { "mon", "tue", "wed", "thu", "fri", NULL }},
 { .name="Wdayz", .opts=0, .strs = { "Mon", "Tue", "Wed", "Thu", "Fri", NULL }},
 { .name="WDAYZ", .opts=0, .strs = { "MON", "TUE", "WED", "THU", "FRI", NULL }},

 { .name="wdays", .opts=0, .strs = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL }},
 { .name="Wdays", .opts=0, .strs = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL }},
 { .name="WDAYS", .opts=0, .strs = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", NULL }},

 { .name="weekdays", .opts=0, .strs = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", NULL }},
 { .name="Weekdays", .opts=0, .strs = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", NULL }},
 { .name="WEEKDAYS", .opts=0, .strs = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", NULL }},

 { .name="weekdayz", .opts=0, .strs = { "monday", "tuesday", "wednesday", "thursday", "friday", NULL }},
 { .name="Weekdayz", .opts=0, .strs = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", NULL }},
 { .name="WEEKDAYZ", .opts=0, .strs = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", NULL }},

 { .name="months", .opts=0, .strs = { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december", NULL }},
 { .name="Months", .opts=0, .strs = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December", NULL }},
 { .name="MONTHS", .opts=0, .strs = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER", NULL }},

 { .name="mons", .opts=0, .strs = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec", NULL }},
 { .name="Mons", .opts=0, .strs = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", NULL }},
 { .name="MONS", .opts=0, .strs = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC", NULL }},

 { .name="decints", .opts=0, .strs = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero", NULL }},
 { .name="Decints", .opts=0, .strs = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Zero", NULL }},
 { .name="DECINTS", .opts=0, .strs = {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "ZERO", NULL }},

 { .name=NULL, .opts=0, .strs={NULL}} //end marker
};

/* co, Co, CO, country, Country, COUNTRY */ /* us, Us, US, united states, United States, UNITED STATES */
/* continent, Continent, CONTINENT */ /* i.e. north america, North America, NORTH AMERICA */
/* os, Os, OS */ /* i.e. linux, Linux, LINUX */
/* platformxx, Platformxx, platform_xx, Platform_xx PLATFORMXX, PLATFORM_XX */ /* i.e. x64, X64, x86_64, X86_64, Intel64, INTEL64 */

/* if you need ideas, check https://github.com/decal/werdlists */

/* would be nice to define flags representing formatting functions to be applied like toupper(), camelcase(), capitalize(),  etc. */

#endif
