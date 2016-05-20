# C compiler
CC := gcc

# Libraries
LIBS := -lncurses

# Include directory
INCLUDE := -Iheaders

# Code directory
CODE := code

# Editor source directory
EDITOR := editor

# Display source directory
DISPLAY := display

EDITOR_OBJS := \
main.o \
$(CODE)/$(EDITOR)/structs.o \
$(CODE)/$(EDITOR)/chars.o \
$(CODE)/$(EDITOR)/ncurses_interface.o \
$(CODE)/$(DISPLAY)/display.o \

OBJS := \
$(EDITOR_OBJS) \

# Output file name
OUT_FILE := editor.o

# Targets
all : editor

.PHONY : all clean

clean :
	rm $(OBJS) $(OUT_FILE)

editor: $(OBJS)
	$(CC) $(OBJS) -g -o $(OUT_FILE) $(LIBS)

%.o : %.c
	$(CC) -c $< -g -o $@ $(INCLUDE)
