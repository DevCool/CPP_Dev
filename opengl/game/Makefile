OBJS=CCamera.o CObjLoader.o CApp.o Main.o
CFLAGS=-O2 -Wall -ggdb
CXXFLAGS=${CFLAGS}
LD=g++ -ggdb

EXEC=game

all: $(EXEC)

rebuild: clean $(EXEC)

$(EXEC): $(OBJS)
	$(LD) $(CXXFLAGS) $(OBJS) -o $@ -lGL -lGLU -lSDLmain -lSDL -lSDL_image

clean:
	@echo Cleaning up...
	@rm *.o $(EXEC)
	@echo Done.
