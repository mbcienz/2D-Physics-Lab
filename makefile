# compiler to use
CC = gcc

# flags: include path, warnings, and debug symbols
CFLAGS = -Iinclude -Wall -g

# fetch sdl2 flags using pkg-config
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl2 SDL2_ttf)

# link the math library
MATH_FLAGS = -lm

# automatically find all .c files inside the src directory
CORE_SRC = $(shell find src -name "*.c")

# automatically generate object files (.o) for the core files
CORE_OBJ = $(CORE_SRC:.c=.o)

# default rule if you just type 'make' (compiles everything)
all: vector camera

# target for the vector demo
# run it with: make vector
vector: $(CORE_OBJ) demo/drawing_vector.o
	$(CC) $(CORE_OBJ) demo/drawing_vector.o -o vector_demo.exe $(SDL_FLAGS) $(MATH_FLAGS)

#target for the camera control demo
# run it with: make camera
camera: $(CORE_OBJ) demo/camera_control.o
	$(CC) $(CORE_OBJ) demo/camera_control.o -o camera_control.exe $(SDL_FLAGS) $(MATH_FLAGS)


# compilation step for every individual .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean up object files and all executables
clean:
	rm -f $(CORE_OBJ) demo/*.o *.exe