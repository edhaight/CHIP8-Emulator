# A simple Makefile for compiling small SDL projects

# # set the compiler
# CC := clang

# set the compiler flags
# 
# 
CFLAGS :=  -ggdb3 --std=c99 -Wall -Wextra -pedantic -Iinclude
SDL := `sdl2-config --cflags --libs` -lSDL2_image

HDRS := $(wildcard include/*.h)
SRC := $(wildcard src/*.c)

ODIR := obj
_OBJS := main.o chip8.o display.o instruction.o
OBJS := $(patsubst %,$(ODIR)/%,$(_OBJS))

CLEANUP := chip8 *.core

# name of executable
EXEC := chip8

# default recipe
all: $(EXEC)

# recipe for building object files
$(ODIR)/%.o: src/%.c $(HDRS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(SDL) $(CFLAGS)

# recipe for running test rom
test: $(EXEC)
	-@./$(EXEC) test/jumpingXO.ch8 2>/dev/null || true

# recipe for cleaning workspace
clean: 
	@rm -f $(CLEANUP) 
	@rm -rf $(ODIR)

.PHONY: all clean

-include $(ODIR)/*.d