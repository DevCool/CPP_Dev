OBJS=Main.o Application.o
CPP=g++
CPPFLAGS=-O2 -Wall
LIBS=-lglfw -lGLEW -lGL
EXEC=testing-ground

all: $(EXEC)

rebuild: clean all

$(EXEC): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	@echo Cleaning project...
	@rm *.o $(EXEC)
	@echo Done.
