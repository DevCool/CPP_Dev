#Makefile Testing
#Coded by Philip Simonson. (AKA DevCool)

CC=g++
CFLAGS=-O2 -Wall -I./game/ -I./game/RenderSystem/
LDFLAGS=-lglfw -lGL -lGLU
GDIR=game/
RENDERSYSTEM_DIR=game/RenderSystem/

all: fps clean

.PHONY: clean cleanest

fps: main.o GameManager.o RenderSystem.o VertexBuffer.o ShaderLoader.o ShaderInterface.o
	$(CC) $(LDFLAGS) main.o GameManager.o RenderSystem.o VertexBuffer.o ShaderLoader.o ShaderInterface.o -o fps

main.o:	main.cpp
	$(CC) $(CFLAGS) -c main.cpp

GameManager.o: $(GDIR)GameManager.cpp
	$(CC) $(CFLAGS) -c $(GDIR)GameManager.cpp

RenderSystem.o: $(RENDERSYSTEM_DIR)RenderSystem.cpp
	$(CC) $(CFLAGS) -c $(RENDERSYSTEM_DIR)RenderSystem.cpp

VertexBuffer.o:	$(RENDERSYSTEM_DIR)VertexBuffer.cpp
	$(CC) $(CFLAGS) -c $(RENDERSYSTEM_DIR)VertexBuffer.cpp

ShaderLoader.o: $(RENDERSYSTEM_DIR)ShaderLoader.cpp
	$(CC) $(CFLAGS) -c $(RENDERSYSTEM_DIR)ShaderLoader.cpp

ShaderInterface.o: $(RENDERSYSTEM_DIR)ShaderInterface.cpp
	$(CC) $(CFLAGS) -c $(RENDERSYSTEM_DIR)ShaderInterface.cpp

clean:
	rm *.o

cleanest:
	rm fps

