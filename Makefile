#
# GNU Makefile to compile static and dynamic strglob library types with driver code and unit testing
#
# Written by: Derek Callaway [decal (AT) sdf {D0T} org]
#

CC = gcc
CFLAGS = -fPIC -Wall -pedantic -std=c11 -g -I. -O0 # -D_FORTITY_SOURCE=2 -fstack-check # -fstack-protector-all # -fsanitize=alignment # -DDEBUG_STRGLOB
LIBS = -lstrglob -L.
SRCS = calc_setlens.c cartesian_product.c conv_gl2ias.c conv_gl2sas.c enum_intseq.c exit_verbose.c count_commas.c imply_range.c measure_integer.c strglob_error.c open_bracket.c open_brace.c open_paren.c next_string.c char_class.c string_class.c init_strglob.c set_diff.c set_union.c 
OBJS = $(SRCS:.c=.o) 
EXE = strglob
CFLAGS_LIB = -fPIC
CFLAGS_STATIC = -static
CFLAGS_SHARED = -shared
TARGET_SHARED = libstrglob.so 
TARGET_STATIC = libstrglob.a 

.PHONY: all clean rebuild

$(TARGET_SHARED): $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_LIB) $(CFLAGS_SHARED) -o $(TARGET_SHARED) *.o 

$(TARGET_STATIC): $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_LIB) $(CFLAGS_STATIC) -o $(TARGET_STATIC) *.o 

$(EXE): $(OBJS) main_function.c 
	LD_LIBRARY_PATH=. $(CC) $(CFLAGS) main_function.c -o $(EXE) *.o $(LIBS)

all: $(OBJS) $(TARGET_SHARED) $(EXE)

rebuild: clean all

#$(OUTS): $(SRCS)
#	$(CC) $(CFLAGS) -c $(subst output,,$@.c) $(LIBS)

clean: 
	$(RM) $(OBJS)

clobber: clean
	$(RM) $(EXE) $(TARGET_SHARED) $(TARGET_STATIC) $(OBJS)
