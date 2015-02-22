OBJS=Main.o Application.o Camera.o
EXECUTABLE=mygame
CC=g++ -g
CXX=$(CC)
CFLAGS=-std=c++11 -O2 -Wall -g
CXXFLAGS=$(CFLAGS)
LD=$(CXX)

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o $@ `sdl-config --cflags --libs` -lGL -lGLU

clean:
	@echo Cleaning up...
	@rm *.o
	@echo Done.

cleanest:
	@rm $(EXECUTABLE)