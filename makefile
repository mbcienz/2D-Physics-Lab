# compiler to use
CC = gcc

# flags: include path, warnings, and debug symbols
CFLAGS = -Iinclude -Wall -g

# fetch sdl2 flags using pkg-config
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl2)

# link the math library
MATH_FLAGS = -lm

# automatically find all .c files inside the src directory
CORE_SRC = $(wildcard src/*.c)

# automatically generate object files (.o) for the core files
CORE_OBJ = $(CORE_SRC:.c=.o)

# default rule if you just type 'make' (compiles everything)
all: vector

# target for the vector demo
# run it with: make vector
vector: $(CORE_OBJ) demo/drawing_vector.o
	$(CC) $(CORE_OBJ) demo/drawing_vector.o -o vector_demo.exe $(SDL_FLAGS) $(MATH_FLAGS)

# target for a future demo (example)
# run it with: make sand
# sand: $(CORE_OBJ) demo/falling_sand.o
# 	$(CC) $(CORE_OBJ) demo/falling_sand.o -o sand_demo.exe $(SDL_FLAGS) $(MATH_FLAGS)

# compilation step for every individual .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean up object files and all executables
clean:
	rm -f src/*.o demo/*.o *.exe