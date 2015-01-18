CC=g++
CFLAGS=-O2
CFLAGS2=-c -Wall
LDFLAGS=-lSDL2main -lSDL2
#LDFLAGS2=-lSDL2main -lSDL2 -lSDL2_image


all: clean tut tut1 tut2 tut3 clean2

tut: tut.o initClass.o
	$(CC) $(CFLAGS) tut.o initClass.o -o $@ $(LDFLAGS)

tut.o: tut.cpp
	$(CC) $(CFLAGS2) tut.cpp

initClass.o: initClass.cpp
	$(CC) $(CFLAGS2) initClass.cpp

tut1: tut1.o initClass.o testClass.o
	$(CC) $(CFLAGS) tut1.o initClass.o testClass.o -o $@ $(LDFLAGS)

tut1.o: tut1.cpp
	$(CC) $(CFLAGS2) tut1.cpp

testClass.o: testClass.cpp
	$(CC) $(CFLAGS2) testClass.cpp

tut2: tut2.o initClass.o testClass.o testClass2.o
	$(CC) $(CFLAGS) tut2.o initClass.o testClass.o testClass2.o -o $@ $(LDFLAGS)

tut2.o: tut2.cpp
	$(CC) $(CFLAGS2) tut2.cpp

testClass2.o: testClass2.cpp
	$(CC) $(CFLAGS2) testClass2.cpp

tut3: tut3.o initClass.o testClass.o testClass3.o
	$(CC) $(CFLAGS) tut3.o initClass.o testClass.o testClass3.o -o $@ $(LDFLAGS)

tut3.o: tut3.cpp
	$(CC) $(CFLAGS2) tut3.cpp

testClass3.o: testClass3.cpp
	$(CC) $(CFLAGS2) testClass3.cpp

clean:
	rm -f *.o tut tut1 tut2 tut3

clean2:
	rm -f *.o

