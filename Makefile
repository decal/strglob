#
# GNU Makefile to compile static and dynamic strglob libraries with driver code and unit testing
#
# Written by: Derek Callaway [decal (AT) sdf {D0T} org]
#

CC = gcc
CFLAGS = -fPIC -std=c11 -fopenmp -fopenmp-simd -fopenacc -Wall -pedantic -O2 -g -I. -D_FORTITY_SOURCE=2 -fstack-check -fstack-protector-all -fsanitize=alignment
LIBS = -lstrglob -L.
SRCS = count_commas.c count_strglob.c count_strptrs.c show_strglob.c showall_strglob.c array_range.c show_usage.c integer_length.c strglob_error.c open_bracket.c open_brace.c next_string.c char_class.c open_paren.c string_class.c write_strptrs.c set_difer.c set_union.c dis_union.c
OBJS = $(SRCS:.c=.o) 
EXE = strglob
CFLAGS_SHARED = -fPIC
CFLAGS_STATIC = -fPIC
LDFLAGS_SHARED = -shared
LDFLAGS_STATIC = -static
TARGET_SHARED = libstrglob.so
TARGET_STATIC = libstrglob.a

.PHONY: all clean rebuild

$(TARGET_SHARED): $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) $(LDFLAGS_SHARED) -o $(TARGET_SHARED) *.o 

$(TARGET_STATIC): $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_STATIC) $(LDFLAGS_STATIC) -o $(TARGET_STATIC) *.o 

main_function.o: main_function.c
	$(CC) $(CFLAGS) -c $(subst output,,$@.c) $(LIBS)

$(EXE): $(OBJS) main_function.o
	LD_LIBRARY_PATH=. $(CC) $(CFLAGS) -o $(EXE) *.o $(LIBS)

all: $(OBJS) $(TARGET_SHARED) $(EXE)

rebuild: clean all

$(OUTS): $(SRCS)
	$(CC) $(CFLAGS) -c $(subst output,,$@.c) $(LIBS)

clean: clobber
	$(RM) $(OBJS)

clobber: 
	$(RM) $(EXE) $(TARGET_SHARED) $(TARGET_STATIC) $(OUTS)
