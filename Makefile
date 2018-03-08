#
# GNU Makefile to compile static and dynamic strglob library types with driver code and unit testing
#
# Written by: Derek Callaway [decal (AT) sdf {D0T} org]
#

CC = gcc
CFLAGS = -fPIC -std=c11 -fopenmp -fopenmp-simd -fopenacc -Wall -pedantic -O2 -g -I. -D_FORTITY_SOURCE=2 -fstack-check -fstack-protector-all -fsanitize=alignment
LIBS = -lstrglob -L.
SRCS = count_commas.c count_strglob.c count_strptrs.c show_strglob.c showall_strglob.c array_range.c integer_length.c strglob_error.c open_bracket.c open_brace.c next_string.c char_class.c open_paren.c string_class.c write_strptrs.c set_difer.c set_union.c dis_union.c init_strglob.c elem_advance.c show_helper.c last_element.c
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

$(EXE): $(OBJS) main_function.c show_usage.c
	LD_LIBRARY_PATH=. $(CC) $(CFLAGS) main_function.c -o $(EXE) *.o $(LIBS)

all: $(OBJS) $(TARGET_SHARED) $(EXE)

rebuild: clean all

#$(OUTS): $(SRCS)
#	$(CC) $(CFLAGS) -c $(subst output,,$@.c) $(LIBS)

clean: 
	$(RM) $(OBJS)

clobber: clean
	$(RM) $(EXE) $(TARGET_SHARED) $(TARGET_STATIC) $(OBJS)
