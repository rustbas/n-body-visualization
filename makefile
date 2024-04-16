all: result.o

result.o:
	gcc main.c -o result.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
