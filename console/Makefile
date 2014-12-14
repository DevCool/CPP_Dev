CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
SRC1=main.cpp
OBJ1=$(SRC1:.cpp=.o)
EXE1=console

all: $(SRC1) $(EXE1) clean.objs

$(EXE1): $(OBJ1)
	$(CC) $(LDFLAGS) $(OBJ1) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXE1)

clean.objs:
	rm -f *.o
