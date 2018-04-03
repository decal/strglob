#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>

void show_usage(const char *const anarg) {
  fprintf(stderr, "usage: %s STRING\n", anarg);

  exit(EX_USAGE);
}
