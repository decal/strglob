#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>

void show_version(const char *const anarg) {
  fputs("\n<== strglob 1.0 ==>\n\n", stderr);
  fputs("Written by Derek Callaway\n", stderr);
  fprintf(stderr, "Compiled Date: %s\n", __DATE__);
  fprintf(stderr, "Compiled Time: %s\n", __TIME__);
  fprintf(stderr, "Standard C Version: %ld\n\n", __STDC_VERSION__);

  exit(EX_OK);
}
