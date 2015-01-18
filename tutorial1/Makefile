CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lSDLmain -lSDL -lGL -lGLU
SOURCES=CApp.cpp CApp_OnInit.cpp CApp_OnEvent.cpp CApp_OnLoop.cpp CApp_OnRender.cpp CApp_OnCleanup.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Game

all: clean $(SOURCES) $(EXECUTABLE) clean2

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)

clean2:
	rm -f *.o

