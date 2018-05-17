#include"strglob.h"
#include"string_class.h"

//sclnm is the name of the string class we want it loops like. stuff like "wdays".
//I'm probably going to do some hash table and initialize it on the first lookup
//urglb is a structure that contains a pointer that we need to point at space that contains an array of strings.
//do not know if it gets
int string_class(const char *sclnm, STR_GLOB *urglb) {
  int invalid_class = 1;
  int len;

//  for(register char **snp = stype_strs;*snp;++snp) {//is this really needed? we do manual checks and compares later.
//    if(!strcmp(*snp, sclnm)) {
//      invalid_class = 0;
//
//      break;
//    }
//  }
  int i;
  for(i=0;strgrp[i].name;i++) {
    if(!strcmp(strgrp[i].name,sclnm)) {
      invalid_class = 0;
      break;//we can reuse this 'i' later.
    }
  }

  if(invalid_class)
    return 1;

  urglb->type = 5; //I bet this is just to set to 5 to say "we're a string class" to other parts of the program.

  register char **wp=0;
  wp=strgrp[i].strs;
  if(!wp) return 1;//invalid class.
  for(len=0;wp[len];len++);

//  fprintf(stderr,"len: %d\n",len);
    
  urglb->out = malloc((len+1) * sizeof *(urglb->out));

  if(!urglb->out)
    exit_verbose("malloc", __FILE__, __LINE__);

  register char **pp = urglb->out;

  while(*wp)
    *pp++ = *wp++;
  *pp++ = NULL;

  return 0; 
}
