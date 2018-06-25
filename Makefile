#
# GNU Makefile to compile static and dynamic strglob library types with driver code and unit testing
#
# Written by: Derek Callaway [decal (AT) sdf {D0T} org]
#

CC = gcc
INSTALL = install
LN = ln
LNFLAGS = -s -f -v 
# CFLAGS = -g -Wall -pedantic -fPIC -fopenmp -I. -O0 -DSTRGLOB_ENVIRON_EXPAND -DSTRGLOB_FILE_INCLUDES # -D_FORTITY_SOURCE=2 -fstack-check -fstack-protector-all -fsanitize=alignment -D_ISOC99_SOURCE -DDEBUG_STRGLOB
CFLAGS = -g -Wall -pedantic -fPIC -I. -O0 -DSTRGLOB_ENVIRON_EXPAND -DSTRGLOB_FILE_INCLUDES -D_FORTITY_SOURCE=2 -fstack-check -fstack-protector-all -fsanitize=alignment -D_ISOC99_SOURCE # -DDEBUG_STRGLOB -fopenmp
LIBS = -lstrglob -L.
LIBS_CHECK = -lcheck -lm -lrt -lstrglob 
SRCS = copy_strglob.c calc_setlens.c cartesian_product.c cons_float2str.c cons_glob2ints.c cons_glob2astras.c cons_str2glob.c cons_str2strs.c cons_char2str.c enum_intseq.c exit_verbose.c count_commas.c count_lines.c float_range.c fputs_strglob.c handle_strglob.c imply_float_range.c imply_range.c measure_float.c measure_integer.c strglob_error.c open_bracket.c open_brace.c open_paren.c next_string.c char_class.c char_range.c string_class.c init_strglob.c show_usage.c
OBJS = $(SRCS:.c=.o) 
EXE = strglob
CFLAGS_LIB = 
CFLAGS_STATIC = -static
CFLAGS_SHARED = -fPIC -shared
TARGET_SHARED = libstrglob.so
TARGET_SHARED_LINK = $(TARGET_SHARED).1.0.0
TARGET_STATIC = libstrglob.a 
STRGLOB_HEADER = strglob.h
LIB_INSTALL = /usr/local/lib
BIN_INSTALL = /usr/local/bin
INC_INSTALL = /usr/local/include

all: $(OBJS) $(TARGET_SHARED) $(TARGET_STATIC) $(EXE)

$(TARGET_SHARED): $(OBJS) string_class.h strglob.h
	$(CC) $(CFLAGS) $(CFLAGS_LIB) $(CFLAGS_SHARED) -o $(TARGET_SHARED) *.o 

$(TARGET_STATIC): $(OBJS)
	ar rcs $(TARGET_STATIC) *.o 

$(EXE): $(OBJS) main_function.c strglob.h string_class.h
	LD_LIBRARY_PATH=. $(CC) $(CFLAGS) -g main_function.c -o $(EXE) $(LIBS)

#$(OUTS): $(SRCS)
#	$(CC) $(CFLAGS) -c $(subst output,,$@.c) $(LIBS)

clean: 
	$(RM) *.o

# https://wikipedia.org/wiki/Clobbering
clobber: clean
	$(RM) $(EXE) $(TARGET_SHARED) $(TARGET_STATIC)

test: tests/check.c
	$(CC) -g -pthread $(CFLAGS) $(CFLAGS_LIB) tests/check.c -o check $(LIBS_CHECK)

install: all
	$(INSTALL) $(TARGET_SHARED) $(TARGET_STATIC) $(LIB_INSTALL)
	$(INSTALL) $(EXE) $(BIN_INSTALL)
	$(INSTALL) $(STRGLOB_HEADER) $(INC_INSTALL)
	$(LN) $(LNFLAGS) $(LIB_INSTALL)/$(TARGET_SHARED) $(LIB_INSTALL)/$(TARGET_SHARED_LINK)
