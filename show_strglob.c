#include"strglob.h"

void show_strglob(STR_GLOB *ugpnt) {
  while(ugpnt) {
    if(!ugpnt->type) {
      if(ugpnt->str && *(ugpnt->str))
        puts(ugpnt->str);

      /* 1 = integer range, 2 = character range, 3 = set */
    } else if(ugpnt->type == 4) { /* character class */
      for(register char *restrict p = ugpnt->str;*p;++p)
        putchar(*p);

      putchar('\n');
    } else if(ugpnt->type == 3) { /* set */
      register char *const *pp = ugpnt->out;

      if(pp) 
        while(*pp) 
          puts(*pp++);
    } else { /* some type of range */
      if(!ugpnt->out)
        ugpnt->out = array_range(ugpnt);

      while(ugpnt->out && *(ugpnt->out)) {
        puts(*(ugpnt->out));

        (ugpnt->out)++;
      }
    }

    ugpnt = ugpnt->next;
  }

  return;
}
