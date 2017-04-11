# OBJS specifies which files to compile as part of the project
OBJS = tests

OUTPUTDIR = build

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
# INCLUDE_PATHS = -I/Users/tanerselim/Dev/antons_opengl_tutorials_book/common/include -I/usr/local/include 
INCLUDE_PATHS =  -I/usr/local/include 

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib 
# LIB_P = /Users/tanerselim/Dev/antons_opengl_tutorials_book/common/osx_64/
LIB_P = /usr/local/lib/
LOC_LIB = $(LIB_P)libGLEW.a $(LIB_P)libglfw3.a

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++11 -DAPPLE -Wall -pedantic -arch x86_64 -fmessage-length=0 -UGLFW_CDECL -ftest-coverage

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework OpenGL -lpng -framework Cocoa -framework IOKit -framework CoreVideo

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cgdisplay

#This is the target that compiles our executable
all : clean $(OBJS) standalone

standalone : 
	$(CC) tests_standalone.cpp $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUTDIR)/standalone $(LOC_LIB)

tests: cgdisplay rawmodel loader renderer shader staticshader texture 
	$(CC) tests.cpp $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUTDIR)/tests $(OUTPUTDIR)/cgdisplay.o $(OUTPUTDIR)/cgrawmodel.o $(OUTPUTDIR)/cgloader.o $(OUTPUTDIR)/cgrenderer.o $(OUTPUTDIR)/cgshader.o $(OUTPUTDIR)/cgstaticshader.o $(OUTPUTDIR)/cgtexture.o $(LOC_LIB)

cgdisplay : cgdisplay.hpp
	$(CC) cgdisplay.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgdisplay.o

loader : rawmodel texture cgloader.hpp 
	$(CC) cgloader.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgloader.o

renderer : rawmodel cgrenderer.hpp 
	$(CC) cgrenderer.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgrenderer.o

rawmodel : cgrawmodel.hpp
	$(CC) cgrawmodel.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgrawmodel.o

staticshader : shader cgstaticshader.hpp
	$(CC) cgstaticshader.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgstaticshader.o

shader : cgshader.hpp
	$(CC) cgshader.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgshader.o

texture : cgtexture.hpp 
	$(CC) cgtexture.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgtexture.o

clean:
	- rm -rf $(OUTPUTDIR)
	- mkdir -p $(OUTPUTDIR)