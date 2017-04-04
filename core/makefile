# OBJS specifies which files to compile as part of the project
OBJS = tests

OUTPUTDIR = build

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -std=c++11

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework OpenGL -lglfw3 -lglew

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cgdisplay

#This is the target that compiles our executable
all : clean $(OBJS)

tests: cgdisplay rawmodel
	$(CC) tests.cpp $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUTDIR)/tests $(OUTPUTDIR)/cgdisplay.o $(OUTPUTDIR)/cgrawmodel.o

cgdisplay : cgdisplay.hpp
	$(CC) cgdisplay.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgdisplay.o

loader : rawmodel.hpp cgloader.hpp 
	$(CC) cgloader.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgloader.o

rawmodel : cgrawmodel.hpp
	$(CC) cgrawmodel.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgrawmodel.o


clean:
	- rm -rf $(OUTPUTDIR)
	- mkdir -p $(OUTPUTDIR)