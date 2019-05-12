

# Declare some variables to help construct our compile command
CC=g++         # the compiler
DEPS = factorial.h
FLAGS = -std=c++11
CFLAGS = -fPIC

OBJ= -o

volimage: main.o volimage.o
	$(CC) -o volimage volimage.o main.o -lm $(FLAGS) 


volimage.o: volimage.cpp volimage.hpp 
	$(CC) -c -o volimage.o volimage.cpp $(CFLAGS) $(FLAGS)
	
   

clean:
	@rm -f *.o
	@rm volimage
   

install:
  
	@mv volimage ~/bin
