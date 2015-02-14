CC=g++
CFLAGS=-O2 -Wall
LDFLAGS=-lSDLmain -lSDL -lGL -lGLU
EXES=tutorial1

all: $(EXES) clean_garbage

tutorial1:
	$(CC) $(CFLAGS) $@.cpp -o $@ $(LDFLAGS)

clean:
	rm -f *.o $(EXES)

clean_garbage:
	rm -f *.o *~
