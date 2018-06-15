#include"strglob.h"

int main(int argc, char *argv[]) {
  if(argc < 2)
    show_usage(*argv);

  const HAND_GLOB *hand = handle_strglob(argv[1]);

  if(!hand) {
    fputs("*** Failure!\n", stderr);

    exit(EXIT_FAILURE);
  }

  fputs_strglob(hand->glob, hand->size, stdout);

  exit(EXIT_SUCCESS);
}
