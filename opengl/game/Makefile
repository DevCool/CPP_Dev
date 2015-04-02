OBJS=CCamera.o Functions.o CObjLoader.o CApp.o Main.o
CFLAGS=-O2 -Wall
CXXFLAGS=${CFLAGS}
LD=g++

EXEC=game

all: $(EXEC)

rebuild: clean $(EXEC)

$(EXEC): $(OBJS)
	$(LD) $(CXXFLAGS) $(OBJS) -o $@ -lGL -lGLU -lSDLmain -lSDL -lSDL_image

debug: $(OBJS)
	$(LD) $(CXXFLAGS) -ggdb $(OBJS) -o $@ -lGL -lGLU -lSDLmain -lSDL -lSDL_image

clean:
	@echo Cleaning up...
	@rm *.o $(EXEC)
	@echo Done.
