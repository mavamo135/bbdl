# The compiler to use
CC= gcc
# Compiler flgas
#	-Wall turn on most, but not all, compiler warnings
CFLAGS= -ansi -Wall -std=c99 -c
# Objects directory
OBJ_DIR= obj
# Drivers directory
SRC_DIR= drivers
# Objects
SRC= $(wildcard $(SRC_DIR)/*c)
OBJ= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ+= $(OBJ_DIR)/main.o

all: directories project

project: $(OBJ) 
	gcc -o $@ $^
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I$(SRC_DIR) $(CFLAGS) $< -o $@
	
$(OBJ_DIR)/main.o: main.c
	$(CC) -I$(SRC_DIR) $(CFLAGS) $^ -o $@

.PHONY: directories
directories:
	mkdir -p obj

.PHONY: clean	
clean:
	rm -f $(OBJ) project
	rmdir obj
