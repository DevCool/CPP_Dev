OBJS=Main.o Application.o Camera.o

CFLAGS=-O2 -Wall -g
LD=g++ -g

all: game

game: $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o mygame `sdl-config --cflags --libs` -lGL -lGLU

clean:
	@echo Cleaning up...
	@rm *.o mygame
	@echo Done.
