#Makefile Testing
#Coded by Philip Simonson. (AKA DevCool)

CC=g++
CFLAGS=-O2 -Wall -I./game
LDFLAGS=-lglfw -lGL -lGLU -lGLEW
GDIR=game

all: fps clean

.PHONY: clean cleanest

fps: main.o GameManager.o RenderSystem.o VertexBuffer.o ShaderLoader.o ShaderInterface.o ResourceManager.o
	$(CC) $(LDFLAGS) main.o GameManager.o RenderSystem.o VertexBuffer.o ShaderLoader.o ShaderInterface.o ResourceManager.o -o fps

main.o:	$(GDIR)/main.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/main.cpp

GameManager.o: $(GDIR)/GameManager.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/GameManager.cpp

RenderSystem.o: $(GDIR)/RenderSystem.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/RenderSystem.cpp

VertexBuffer.o:	$(GDIR)/VertexBuffer.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/VertexBuffer.cpp

ShaderLoader.o: $(GDIR)/ShaderLoader.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/ShaderLoader.cpp

ShaderInterface.o: $(GDIR)/ShaderInterface.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/ShaderInterface.cpp

ResourceManager.o: $(GDIR)/ResourceManager.cpp
	$(CC) $(CFLAGS) -c $(GDIR)/ResourceManager.cpp

clean:
	rm *.o

cleanest:
	rm fps

