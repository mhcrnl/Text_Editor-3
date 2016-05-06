# #######################################################
# OVERALL CONFIG
# #######################################################
# C compiler
CC := gcc
# Libraries
LIBS := -lncurses
# Compiler flags
CFLAGS := -g

# #######################################################
# DIRECTORY CONFIG
# #######################################################

EDITOR_DIR := editor/
HEADER_DIR := headers/

# #######################################################
# OBJECTS
# #######################################################

MAIN := main.o
EDITOR_OBJS := \
$(EDITOR_DIR)chars.o \
$(EDITOR_DIR)cursor.o \
$(EDITOR_DIR)display.o \
$(EDITOR_DIR)structs.o \
$(EDITOR_DIR)utility.o \

OBJS := $(MAIN) $(EDITOR_OBJS)

# #######################################################
# OUTPUT FILE NAME
# #######################################################

OUT_FILE := text_edit.out

# #######################################################
# TARGETS
# #######################################################

.PHONY : all clean

all : $(OUT_FILE)

$(OUT_FILE) : $(OBJS)
	$(CC) -o $@ -I$(HEADER_DIR) $(OBJS) $(LIBS) $(CFLAGS)

clean :
	rm -f $(OBJS) $(OUT_FILE)

%.o : %.c
	$(CC) -c $< -o $@ -I$(HEADER_DIR) $(CFLAGS)
