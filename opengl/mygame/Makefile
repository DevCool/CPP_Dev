# Coded by Philip Simonson. (AKA DevCool)

OBJS=Main.o Application.o Camera.o ObjLoader.o ResourceManager.o
EXECUTABLE=mygame
CC=g++
CXX=$(CC)
CFLAGS=-std=c++11 -O2 -Wall
CXXFLAGS=$(CFLAGS)
LD=$(CXX)

all: $(EXECUTABLE)

rebuild: clean all

$(EXECUTABLE): $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o $@ -lSDLmain -lSDL -lGL -lGLU

clean:
	@echo Cleaning up...
	@rm *.o $(EXECUTABLE)
	@echo Done.

