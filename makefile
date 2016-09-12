# Declare a variable for the compliler which we are going to use
CXX=g++

# Declare another variable with the flags which we are going to use
CXXFLAGS_MAC=-g -Wall -std=c++11 -framework OpenGl -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

OBJDIR=build

default: testing

opengl4: testing4

testing: clean init linmath.hpp
	$(CXX) $(CXXFLAGS_MAC) main.cpp -o $(OBJDIR)/quadtree

testing4: clean init linmath.hpp
	$(CXX) $(CXXFLAGS_MAC) -DGL3 main_gl4.cpp -o $(OBJDIR)/quadtree_gl4


init: 
	- mkdir -p $(OBJDIR)

clean:
	- rm -rf $(OBJDIR)