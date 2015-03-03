OBJS=CApp.o Main.o
CFLAGS=-O2 -Wall
CXXFLAGS=${CFLAGS}
LD=g++

EXEC=game

all: $(EXEC)

rebuild: clean $(EXEC)

$(EXEC): $(OBJS)
	$(LD) $(CXXFLAGS) $(OBJS) -o $@ -lGL -lGLU -lSDLmain -lSDL

clean:
	@echo Cleaning up...
	@rm *.o $(EXEC)
	@echo Done.
