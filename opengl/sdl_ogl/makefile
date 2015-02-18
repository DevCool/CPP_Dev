CC=g++
CFLAGS=-O2 -Wall
LDFLAGS=-lSDLmain -lSDL -lGL -lGLU
LDFLAGS2=-lSDLmain -lSDL -lSDL_image -lGL -lGLU
EXES=tutorial1 tutorial2 tutorial3

all: $(EXES) clean_garbage

tutorial1:
	$(CC) $(CFLAGS) $@.cpp -o $@ $(LDFLAGS)

tutorial2:
	$(CC) $(CFLAGS) $@.cpp -o $@ $(LDFLAGS)

tutorial3:
	$(CC) $(CFLAGS) $@.cpp functions.cpp -o $@ $(LDFLAGS2)

clean:
	rm -f *.o $(EXES)

clean_garbage:
	rm -f *.o *~
