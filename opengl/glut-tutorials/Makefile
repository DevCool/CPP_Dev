FILENAME=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
EXECUTABLE=$(patsubst %.cpp,%,$(wildcard *.cpp))
LIBS=-lglut -lGL -lGLU -lGLEW
CPP=g++
CPPFLAGS=-O2 -Wall

all: $(FILENAME) $(EXECUTABLE)

rebuild: clean all

% : %.o
	$(CPP) $(CPPFLAGS) $< -o $@ $(LIBS)

%.o : %.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

clean :
	@echo Cleaning objects and executables...
	@rm *.o $(EXECUTABLE)
	@echo Cleaning done.
