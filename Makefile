WORKDIR = `pwd`

CC = gcc
AR = ar
LD = $(CC)

INC = -Iinclude
CFLAGS = -Wall

CFLAGS_DEBUG = $(CFLAGS) -Wall -g
OBJDIR_DEBUG = obj/Debug
OUT_DEBUG = lib/libmem-manager.a

CFLAGS_RELEASE = $(CFLAGS) -O2
LDFLAGS_RELEASE = -s
OBJDIR_RELEASE = obj/Release
OUT_RELEASE = build/libmem-manager.a

CFLAGS_TEST = $(CFLAGS) -O2
LIBDIR_TEST = -Llib
LIB_TEST = -lmem-manager
LDFLAGS_TEST = -s
OBJDIR_TEST = obj/Test
OUT_TEST = bin/testmain

OBJ_DEBUG = $(OBJDIR_DEBUG)/main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/main.o

OBJ_TEST = $(OBJDIR_TEST)/testmain.o

all: release

clean: clean_debug clean_release clean_test

before_debug: 
	test -d lib || mkdir -p lib
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

debug: before_debug out_debug

out_debug: before_debug $(OBJ_DEBUG)
	$(AR) rcs $(OUT_DEBUG) $(OBJ_DEBUG)

$(OBJDIR_DEBUG)/main.o: src/main.c
	$(CC) $(CFLAGS_DEBUG) $(INC) -c src/main.c -o $(OBJDIR_DEBUG)/main.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf lib
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d build || mkdir -p build
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

release: before_release out_release

out_release: before_release $(OBJ_RELEASE)
	$(AR) rcs $(OUT_RELEASE) $(OBJ_RELEASE)

$(OBJDIR_RELEASE)/main.o: src/main.c
	$(CC) $(CFLAGS_RELEASE) $(INC) -c src/main.c -o $(OBJDIR_RELEASE)/main.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf build
	rm -rf $(OBJDIR_RELEASE)

before_test: 
	test -d bin || mkdir -p bin
	test -d $(OBJDIR_TEST) || mkdir -p $(OBJDIR_TEST)

test: debug before_test out_test

out_test: before_test $(OBJ_TEST)
	$(LD) $(LIBDIR_TEST) -o $(OUT_TEST) $(OBJ_TEST)  $(LDFLAGS_TEST) $(LIB_TEST)

$(OBJDIR_TEST)/testmain.o: src/testmain.c
	$(CC) $(CFLAGS_TEST) $(INC) -c src/testmain.c -o $(OBJDIR_TEST)/testmain.o

clean_test: 
	rm -f $(OBJ_TEST) $(OUT_TEST)
	rm -rf bin
	rm -rf $(OBJDIR_TEST)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release before_test after_test clean_test

