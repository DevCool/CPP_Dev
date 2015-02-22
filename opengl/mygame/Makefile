OBJS=Main.o Application.o

CFLAGS=-O2 -Wall -g
LD=g++ -g

all: $(OBJS)
	$(LD) $(CFLAGS) $(OBJS) -o mygame `sdl-config --cflags --libs` -lGL -lGLU

clean:
	@echo Cleaning up...
	@rm *.o mygame
	@echo Done.
