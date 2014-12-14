CC=g++
CFLAGS=-c -O2
LDFLAGS=-lSDLmain -lSDL -lSDL_mixer -lGL -lGLU
SOURCES=camera.cpp collision.cpp collisionplane.cpp collisionsphere.cpp functions.cpp game.cpp item.cpp knife.cpp level.cpp main.cpp menu.cpp object.cpp objloader.cpp pengine.cpp player.cpp skybox.cpp text.cpp vector.cpp weapon.cpp zombie.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=shooter

all: $(SOURCES) $(EXECUTABLE) clean.objs

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o shooter

clean.objs:
	rm -f *.o
