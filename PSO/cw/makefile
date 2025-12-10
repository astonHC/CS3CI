## COPYRIGHT (C) HARRY CLARK 2025
## BUILD SCHEME SPECIFIC TO PSO COURSEWORK IMPLEMENTATION

#####################################
## 			   PREFIXES
#####################################

CC				:= gcc
CSTD			:= --std=c99
CFLAGS			:= -fPIC -fno-common
WARNINGS		:= -Wall -Wextra -Wpedantic -Wunused-value -Wunused-parameter -O3

#####################################
## 			  DIRECTORIES
#####################################

SRC_DIR			:= .
PSO_SIMPLE_DIR	:= pso_simple
BUILD_DIR		:= build

#####################################
## 			SOURCE FILES
#####################################

CW_C_FILES		:= pso.c main.c
CW_H_FILES		:= pso.h
CW_O_FILES		:= $(patsubst %.c,$(BUILD_DIR)/%.o,$(CW_C_FILES))

SIMPLE_C_FILES	:= $(wildcard $(PSO_SIMPLE_DIR)/*.c)
SIMPLE_H_FILES	:= $(wildcard $(PSO_SIMPLE_DIR)/*.h)
SIMPLE_O_FILES	:= $(patsubst $(PSO_SIMPLE_DIR)/%.c,$(BUILD_DIR)/simple_%.o,$(SIMPLE_C_FILES))

#####################################
## 			    TARGETS
#####################################

.PHONY: all clean dirs cw simple

all: dirs cw

dirs:
	@mkdir -p $(BUILD_DIR)

cw: dirs $(BUILD_DIR)/pso_cw.exe

$(BUILD_DIR)/pso_cw.exe: $(CW_O_FILES)
	$(CC) $(CW_O_FILES) -o $@ -lm

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(CW_H_FILES)
	$(CC) -c $(CSTD) $(WARNINGS) $(CFLAGS) -o $@ $<

simple: dirs $(BUILD_DIR)/pso_simple.exe

$(BUILD_DIR)/pso_simple.exe: $(SIMPLE_O_FILES)
	$(CC) $(SIMPLE_O_FILES) -o $@ -lm

$(BUILD_DIR)/simple_%.o: $(PSO_SIMPLE_DIR)/%.c $(SIMPLE_H_FILES)
	$(CC) -c $(CSTD) $(WARNINGS) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)