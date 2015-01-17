CC=g++
CFLAGS=-O2
CFLAGS2=-c -Wall
LDFLAGS=-lSDL2main -lSDL2

all: clean tut1 tut2 clean2

tut1: tut1.o testClass.o
	$(CC) $(CFLAGS) tut1.o testClass.o -o $@ $(LDFLAGS)

tut1.o: tut1.cpp
	$(CC) $(CFLAGS2) tut1.cpp

testClass.o: testClass.cpp
	$(CC) $(CFLAGS2) testClass.cpp

tut2: tut2.o testClass.o testClass2.o
	$(CC) $(CFLAGS) tut2.o testClass.o testClass2.o -o $@ $(LDFLAGS)

tut2.o: tut2.cpp
	$(CC) $(CFLAGS2) tut2.cpp

testClass2.o: testClass2.cpp
	$(CC) $(CFLAGS2) testClass2.cpp

clean:
	rm -f *.o tut1 tut2

clean2:
	rm -f *.o
