# Coded by Philip Simonson. (AKA DevCool)

OBJS=Main.o GameClass.o
EXECUTABLE=game
CC=g++
CXX=$(CC)
CFLAGS=-std=c++11 -O2 -Wall
CXXFLAGS=$(CFLAGS)
LIBS=-lsfml-window -lsfml-system -lGL -lGLU
LD=$(CXX)

all: $(EXECUTABLE)

rebuild: clean all

$(EXECUTABLE): $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	@echo Cleaning up...
	@rm *.o $(EXECUTABLE)
	@echo Done.
